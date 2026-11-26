import json
import numpy as np
import math as mt

from bycc.agent.behavior_tree.nodes.bt_action import BTAction
from bycc.agent.config_def import BehaviorTreeNodeResult

from env_interface.utils.GetData import Get_EquipID

DECLARATION = {
    "name": "XKU雷达对抗ZC",      # 组件名称，用于前端显示和后台索引
    "class": "XKUReconRule",  # 组件类名
    "params": {},
    "description": "XKU雷达对抗ZC决策任务，返回控制指令"    # 组件描述，用于前端显示
}


class XKUReconRule(BTAction):
    def __init__(self):
        super(XKUReconRule).__init__()
        self.Task_Info = {}
        self.Recon_Info = []
        self.cmds = []
        self.IsNewTask = False

        self.Search_Param = {}
        self.Watch_Param = {}

        self.PolicyNum = 0

        self.LastTaskMessage = None
        self.Last_KcgSubTaskType = None  # 表示上次的工作任务 默认为搜索  1表示搜索, 2表示监视

        self.WorkPitNorList = [2, 6, 10, 14, 18, 22, 26, 30]                            # 度
        self.XKU_Search_Freq = [(6, 10), (10, 14), (14, 18)]                            # GHz
        self.XKU_Watch_Freq = [(6, 10), (8, 12), (10, 14), (12, 16), (14, 18)]          # GHz

        # 我方平台id
        self.EquipID = -1
        # 存储Scheduler的值
        self.Scheduler = None

        self.Aero_List = [6, 7, 8, 13, 15]
        self.Star_List = [9]

    def step(self, info_manager, blackboard, message):
        if message['XKUReconRuleInput'] == {}:  # 不启动ZC
            return [{'SetRadarReconParam_Rule':{'Scheduler':message['XKUReconRuleSC']}}], \
                    BehaviorTreeNodeResult.SUCCESS, {}   # TODO 如果message为空，只用在cmd里面传scheduler

        # 取SC标志
        if message['XKUReconRuleSC']:
            return self._step(info_manager, blackboard, message)
        else:
            return [{'SetRadarReconParam_Rule':{'Scheduler':message['XKUReconRuleSC']}}], \
                    BehaviorTreeNodeResult.SUCCESS, {}


    def _step(self, info_manager, blackboard, message):
        # 取scheduler的值
        self.Scheduler = message['XKUReconRuleSC']
        # 取任务标志：
        self.IsNewTask = message['XKUReconRuleInput']['IsNewTask']

        # 如果有新任务
        if self.IsNewTask:
            self.KcgTaskType = message['XKUReconRuleInput']['KcgTaskType']
            self.KcgSubTaskType = message['XKUReconRuleInput']['KcgSubTaskType']
            # 取保护频段
            if 'pProtectRFInfo' in message['XKUReconRuleInput']:
                self.pProtectRFInfo = message['XKUReconRuleInput']['pProtectRFInfo']
            else:
                self.pProtectRFInfo = []

            self.Task_Info['fStartAZ'] = message['XKUReconRuleInput']['fStartAZ']
            self.Task_Info['fEndAZ'] = message['XKUReconRuleInput']['fEndAZ']
            self.Task_Info['fStartEL'] = message['XKUReconRuleInput']['fStartEL']
            self.Task_Info['fEndEL'] = message['XKUReconRuleInput']['fEndEL']
            self.Task_Info['fStartRF'] = message['XKUReconRuleInput']['fStartRF']
            self.Task_Info['fEndRF'] = message['XKUReconRuleInput']['fEndRF']

            # 搜索
            if self.KcgSubTaskType == 1:
                ReconParaList, _ = self.SetReconSearchPolicy(self.IsNewTask)

                self.Search_Param["SetReconParaList"] = ReconParaList
                self.cmds = [{"SetReconParaList":ReconParaList}]
                self.Last_KcgSubTaskType = 1
                self.Last_Cmd = self.cmds

            # 监视
            elif self.KcgSubTaskType == 2:
                self.Watch_Param["SetReconParaList"] = self.SetReconWatchPolicy(self.IsNewTask)

                self.cmds = [{"SetReconParaList":self.Watch_Param["SetReconParaList"]}]
                self.Last_KcgSubTaskType = 2
                self.Last_Cmd = self.cmds

        # 如果没新任务
        else:
            # 如果上次任务是搜索：
            if self.Last_KcgSubTaskType == 1:
                # 从info_manager中取目标回波，last_target_info存储起来 方便后续对比
                self.EquipID = Get_EquipID(info_manager)
                assert self.EquipID and self.EquipID != -1, "Invalid EquipID"

                # 基于ReconID 获取Recon_RadarPara
                cur_reconRadarPara = None
                reconRadarPara_List = info_manager.raw_obs.extra_info_dict['obs']['data']['reconRadarPara']
                for reconRadarPara in reconRadarPara_List:
                    if self.EquipID == reconRadarPara['ReconID']:
                        cur_reconRadarPara = reconRadarPara
                        break

                cur_ReconRadarPara_List = []
                # 如果当前收到目标回波
                if cur_reconRadarPara and cur_reconRadarPara["RadarNum"] > 0:
                    cur_ReconRadarPara_List = cur_reconRadarPara["ReconRadarPara"]
                    self.Recon_Info.append({"ReconRadarPara": cur_ReconRadarPara_List})
                    # 排序DangerClass
                    Sorted_ReconRadarPara_List = sorted(cur_ReconRadarPara_List, key=lambda x: x["DangerClass"])

                    # ZC转为长时监视+短时ZC
                    _, ExtraReconParaList = self.SetReconSearchPolicy(self.IsNewTask,
                        PlatType=Sorted_ReconRadarPara_List[0]["PlatType"],
                        ReconResult=Sorted_ReconRadarPara_List[0]["ReconResult"])

                    self.cmds = [
                        {"SetReconParaList": self.Search_Param["SetReconParaList"] + ExtraReconParaList}
                    ]
                    self.Last_Cmd = self.cmds
                    self.Last_KcgSubTaskType = 1

                # FIXME 如果当前没有目标回波,需找总体确认工作状态变化
                else:
                    self.Recon_Info.append({"ReconRadarPara": cur_ReconRadarPara_List})
                    # 之前有目标 现在没有目标  不需要进行对某目标的凝视
                    # 可以增加条件，避免频繁控制：
                    # 1. 采用最小执行时间约束 若小于执行时间 则输出[] 大于就生成新cmd（可能与上次一样）

                    # 上次有目标
                    if len(self.Recon_Info) >= 2 and len(self.Recon_Info[-2]) > 0:
                        self.cmds = [
                            {"SetReconParaList": self.Search_Param["SetReconParaList"]}
                        ]
                        self.Last_KcgSubTaskType = 1
                        self.Last_Cmd = self.cmds
                    else:
                        # 如果是仿真第一轮 or 之前也无目标，则直接返回空，不改变ZC策略
                        self.Last_KcgSubTaskType = 1
                        self.cmds = self.Last_Cmd

            # 如果上次任务是监视：
            elif self.Last_KcgSubTaskType == 2:
                self.Last_KcgSubTaskType = 2
                self.cmds = self.Last_Cmd # 返回 Last_Cmd  表示一直执行监视

        grpc_cmds = self.SendCommand(info_manager)

        return grpc_cmds, BehaviorTreeNodeResult.SUCCESS, {}

    # ZC策略设置
    def SetReconSearchPolicy(self, IsNewTask=True, **kwargs):
        ReconSearchPolicy = []
        NewReconSearchPolicy = []
        if IsNewTask:
            PolicyID = 0
            # 如果是机载目标
            if (self.KcgTaskType == 201) or (self.KcgTaskType == 202):
                DwellTime = 100.0
                ReconPolarType = 2
                WorkAzRng = (self.Task_Info['fStartAZ'] + self.Task_Info['fEndAZ']) / 2
                for WorkPitNor in self.WorkPitNorList:
                    for (StartFreq, EndFreq) in self.XKU_Search_Freq:
                        # if not isGZ(StartFreq, EndFreq):
                        PolicyID += 1
                         
                        ReconSearchPolicy.append({"PolicyID": PolicyID})
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
                                "PolarType": ReconPolarType   # 1是水平极化 2是垂直极化 3是斜极化
                            }
                        })

            # FIXME 如果是星载目标, 需更新参数设置策略
            elif self.KcgTaskType == 203:
                WorkPitNor = self.WorkPitNorList[0]
                DwellTime = 100.0
                ReconPolarType = 1
                WorkAzRng = (self.Task_Info['fStartAZ'] + self.Task_Info['fEndAZ']) / 2
                StartFreq = mt.floor(self.Task_Info['fStartRF'])
                EndFreq = min(mt.ceil(self.Task_Info['fEndRF']), StartFreq + 4)

                # 找出所有范围
                Freq_idx_s = -1
                Freq_idx_e = -1
                for i,(s,e) in enumerate(self.XKU_Search_Freq):
                    if s <= StartFreq <= e:
                        Freq_idx_s = i
                    if s <= EndFreq <= e:
                        Freq_idx_e = i
                    if Freq_idx_s != -1 and Freq_idx_e !=-1:
                        break

                for i in range(Freq_idx_s, Freq_idx_e+1):
                    StartFreq = self.XKU_Search_Freq[i][0]
                    EndFreq = self.XKU_Search_Freq[i][1]
                    # if not isGZ(StartFreq, EndFreq):
                    PolicyID += 1

                    ReconSearchPolicy.append({"PolicyID": PolicyID})
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
                            "PolarType": ReconPolarType  # 1是水平极化 2是垂直极化 3是斜极化
                        }
                    })

        else:
            PolicyID = 0
            PlatType = -1
            ReconResult = {}
            if 'PlatType' in kwargs:
                PlatType = kwargs['PlatType']

            if 'ReconResult' in kwargs:
                ReconResult = kwargs['ReconResult']

            # 找出
            min_pRF = ReconResult['pRF'][np.argmin(ReconResult['pRF'])] # MHZ
            max_pRF = ReconResult['pRF'][np.argmax(ReconResult['pRF'])] # MHZ

            # 找出包含范围的索引
            Freq_idx_s = -1
            Freq_idx_e = -1
            for i, (s, e) in enumerate(self.XKU_Search_Freq):
                if s <= min_pRF <= e:
                    Freq_idx_s = i
                if s <= max_pRF <= e:
                    Freq_idx_e = i
                if Freq_idx_s != -1 and Freq_idx_e != -1:
                    break

            # 如果是机载的
            if int(PlatType) in self.Aero_List:

                DwellTime = 100.0
                ReconPolarType = 2
                WorkAzRng = (self.Task_Info['fStartAZ'] + self.Task_Info['fEndAZ']) / 2
                for WorkPitNor in self.WorkPitNorList:
                    for i in range(Freq_idx_s, Freq_idx_e + 1):
                        StartFreq = self.XKU_Search_Freq[i][0]
                        EndFreq = self.XKU_Search_Freq[i][1]

                        # if not isGZ(StartFreq, EndFreq):
                        PolicyID += 1
                        NewReconSearchPolicy.append({"PolicyID": PolicyID})
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
            # 如果是星载
            elif int(PlatType) in self.Star_List:

                WorkPitNor = self.WorkPitNorList[0]
                DwellTime = 100.0
                ReconPolarType = 1
                WorkAzRng = (self.Task_Info['fStartAZ'] + self.Task_Info['fEndAZ']) / 2
                for i in range(Freq_idx_s, Freq_idx_e + 1):
                    StartFreq = self.XKU_Search_Freq[i][0]
                    EndFreq = self.XKU_Search_Freq[i][1]

                    # if not isGZ(StartFreq, EndFreq):
                    PolicyID += 1
                     
                    NewReconSearchPolicy.append({"PolicyID": PolicyID})
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

    def SetReconWatchPolicy(self, IsNewTask=True):
        ReconWatchPolicy = []
        if IsNewTask:
            PolicyID = 0
            # 如果是机载目标
            if (self.KcgTaskType == 201) or (self.KcgTaskType == 202):
                DwellTime = 100.0
                ReconPolarType = 2

                # 工作频率按6GHz~8GHz、8GHz~10GHz,10Ghz~12Ghz,12~14Ghz,14GHz~18GHz五段
                StartFreq = mt.floor(self.Task_Info['fStartRF'])
                EndFreq = mt.ceil(self.Task_Info['fEndRF'])

                # 找出索引
                Freq_idx_s = -1
                Freq_idx_e = -1
                for i, (s, e) in enumerate(self.XKU_Watch_Freq):
                    if s <= StartFreq <= e:
                        Freq_idx_s = i
                    if s <= EndFreq <= e:
                        Freq_idx_e = i
                    if Freq_idx_s != -1 and Freq_idx_e != -1:
                        break

                for WorkPitNor in self.WorkPitNorList:
                    for i in range(Freq_idx_s, Freq_idx_e+1):
                        StartFreq = self.XKU_Watch_Freq[i][0]
                        EndFreq = self.XKU_Watch_Freq[i][1]

                        # if not isGZ(StartFreq, EndFreq):
                        PolicyID += 1
                         
                        ReconWatchPolicy.append({"PolicyID": PolicyID})
                        ReconWatchPolicy.append({
                            "SetReconRFPara": {
                                "StartFreq": StartFreq,
                                "EndFreq": EndFreq
                            },
                            "SetWorkPitNor": {
                                "WorkPitNor": WorkPitNor
                            },
                            "SetDwellTime": {
                                "DwellTime": DwellTime
                            },
                            "SetReconPolarType": {
                                "PolarType": ReconPolarType  # 1是水平极化 2是垂直极化 3是斜极化
                            }
                        })

            # 如果是星载目标
            elif self.KcgTaskType == 203:
                WorkPitNor = self.WorkPitNorList[0]
                DwellTime = 100.0
                ReconPolarType = 1

                StartFreq = mt.floor(self.Task_Info['fStartRF'])
                EndFreq = min(mt.ceil(self.Task_Info['fEndRF']), StartFreq + 4)

                # 找出所有范围
                Freq_idx_s = -1
                Freq_idx_e = -1
                for i, (s, e) in enumerate(self.XKU_Search_Freq):
                    if s <= StartFreq <= e:
                        Freq_idx_s = i
                    if s <= EndFreq <= e:
                        Freq_idx_e = i
                    if Freq_idx_s != -1 and Freq_idx_e != -1:
                        break

                for i in range(Freq_idx_s, Freq_idx_e+1):
                    StartFreq = self.XKU_Search_Freq[i][0]
                    EndFreq = self.XKU_Search_Freq[i][1]

                    PolicyID += 1
                     
                    ReconWatchPolicy.append({"PolicyID": PolicyID})
                    ReconWatchPolicy.append({
                        "SetReconRFPara": {
                            "StartFreq": StartFreq,
                            "EndFreq": EndFreq
                        },
                        "SetWorkPitNor": {
                            "WorkPitNor": WorkPitNor
                        },
                        "SetDwellTime": {
                            "DwellTime": DwellTime
                        },
                        "SetReconPolarType": {
                            "PolarType": ReconPolarType  # 1是水平极化 2是垂直极化 3是斜极化
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

    recon = XKUReconRule()

    print(recon.Recon_Info)

