from bycc.agent.behavior_tree.nodes.bt_action import BTAction
from bycc.common.data_interface import RuleNodeOutput
from bycc.agent.config_def import BehaviorTreeNodeResult
import random
import statistics

import numpy as np
import json
from collections import defaultdict
import copy
from env_interface.utils.GetData import Get_EquipID

DECLARATION = {
    'name': 'XKU雷达对抗GR',      # 组件名称，用于前端显示和后台索引
    'class': 'XKUJamRule',  # 组件类名
    'params': {},
    'description': 'XKU雷达对抗GR决策任务，返回控制指令'    # 组件描述，用于前端显示
}

XKUJamRuleInput1 = {
    'IsNewTask':True,
    'sRID': 1,
    'KcgTaskType': 103,
    'KcgSubTaskType': 2, # 1表示雷达GR, 2表示强制GR, 3表示自主GR
    'TargetID': 1,
    'TargetRadius': 1,
    # 'GRYSBZ': 1,
    'JamMode': 1,
    # 'LDGRYS': 1,
    'fJamRF': 30.0,
    'fJamSigBW': 20.0,
    'JamPointAZ': 0.0,
    'JamPointEL': 0.0,
    'iProtectRFNum': 1,
    "pProtectRFInfo":[(20, 30)]
}

XKUJamRuleInput2 = {
    'IsNewTask':True,
    'sRID': 1,
    'KcgTaskType': 103,
    'KcgSubTaskType': 1, # 1表示雷达GR, 2表示强制GR, 3表示自主GR
    'TargetID': 1,
    'TargetRadius': 1,
    # 'GRYSBZ': 1,
    'JamMode': 1,
    # 'LDGRYS': 1,
    'fJamRF': 30.0,
    'fJamSigBW': 20.0,
    'JamPointAZ': 0.0,
    'JamPointEL': 0.0,
    'iProtectRFNum': 1,
    "pProtectRFInfo":[(0, 3)]
}


