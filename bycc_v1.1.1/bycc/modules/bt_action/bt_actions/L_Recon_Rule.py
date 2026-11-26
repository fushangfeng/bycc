import json
import numpy as np
import math as mt

from bycc.agent.behavior_tree.nodes.bt_action import BTAction
from bycc.agent.config_def import BehaviorTreeNodeResult

from env_interface.utils.GetData import Get_EquipID

"""
任务报文作为初始化时给予的信息，可能后续要根据info_manager来控制

启用 等待 启用 思考这样的逻辑如何实现
"""

DECLARATION = {
    "name": "L雷达对抗ZC",  # 组件名称，用于前端显示和后台索引
    "class": "LReconRule",  # 组件类名
    "params": {},
    "description": "L雷达对抗ZC决策任务，返回控制指令"  # 组件描述，用于前端显示
}


class LReconRule(BTAction):
    def __init__(self, **kwargs):
        super().__init__()
        self.Task_Info = {}
        self.Recon_Info = []
        self.cmds = []
        self.IsNewTask = False

        self.Search_Param = {}
        self.Watch_Param = {}

        self.EquipID = -1

        self.LastTaskMessage = None
        self.Last_KcgSubTaskType = 1  # 表示上次的工作任务 默认为搜索  1表示搜索, 2表示监视

        self.WorkPitNorList = [2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30]
        self.L_Search_Freq = [(0.8, 1.2), (1.2, 1.6), (1.6, 2)]
        self.L_Watch_Freq = [(0.8, 1.2), (1.2, 1.6), (1.6, 2)]

        # 存储Scheduler的值
        self.Scheduler = None

    def step(self, info_manager, blackboard, message):
        if message['LReconRuleInput'] == {}:  # 不启动ZC
            return [{'SetRadarReconParam_Rule':{'Scheduler':message['LReconRuleSC']}}], \
                    BehaviorTreeNodeResult.SUCCESS, {}   # TODO 如果message为空，只用在cmd里面传scheduler

        # 取SC标志
        if message['LReconRuleSC']:
            return self._step(info_manager, blackboard, message)
        else:
            return [{'SetRadarReconParam_Rule':{'Scheduler':message['LReconRuleSC']}}], \
                    BehaviorTreeNodeResult.SUCCESS, {}


    def _step(self, info_manager, blackboard, message):
        # 取scheduler的值
        self.Scheduler = message['LReconRuleSC']
        # 取任务标志：
        self.IsNewTask = message['LReconRuleInput']['IsNewTask']

        # 如果有任务
        if self.IsNewTask:
            self.KcgTaskType = message['LReconRuleInput']['KcgTaskType']
            self.KcgSubTaskType = message['LReconRuleInput']['KcgSubTaskType']
            # 取保护频段
            if 'pProtectRFInfo' in message['LReconRuleInput']:
                self.pProtectRFInfo = message['LReconRuleInput']['pProtectRFInfo']
            else:
                self.pProtectRFInfo = []

            self.Task_Info['fStartAZ'] = message['LReconRuleInput']['fStartAZ']
            self.Task_Info['fEndAZ'] = message['LReconRuleInput']['fEndAZ']
            self.Task_Info['fStartEL'] = message['LReconRuleInput']['fStartEL']
            self.Task_Info['fEndEL'] = message['LReconRuleInput']['fEndEL']
            self.Task_Info['fStartRF'] = message['LReconRuleInput']['fStartRF']
            self.Task_Info['fEndRF'] = message['LReconRuleInput']['fEndRF']

            # 搜索 默认认为是雷侦
            # 分 通侦查、雷侦、一体化
            if self.KcgSubTaskType == 1:
                ReconParaList, _ = self.SetReconSearchPolicy(
                    info_manager, self.IsNewTask)

                self.Search_Param["SetReconParaList"] = ReconParaList
                self.cmds = [{"SetReconParaList": ReconParaList}]
                self.Last_KcgSubTaskType = 1
                self.Last_Cmd = self.cmds

            # 监视  默认认为是雷侦
            # 分 通侦、雷侦、一体化
            elif self.KcgSubTaskType == 2:
                self.Watch_Param["SetReconParaList"] = self.SetReconWatchPolicy(
                    info_manager, self.IsNewTask)

                self.cmds= [{"SetReconParaList": self.Watch_Param["SetReconParaList"]}]
                self.Last_KcgSubTaskType = 2
                self.Last_Cmd = self.cmds

        # 如果没任务
        else:
            # 如果上次任务是搜索：
            if self.Last_KcgSubTaskType == 1:
                self.EquipID = Get_EquipID(info_manager)
                assert self.EquipID and self.EquipID != -1, "Invalid EquipID"

                # 基于EquipID 获取Recon_RadarPara
                cur_reconRadarPara = {}
                reconRadarPara_List = info_manager.raw_obs.extra_info_dict['obs']['data']['reconRadarPara']
                for reconRadarPara in reconRadarPara_List:
                    if self.EquipID == reconRadarPara['ReconID']:
                        cur_reconRadarPara = reconRadarPara
                        break

                # 基于EquipID 获取COMMDETECTPARA
                cur_comMdetectPara = {}
                comMdetectPara_List = info_manager.raw_obs.extra_info_dict['obs']['data']['comMdetectPara']
                for comMdetectPara in comMdetectPara_List:
                    if self.EquipID == comMdetectPara['ReconID']:
                        cur_comMdetectPara = comMdetectPara

                cur_ReconRadarPara_List = []
                cur_comMdetectPara_List = []


                # 如果当前收到目标回波
                if "RadarNum" in cur_reconRadarPara:
                    if cur_reconRadarPara and cur_reconRadarPara["RadarNum"] > 0:
                        cur_ReconRadarPara_List = cur_reconRadarPara["ReconRadarPara"]
                        self.Recon_Info.append({"ReconRadarPara": cur_ReconRadarPara_List})

                        # ZC转为长时监视+短时ZC
                        Sorted_ReconRadarPara_List = sorted(cur_ReconRadarPara_List, key=lambda x: x["DangerClass"])

                        _, ExtraReconParaList = self.SetReconSearchPolicy(
                            info_manager, self.IsNewTask,
                            RadarNum=cur_comMdetectPara["RadarNum"],
                            nTrgNum=cur_comMdetectPara["nTrgNum"],
                            ReconResult=Sorted_ReconRadarPara_List[0]["ReconResult"]
                            # TrgPara=
                        )


                        self.cmds = [
                            {"SetReconParaList": self.Search_Param["SetReconParaList"] + ExtraReconParaList}
                        ]

                        self.Last_KcgSubTaskType = 1
                        self.Last_Cmd = self.cmds

                    # 如果当前没有目标回波
                    else:
                        #
                        self.Recon_Info.append({"ReconRadarPara": cur_ReconRadarPara_List})

                        if len(self.Recon_Info) >= 2 and len(self.Recon_Info[-2]) > 0:
                            self.cmds = [
                                {"SetReconParaList": self.Search_Param["SetReconParaList"]}
                            ]
                            self.Last_KcgSubTaskType = 1
                            self.Last_Cmd = self.cmds
                        else:
                            # 之前也无目标，则直接返回空，不改变ZC策略
                            self.Last_KcgSubTaskType = 1
                            self.cmds = self.Last_Cmd

            # 如果上次任务是监视：
            elif self.Last_KcgSubTaskType == 2:
                self.Last_KcgSubTaskType = 2
                self.cmds = self.Last_Cmd # 返回 []  表示一直执行监视

        grpc_cmds = self.SendCommand(info_manager)

        return grpc_cmds, BehaviorTreeNodeResult.SUCCESS, {}

    def find_idx(self, StartFreq, EndFreq, FreqList):
        # 找出索引
        Freq_idx_s = -1
        Freq_idx_e = -1
        for i, (s, e) in enumerate(FreqList):
            if s <= StartFreq and StartFreq <= e:
                Freq_idx_s = i
            if s <= EndFreq and EndFreq <= e:
                Freq_idx_e = i
            if Freq_idx_s != -1 and Freq_idx_e != -1:
                break
        return Freq_idx_s, Freq_idx_e


    def isGZ(self,StartFreq,EndFreq):
        for (fStartRF, fEndRF) in self.pProtectRFInfo:
            # 如果有重叠
            if ((StartFreq < fEndRF) and (fStartRF < EndFreq)):
                return True
        return False

    # ZC极化设置
    def SetReconPolarType(self, IsNewTask, **kwargs):

        if IsNewTask:
            ReconPolarType = 3  # 2是垂直 3是水平 4是斜极化
            return ReconPolarType
        else:
            #
            if kwargs['RadarNum']:
                RadarNum = kwargs['RadarNum']

            if kwargs['nTrgNum']:
                nTrgNum = kwargs['nTrgNum']

            # 如果当前收到雷达目标回波 且 无通信目标回波
            if RadarNum >= 0 and nTrgNum == 0:
                ReconPolarType = 3
            # 如果当前收到通信目标回波 且 无雷达目标回波
            elif RadarNum == 0 and nTrgNum > 0:
                ReconPolarType = 2
            # 如果当前收到通信和雷达目标回波
            elif RadarNum > 0 and nTrgNum > 0:
                ReconPolarType = 4

            return ReconPolarType

    # ZC策略设置
    def SetReconSearchPolicy(self, info_manager, IsNewTask=True, **kwargs):
        ReconSearchPolicy = []
        NewReconSearchPolicy = []
        if IsNewTask:
            PolicyID = 0
            DwellTime = 100.0
            WorkAzRng = (self.Task_Info['fStartAZ'] + self.Task_Info['fEndAZ']) / 2
            ReconPolarType = self.SetReconPolarType(IsNewTask)

            # 取出俯仰波位范围
            WorkPitNor_idx_s = -1
            WorkPitNor_idx_e = -1
            for i, WorkPitNor in enumerate(self.WorkPitNorList):
                if self.Task_Info['fStartEL'] <= WorkPitNor:
                    WorkPitNor_idx_s = i - 1
                    if (WorkPitNor_idx_s < 0):
                        WorkPitNor_idx_s = 0
                    break
            for i, WorkPitNor in enumerate(self.WorkPitNorList):
                if self.Task_Info['fEndEL'] <= WorkPitNor:
                    WorkPitNor_idx_e = i
                    break

            for i in range(WorkPitNor_idx_s, WorkPitNor_idx_e+1):
                WorkPitNor = self.WorkPitNorList[i]
                for (StartFreq, EndFreq) in self.L_Search_Freq:
                    # if not isGZ(StartFreq, EndFreq):
                    PolicyID += 1
                    ReconSearchPolicy.append({'PolicyID': PolicyID})
                    ReconSearchPolicy.append({
                        "SetReconRFPara": {
                            "StartFreq": StartFreq,
                            "EndFreq": EndFreq
                        },
                        "SetWorkPitNor": {
                            "WorkPitNor": WorkPitNor
                        },
                        "SetWorkAzRng": {
                            "WorkAzRng": WorkAzRng
                        },
                        "SetDwellTime": {
                            "DwellTime": DwellTime
                        },
                        "SetReconPolarType": {
                            "PolarType": ReconPolarType
                        }
                    })
        else:
            PolicyID = 0
            if kwargs['RadarNum']:
                RadarNum = kwargs['RadarNum']

            if kwargs['nTrgNum']:
                nTrgNum = kwargs['nTrgNum']

            if kwargs['ReconResult']:
                ReconResult = kwargs['ReconResult']

            if kwargs['TrgPara']:
                TrgPara = kwargs['TrgPara']

            ReconPolarType = self.SetReconPolarType(
                IsNewTask,
                RadarNum=RadarNum,
                nTrgNum=nTrgNum
            )

            # 找出

            min_radar_pRF = ReconResult["pRF"][np.argmin(ReconResult["pRF"])]
            max_radar_pRF = ReconResult["pRF"][np.argmax(ReconResult["pRF"])]

            Freq_idx_s, Freq_idx_e = self.find_idx(min_radar_pRF, max_radar_pRF, self.L_Search_Freq)

            WorkAzRng = (self.Task_Info['fStartAZ'] + self.Task_Info['fEndAZ']) / 2
            DwellTime = 1000.0

            for WorkPitNor in self.WorkPitNorList:
                for i in range(Freq_idx_s, Freq_idx_e + 1):
                    StartFreq = self.L_Search_Freq[i][0]
                    EndFreq = self.L_Search_Freq[i][1]

                    # if not isGZ(StartFreq, EndFreq):
                    PolicyID += 1
                    NewReconSearchPolicy.append({'PolicyID': PolicyID})

                    NewReconSearchPolicy.append({
                        "SetReconRFPara": {
                            "StartFreq": StartFreq,
                            "EndFreq": EndFreq
                        },
                        "SetWorkPitNor": {
                            "WorkPitNor": WorkPitNor
                        },
                        "SetWorkAzRng": {
                            "WorkAzRng": WorkAzRng
                        },
                        "SetDwellTime": {
                            "DwellTime": DwellTime
                        },
                        "SetReconPolarType": {
                            "PolarType": ReconPolarType  # 1是水平极化 2是垂直极化 3是斜极化
                        }
                    })

        return ReconSearchPolicy, NewReconSearchPolicy

    # 监视策略设置
    def SetReconWatchPolicy(self, info_manager, IsNewTask=True):

        ReconWatchPolicy = []
        if IsNewTask:
            PolicyID = 0
            DwellTime = 100.0
            ReconPolarType = 3
            WorkAzRng = (self.Task_Info['fStartAZ'] + self.Task_Info['fEndAZ']) / 2

            # 工作频率按0.8GHz~1.2GHz、1.2GHz~1.6GHz,1.6Ghz~2Ghz三段
            StartFreq = mt.floor(self.Task_Info['fStartRF'])
            EndFreq = mt.ceil(self.Task_Info['fEndRF'])

            Freq_idx_s, Freq_idx_e = self.find_idx(StartFreq, EndFreq, self.L_Watch_Freq)

            for WorkPitNor in self.WorkPitNorList:
                for i in range(Freq_idx_s, Freq_idx_e+1):
                    StartFreq = self.L_Watch_Freq[i][0]
                    EndFreq = self.L_Watch_Freq[i][1]

                    # if not isGZ(StartFreq, EndFreq):
                    PolicyID +=1
                    ReconWatchPolicy.append({'PolicyID':PolicyID})
                    ReconWatchPolicy.append({
                        "SetReconRFPara": {
                            "StartFreq": StartFreq,
                            "EndFreq": EndFreq
                        },
                        "SetWorkPitNor": {
                            "WorkPitNor": WorkPitNor
                        },
                        "SetWorkAzRng": {
                            "WorkAzRng": WorkAzRng
                        },
                        "SetDwellTime": {
                            "DwellTime": DwellTime
                        },
                        "SetReconPolarType": {
                            "PolarType": ReconPolarType  # 2是垂直极化 3水平 4是斜极化
                        }
                    })

        return ReconWatchPolicy

    def SendCommand(self, info_manager):
        cmds = []
        MyEquipID = Get_EquipID(info_manager)
        assert MyEquipID != -1, 'EquipID 为无效值'

        if self.cmds != []:
            self.cmds[0]["ReconID"] = MyEquipID
            self.cmds[0]["KcgTaskType"] = self.KcgTaskType
            self.cmds[0]["KcgSubTaskType"] = self.KcgSubTaskType
            self.cmds[0]["Scheduler"] = self.Scheduler
        else:
            self.cmds.append({
                "ReconID": MyEquipID,
                "KcgTaskType": self.KcgTaskType,
                "KcgSubTaskType": self.KcgSubTaskType,
                "Scheduler": self.Scheduler
            })

        cmds.append({"SetRadarReconParam_Rule": self.cmds[0]})

        return cmds

if __name__ == '__main__':
    file_path = 'info_manager.json'
    with open(file_path) as f:
        info_manager = json.load(f)