# 继承
class XKUJamRule(BTAction):
    def __init__(self, **kwargs):
        super().__init__()
        # 任务判断
        self.IsNewTask = None
        # 存任务信息
        self.CurrentTaskInfo = defaultdict()
        # 存info_manager里的数据
        self.CurrentObs = []
        # 存上一次的ZC目标信息
        self.Recon_Info = []
        # 存储之前的命令
        self.LastCmds = []
        # 存储上一次GR的时间
        self.StartTime = None
        # 存储雷达个数
        self.RadarNum = 0
        # 存储保护频段
        self.pProtectRFInfo = []
        # 存储Scheduler
        self.Scheduler = None
        self.EquipID = None


    # 获取任务信息
    def getMessage(self, message):
        CurrentTaskInfo = {}
        CurrentTaskInfo['KcgTaskType'] = message['XKUJamRuleInput']['KcgTaskType'] if 'KcgTaskType' in message['XKUJamRuleInput'] else None
        # FIXME 后续对可能不存在的数据进行保护
        CurrentTaskInfo['KcgSubTaskType'] = message['XKUJamRuleInput']['KcgSubTaskType']
        CurrentTaskInfo['JamMode'] = message['XKUJamRuleInput']['JamMode']   # 这里往下的参数，如果是强制GR任务，一定会有
        CurrentTaskInfo['fJamRF'] = message['XKUJamRuleInput']['fJamRF']
        CurrentTaskInfo['fJamSigBW'] = message['XKUJamRuleInput']['fJamSigBW']
        CurrentTaskInfo['JamPointAZ'] = message['XKUJamRuleInput']['JamPointAZ']
        CurrentTaskInfo['JamPointEL'] = message['XKUJamRuleInput']['JamPointEL']
        # 取保护频段信息
        CurrentTaskInfo['iProtectRFNum'] = message['XKUJamRuleInput']['iProtectRFNum']
        CurrentTaskInfo['pProtectRFInfo'] = message['XKUJamRuleInput']['pProtectRFInfo']
        # 处理保护频段
        if CurrentTaskInfo['iProtectRFNum'] > 0:
            pProtectRFInfo = [(ProtectRF[0], ProtectRF[1]) for ProtectRF in CurrentTaskInfo['pProtectRFInfo'] ]
            setattr(self, "pProtectRFInfo", pProtectRFInfo)

        return CurrentTaskInfo

    # 判断起始和终止频段，与保护频段的关系
    def GetEffectFreq(self, JamFreqList):
        jam_freq_list = JamFreqList.copy()

        if self.CurrentTaskInfo['pProtectRFInfo'] is not None:
            for (fStartRF, fEndRF) in self.CurrentTaskInfo['pProtectRFInfo']:
                new_remaining = []
                for part_start,part_end in jam_freq_list:
                    if part_start < fStartRF :
                        new_remaining.append((part_start,min(part_end,fStartRF)))
                    if part_end > fEndRF :
                        new_remaining.append((max(part_start,fEndRF),part_end))
                jam_freq_list = new_remaining
        return jam_freq_list

    # 取出侦查目标，并进行筛选
    def GetReconObs(self, info_manager):
        self.EquipID = Get_EquipID(info_manager)
        assert self.EquipID and self.EquipID != -1, "Invalid EquipID"

        ReconObs = []
        DangerClassList = [-1 for _ in range(8)]
        ProbList = [-1 for _ in range(8)]
        TargetIDList = [-1 for _ in range(8)]
        MinProbIndex = 0
        ObsTop = 0

        reconRadarPara = info_manager.raw_obs.extra_info_dict['obs']['data']['reconRadarPara']
        for ParaIndex in range(len(reconRadarPara)):    # 遍历任务信息
            # 判断是不是我的RADAR数据
            if self.EquipID != reconRadarPara[ParaIndex]['ReconID']:
                continue

            ReconDetectRadar = reconRadarPara[ParaIndex]['ReconRadarPara']
            self.RadarNum = reconRadarPara[ParaIndex]['RadarNum']

            for DetectRadar in range(self.RadarNum):     # DetectRadar:int  便利所有发现的雷达
                ReconResult = ReconDetectRadar[DetectRadar]['ReconResult']
                TargetID = ReconResult['TargetID']
                PlatType = ReconDetectRadar[DetectRadar]['PlatType']
                AZ = ReconResult['AZ']
                EL = ReconResult['EL']
                pRF = copy.deepcopy(ReconResult['pRF'])  # MHZ
                DangerClass = ReconDetectRadar[DetectRadar]['DangerClass']
                CaptureProb = ReconResult['CaptureProb']

                # 保护频段筛选的判断逻辑(判断的是点)
                for i in range(len(pRF)):
                    for protectRFtuple in self.pProtectRFInfo:
                        if protectRFtuple[0] <= pRF[i] <= protectRFtuple[1]:
                            pRF[i] = -1

                pRF = [RF for RF in pRF if RF != -1]
                if pRF == []:
                    continue

                ThisRadar = [TargetID, PlatType, AZ, EL, pRF, DangerClass, CaptureProb]

                # TargetID 相同，则将CaptureProb大的替换列表里面的，这个判断要在最前面，
                if TargetID in TargetIDList:
                    # 同一目标的威胁等级发生变化，优先级更高
                    if DangerClass < DangerClassList[TargetIDList.index(TargetID)]:
                        SameTargetIndex = TargetIDList.index(TargetID)
                        ReconObs[SameTargetIndex] = ThisRadar
                        DangerClassList[SameTargetIndex] = DangerClass
                        ProbList[SameTargetIndex] = CaptureProb
                        # MaxDangerClassIndex = DangerClassList.index(max(DangerClassList[:]))
                        # MinProbIndex = ProbList.index(min(ProbList[:]))
                    elif DangerClass == DangerClassList[TargetIDList.index(TargetID)]:
                        if CaptureProb > ProbList[TargetIDList.index(TargetID)]:
                            SameTargetIndex = TargetIDList.index(TargetID)
                            ReconObs[SameTargetIndex] = ThisRadar
                            ProbList[SameTargetIndex] = CaptureProb
                            # MaxDangerClassIndex = DangerClassList.index(max(DangerClassList[:]))
                            # MinProbIndex = ProbList.index(min(ProbList[:]))
                    continue

                # 前8个直接入列
                if ObsTop < 8:
                    ReconObs[ObsTop] = ThisRadar
                    DangerClassList[ObsTop] = DangerClass
                    ProbList[ObsTop] = CaptureProb
                    TargetIDList[ObsTop] = TargetID
                    ObsTop += 1
                    # 修改1 ObsTop == 7
                    if ObsTop == 8:
                        # NOTE 记录当前最大DangerClassIndex，可能存在复数个同威胁等级的，要取出其中截获概率最小的那个作为Index
                        # 修改2
                        # 找出威胁等级最低的目标
                        max_danger_value = max(DangerClassList[:])
                        # 获取所有威胁等级最低的目标的索引，放到列表里面
                        lowest_indices = [i for i in range(8) if DangerClassList[i] == max_danger_value]
                        # 在这些索引中找出CaptureProb最小的
                        MinProbIndex = min(lowest_indices, key=lambda i: ProbList[i])
                        # MinProbIndex = ProbList.index(min(ProbList[:]))
                    continue

                # 修改3：DangerClass小的威胁等级高，应该保留
                # 如果新目标威胁等级高于当前最弱的（即新目标的DangerClass更小或者DangerClass相同，CaptureProb更大），则替换
                if DangerClass < DangerClassList[MinProbIndex]:
                    # 替换最弱目标
                    ReconObs[MinProbIndex] = ThisRadar
                    DangerClassList[MinProbIndex] = DangerClass
                    ProbList[MinProbIndex] = CaptureProb
                    TargetIDList[MinProbIndex] = TargetID

                    # 修改4：更新后重新计算最弱目标索引
                    # 找出新的威胁等级最低（DangerClass最大）的目标
                    max_danger_value = max(DangerClassList[:])
                    # 找出所有威胁等级最低的目标
                    lowest_indices = [i for i in range(8) if DangerClassList[i] == max_danger_value]
                    # 在这些目标中找出截获概率最小的
                    MinProbIndex = min(lowest_indices, key=lambda i: ProbList[i])

                # 修改5：如果威胁等级与当前最弱目标相同
                elif DangerClass == DangerClassList[MinProbIndex]:
                    # 如果CaptureProb大于最弱目标的CaptureProb，则替换
                    if CaptureProb > ProbList[MinProbIndex]:
                        ReconObs[MinProbIndex] = ThisRadar
                        DangerClassList[MinProbIndex] = DangerClass
                        ProbList[MinProbIndex] = CaptureProb
                        TargetIDList[MinProbIndex] = TargetID

                        # 修改6：更新后重新计算最弱目标索引
                        max_danger_value = max(DangerClassList[:])
                        lowest_indices = [i for i in range(8) if DangerClassList[i] == max_danger_value]
                        MinProbIndex = min(lowest_indices, key=lambda i: ProbList[i])                               # 更新对应行的CaptureProb

        # 基于CaptureProb对ReconObs进行排序
        ObsCopy = ReconObs.copy()
        SortedObs = sorted(ObsCopy, key=lambda row: row[-1], reverse=True)   # -1为CaptureProb的索引

        return SortedObs

    # 设置强制GR下
    def SetForceJamType(self):
        totalcmds = []
        # zscmds临时使用
        policyID = {'PolicyID': 1}
        forcecmds = {'SetJamOnoff': {"JamChannelList": []},
                  'SetRadarJamPolar': {'PolarType': 0},
                  'SetRadarJamType': {'JamChannelList': []}}
        forcecmds['SetJamOnoff']['JamChannelList'].append({'ChannelID': 1, 'Onoff': 1})
        # 设置GR方向
        tempcmds = {
                    'SetJamType': 101 ,
                    'JamParam': {'SetJamRF':0, 'SetJamBandWidth':0},
                    'SetTargetID': 1,
                    'SetJamAZ': self.CurrentTaskInfo['JamPointAZ'],
                    'SetJamEL': self.CurrentTaskInfo['JamPointEL']
                    }
        StartFreq = np.array(self.CurrentTaskInfo['fJamRF']) - self.CurrentTaskInfo['fJamSigBW'] / 2
        EndFreq = np.array(self.CurrentTaskInfo['fJamRF']) + self.CurrentTaskInfo['fJamSigBW'] / 2
        # 判断是否在保护频段
        FreqList = list(np.vstack((StartFreq, EndFreq)).T)
        # 设置GR频段
        tempcmds['JamParam']['SetJamRF'] = self.GetEffectFreq(FreqList)
        # 天线极化设置
        if self.CurrentTaskInfo['KcgTaskType'] == 202:
            forcecmds['SetRadarJamPolar']['PolarType'] = 3
        elif self.CurrentTaskInfo['KcgTaskType'] == 203:
            forcecmds['SetRadarJamPolar']['PolarType'] = 2
        # 设置侦干时序
        # cmds['SetJamDutyCycle'] = [0.0, 1000.0]
        forcecmds['SetRadarJamType']['JamChannelList'].append(tempcmds)
        totalcmds.append(policyID)
        totalcmds.append(forcecmds)
        return totalcmds

    # 侦收信号下GR

    """
        GR从ReconResult (R), （L）COMMDETECTPara(C)获取目标信息，
        最核心影响GR参数的是  pRF, [RF1, RF2, ...]
        选择GR目标
        RadarNum = 10, （L）nTrgNum = 8
        8, 4 + 4（L：雷+通），XKU就是8个，L可能需要拆分
        截获概率最高，且不同目标的回波结果的前4个，pRF(), PRI, PW
        
        (pRF() + BandWidth) Type（GR样式）
        BandWidth 网络控制
        pRF 也会通过网络输出，最后可设计一个开关，来判断是输出规则的还是输出网络的
        
        1. Type = 梳状谱 len(pRF()) <= 8
        2. Type = 噪声 1 + 1（取pRF的中位数）
        3. Type = len(pRF()) <= 8
        
        取目标  筛选目标（基于保护频段） 合并目标  排序（基于CaptureProb排序）
        
        
        
        "DangerClass:"
        组合优化
        Pareto
    """
    def SetZSJam(self):
        cmds = []

        # 以DangerClass的值进行排序
        # SetJamParaList = sorted(self.CurrentObs['reconRadarPara']['ReconRadarPara'],
        #                                     key=lambda x: x['DangerClass'])
        jampolar = {"PolarType": 0}
        # TODO 处理多个装备GR参数设置 >8个 按照8个处理
        #  根据taskcontrol判断需要设置几个通道，并且对于通道的GR样式也要进行设置（3选1）
        # [TargetID, PlatType, AZ, EL, pRF, CaptureProb]
        for i in range(len(self.CurrentObs)):
            policyID = {'PolicyID': -1}
            jamparamlist = {'SetJamOnOff': {"JamChannelList": []},
                            'SetRadarJamType': {'JamChannelList': []},
                            'SetDutyCycle':{}}
            jamchannel = {'JamParam': {},
                          'SetTargetID': -1,
                          'SetJamAZ': -1,
                          'SetJamEL': -1}
            # TODO SetJamOnOff是个字典，不是列表
            jamonoff = {'ChannelID': i + 1, 'Onoff': 1}
            jamparamlist['SetJamOnOff']['JamChannelList'].append(jamonoff)
            policyID['PolicyID'] = i + 1
            jamchannel['SetTargetID'] = self.CurrentObs[i][0]
            jamchannel['SetJamAZ'] = self.CurrentObs[i][2]
            jamchannel['SetJamEL'] = self.CurrentObs[i][3]
            # 设置GR样式
            # 先用随机值代替（0：梳状谱，1：噪声，2：精瞄频）
            jamtype = random.randint(0, 2)
            if jamtype == 0:
                jamchannel['SetJamType'] = 101
                # 设置GR频段
                jamchannel['JamParam']['SetJamRF'] = self.CurrentObs[i][4]  # MHZ
                # TODO 设置带宽（网络控制）
                jamchannel['JamParam']['SetJamBandWidth'] = -1
            elif jamtype == 1:
                jamchannel['SetJamType'] = 102
                # 设置GR频段，取中位数
                jamchannel['JamParam']['SetJamRF'] = [statistics.median(self.CurrentObs[i][4])] # MHZ
                # TODO 设置带宽（网络控制）
                jamchannel['JamParam']['SetJamBandWidth'] = -1
            elif jamtype == 2:
                jamchannel['SetJamType'] = 103
                # 设置GR频段
                jamchannel['JamParam']['SetJamRF'] = self.CurrentObs[i][4] # MHZ
                # TODO 设置带宽（网络控制）
                jamchannel['JamParam']['SetJamBandWidth'] = -1

            # jamchannel['SetJamBandWidth']
            # 天线极化设置 2：垂直极化，3：水平极化，4：斜极化
            if self.CurrentTaskInfo['KcgTaskType'] == 202:
                jampolar['PolarType'] = 2
            elif self.CurrentTaskInfo['KcgTaskType'] == 203:
                jampolar['PolarType'] = 3
            jamdutycycle = {'DutyCycle': [100.0, 900.0]}
            jamparamlist['SetRadarJamType']['JamChannelList'].append(jamchannel)
            jamparamlist['SetRadarJamPolar'] = jampolar
            jamparamlist['SetDutyCycle'] = jamdutycycle
            cmds.append(policyID)
            cmds.append(jamparamlist)
        # cmds['SetDutyCycle']['DutyCycle'] = [100.0, 900.0]
        return cmds

    def step(self, info_manager, blackboard, message):
        if message['XKUJamRuleSC']:
            return self._step(info_manager, blackboard, message)
        else:
            return ([{'SetRadarJamParam_Rule':{'Scheduler':message['XKUJamRuleSC']}}],
                    BehaviorTreeNodeResult.SUCCESS, {})

    def _step(self, info_manager, blackboard, message):
        cmds = {}
        # 取scheduler
        self.Scheduler = message['XKUJamRuleSC']
        # 取任务判断标志
        self.IsNewTask = message['XKUJamRuleInput']['IsNewTask']
        # 新任务
        if self.IsNewTask:
            # 取任务信息
            self.CurrentTaskInfo = self.getMessage(message)
            # 强制GR
            if self.CurrentTaskInfo['KcgSubTaskType'] == 2:
                cmds = self.SetForceJamType()
            # 侦收信号GR
            elif self.CurrentTaskInfo['KcgSubTaskType'] == 1:
                # 取数据
                self.CurrentObs = self.GetReconObs(info_manager)
                if len(self.CurrentObs) == 0:
                    cmds = []
                else:
                    cmds = self.SetZSJam()

            # FIXME 没处理无效值？
            self.LastCmds = cmds
        # 旧任务
        else:
            # 强制GR
            if self.CurrentTaskInfo['KcgSubTaskType'] == 2:
                cmds = self.LastCmds

            # 侦收信号GR
            elif self.CurrentTaskInfo['KcgSubTaskType'] == 1:
                self.CurrentObs = self.GetReconObs(info_manager)
                # self.Recon_Info.append(self.CurrentObs)
                if len(self.CurrentObs) == 0:
                    cmds = []
                else:
                    cmds = self.SetZSJam()

        tempcmds = {'SetRadarJamParam_Rule': {'SetRadarJamParaList': cmds}}
        total_cmds = self.SendCommand(info_manager, tempcmds)

        return total_cmds, BehaviorTreeNodeResult.SUCCESS, {}

    def SendCommand(self, info_manager, cmds):
        MyEquipID = Get_EquipID(info_manager)
        assert MyEquipID != -1, 'EquipID 为无效值'

        cmds['SetRadarJamParam_Rule']["JammerID"] = MyEquipID
        cmds['SetRadarJamParam_Rule']["KcgTaskType"] = self.CurrentTaskInfo["KcgTaskType"]
        cmds['SetRadarJamParam_Rule']["KcgSubTaskType"] = self.CurrentTaskInfo["KcgSubTaskType"]
        cmds['SetRadarJamParam_Rule']["Scheduler"] = self.Scheduler
        return [cmds]


if __name__ == '__main__':
    file_path = 'info_manager_for_XKUTC.json'
    with open(file_path) as f:
        info_manager = json.load(f)

    xku_rule = XKUJamRule()
    # 测试强制GR
    cmds, _, _ = xku_rule.step(info_manager, None, message={'XKUJamRuleInput':XKUJamRuleInput1})
    print(cmds)
    print("---------------------------------------------------------------")
    # 测试侦收GR
    cmds2, _, _ = xku_rule.step(info_manager, None, message={'XKUJamRuleInput': XKUJamRuleInput2})
    print(cmds2)
    # print("---------------------------------------------------------------")
    # # 测试星载
    # cmds3, _, _ = xku_rule.step(info_manager, None, message={'XKUJamRuleInput': XKUJamRuleInput3})
    # print(cmds3)
    # print("---------------------------------------------------------------")

    # # 测试旧任务报文，但info_manager不同
    # file_path = 'info_manager2.json'
    # with open(file_path) as f:
    #     info_manager = json.load(f)
    # cmds, _, _ = xku_rule.step(info_manager, None, message={'XKUJamRuleInput': XKUJamRuleInput4})
    # print(cmds)
    # print("---------------------------------------------------------------")
    #print(1)


