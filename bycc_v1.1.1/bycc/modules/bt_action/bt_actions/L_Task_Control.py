from bycc.agent.config_def import BehaviorTreeNodeResult
from bycc.agent.behavior_tree.nodes.bt_action import BTAction
from bycc.common.data_interface import RuleNodeOutput

import numpy as np
import copy
from env_interface.utils.GetData import Get_EquipID

DECLARATION = {
    "name": "L任务控制",  # 组件名称，用于前端显示和后台索引
    "class": "LTaskControl",  # 组件类名
    "params": {},
    "description": "L任务控制组件"
}


class LTaskControl(BTAction):
    """
    L任务控制模块
    """

    def __init__(self):
        super().__init__()
        self.LastReconTask = None
        self.LastJamTask = None
        self.LastReconOut = None
        self.LastJamOut = None

        self.EquipID = None
        # self.myPlatName = None
        self.task_manager = {
            "recon_task_info": {
                'Step0': {
                    "SetRadarReconTask": [
                        {
                            "SetRadarReconTask": {
                                "KcgTaskType": 101,  # 101雷达ZC模式  102雷达TC模式 103 电子GR模式   104是一体化模式
                                "KcgSubTaskType": 1,  # 1表示搜索, 2表示监视
                                "fStartRF": 12,  # 起始频率
                                "fEndRF": 14,  # 终止频率
                                "fStartAZ": 0.0,  # ZC起始方位
                                "fEndAZ": 180.0,  # 侦查终止方位
                                "fStartEL": 2.0,  # 俯仰起始
                                "fEndEL": 30.0,  # 俯仰终止
                            }
                        }
                    ],
                    "SetRadarJamTask": [],
                    "SetFreqControl": [
                        {
                            "iProtectRFNum": 1,
                            "pProtectRFInfo": [{
                                "fStartRF": 6,
                                "fEndRF": 10
                            }]
                        }
                    ]
                },  # NewTask, 有保护频段， SubTaskType = 1, 搜索
                'Step1': {
                    "SetRadarReconTask": [
                        {
                            "SetRadarReconTask":
                                {
                                    "KcgTaskType": 101,  # 101雷达ZC模式  102雷达TC模式 103 电子GR模式   104是一体化模式
                                    "KcgSubTaskType": 1,  # 1表示搜索, 2表示监视
                                    "fStartRF": 12,  # 起始频率
                                    "fEndRF": 14,  # 终止频率
                                    "fStartAZ": 0.0,  # ZC起始方位
                                    "fEndAZ": 180.0,  # 侦查终止方位
                                    "fStartEL": 2.0,  # 俯仰起始
                                    "fEndEL": 30.0,  # 俯仰终止
                                }
                        }
                    ],
                    "SetRadarJamTask": [],
                    "SetFreqControl":[
                            {
                                "iProtectRFNum": 1,
                                "pProtectRFInfo": [
                                    {
                                        "fStartRF": 6,
                                        "fEndRF": 10
                                    }
                                ]
                            }
                        ]
                },  # OldTask, 有保护频段， 1, 搜索, info_manager: RadarNum > 0
                'Step2': {
                    "SetRadarReconTask":[
                        {
                            "SetRadarReconTask":
                                {
                                    "KcgTaskType": 101,  # 101雷达ZC模式  102雷达TC模式 103 电子GR模式   104是一体化模式
                                    "KcgSubTaskType": 1,  # 1表示搜索, 2表示监视
                                    "fStartRF": 12,  # 起始频率
                                    "fEndRF": 14,  # 终止频率
                                    "fStartAZ": 0.0,  # ZC起始方位
                                    "fEndAZ": 180.0,  # 侦查终止方位
                                    "fStartEL": 2.0,  # 俯仰起始
                                    "fEndEL": 30.0,  # 俯仰终止
                                }
                        }
                    ],
                    "SetRadarJamTask": [],
                    "SetFreqControl":[
                            {
                                "iProtectRFNum": 1,
                                "pProtectRFInfo": [
                                    {
                                        "fStartRF": 6,
                                        "fEndRF": 10
                                    }
                                ]
                            }
                        ]
                },  # OldTask, 有保护频段， 1, 搜索, info_manager: RadarNum = 0
                'Step3': {
                    "SetRadarReconTask":[
                        {
                            "SetRadarReconTask":
                                {
                                    "KcgTaskType": 101,  # 101雷达ZC模式  102雷达TC模式 103 电子GR模式   104是一体化模式
                                    "KcgSubTaskType": 1,  # 1表示搜索, 2表示监视
                                    "fStartRF": 12,  # 起始频率
                                    "fEndRF": 14,  # 终止频率
                                    "fStartAZ": 0.0,  # ZC起始方位
                                    "fEndAZ": 180.0,  # 侦查终止方位
                                    "fStartEL": 2.0,  # 俯仰起始
                                    "fEndEL": 30.0,  # 俯仰终止
                                }
                        }
                    ],
                    "SetRadarJamTask": [],
                    "SetFreqControl":[
                        {
                            "iProtectRFNum": 1,
                            "pProtectRFInfo": [
                                {
                                    "fStartRF": 6,
                                    "fEndRF": 10
                                }
                            ]
                        }
                    ]
                },  # OldTask, 有保护频段， 1, 搜索, info_manager: RadarNum = 0
                'Step4': {
                    "SetRadarReconTask":[
                        {
                            "SetRadarReconTask":
                                {
                                    "KcgTaskType": 101,  # 101雷达ZC模式  102雷达TC模式 103 电子GR模式   104是一体化模式
                                    "KcgSubTaskType": 2,  # 1表示搜索, 2表示监视
                                    "fStartRF": 12,  # 起始频率
                                    "fEndRF": 14,  # 终止频率
                                    "fStartAZ": 0.0,  # ZC起始方位
                                    "fEndAZ": 180.0,  # 侦查终止方位
                                    "fStartEL": 2.0,  # 俯仰起始
                                    "fEndEL": 30.0,  # 俯仰终止
                                }
                        }
                    ],
                    "SetRadarJamTask": [],
                    "SetFreqControl":[
                        {
                            "iProtectRFNum": 0,
                            "pProtectRFInfo": []
                        }
                    ]
                },  # NewTask, 无保护频段， 2, 监视,
                'Step5': {
                    "SetRadarReconTask":[
                        {
                            "SetRadarReconTask":
                                {
                                    "KcgTaskType": 101,  # 101雷达ZC模式  102雷达TC模式 103 电子GR模式   104是一体化模式
                                    "KcgSubTaskType": 2,  # 1表示搜索, 2表示监视
                                    "fStartRF": 12,  # 起始频率
                                    "fEndRF": 14,  # 终止频率
                                    "fStartAZ": 0.0,  # ZC起始方位
                                    "fEndAZ": 180.0,  # 侦查终止方位
                                    "fStartEL": 2.0,  # 俯仰起始
                                    "fEndEL": 30.0,  # 俯仰终止
                                }
                        }
                    ],
                    "SetRadarJamTask": [],
                    "SetFreqControl":[
                        {
                            "iProtectRFNum": 0,
                            "pProtectRFInfo": []
                        }
                    ]
                }  # OldTask, 无保护， 2, 监视
            },
            "jam_task_info": {
                'Step0': {
                    "SetRadarReconTask": [],
                    "SetRadarJamTask":[
                        {
                            "SetRadarJamTask":
                                {
                                    "KcgTaskType": 103,  # 101 ZC 102 TC 103 GR 104 一体化
                                    "KcgSubTaskType": 1,  # 1表示雷达ZCGR, 2表示强制GR, 3表示自主GR
                                    "TargetID": 1,
                                    "TargetRadius": 1,  # FIXME START 命名确认，重要程度：不重要
                                    # KcgSubTaskType == 2时，会有以下参数，写到RULE内，强制GR时会在任务报文提供这些GR参数
                                    "JamMode": -1,  # 1表示噪声GR, 5表示精瞄频, 6表示梳状谱
                                    "fJamRF": -1,
                                    "fJamSigBW": -1,
                                    "JamPointAZ": -1,
                                    "JamPointEL": -1  # FIXME END
                                }
                        }
                    ],
                    "SetFreqControl":[
                        {
                            "iProtectRFNum": 1,
                            "pProtectRFInfo": [
                                {
                                    "fStartRF": 6,
                                    "fEndRF": 10
                                }
                            ]
                        }
                    ]
                },  # NewTask, RadarNum = 0
                'Step1': {
                    "SetRadarReconTask": [],
                    "SetRadarJamTask":[
                        {
                            "SetRadarJamTask":
                                {
                                    "KcgTaskType": 103,  # 101 ZC 102 TC 103 GR 104 一体化
                                    "KcgSubTaskType": 1,  # 1表示雷达ZCGR, 2表示强制GR, 3表示自主GR
                                    "TargetID": 1,
                                    "TargetRadius": 1,  # FIXME START 命名确认，重要程度：不重要
                                    # KcgSubTaskType == 2时，会有以下参数，写到RULE内，强制GR时会在任务报文提供这些GR参数
                                    "JamMode": -1,  # 1表示噪声GR, 5表示精瞄频, 6表示梳状谱
                                    "fJamRF": -1,
                                    "fJamSigBW": -1,
                                    "JamPointAZ": -1,
                                    "JamPointEL": -1  # FIXME END
                                }
                        }
                    ],
                    "SetFreqControl":[
                        {
                            "iProtectRFNum": 1,
                            "pProtectRFInfo": [
                                {
                                    "fStartRF": 6,
                                    "fEndRF": 10
                                }
                            ]
                        }
                    ]
                },  # OldTask, RadarNum = 0
                'Step2': {
                    "SetRadarReconTask": [],
                    "SetRadarJamTask":[
                        {
                            "SetRadarJamTask":
                                {
                                    "KcgTaskType": 103,  # 101 ZC 102 TC 103 GR 104 一体化
                                    "KcgSubTaskType": 1,  # 1表示雷达ZCGR, 2表示强制GR, 3表示自主GR
                                    "TargetID": 1,
                                    "TargetRadius": 1,  # FIXME START 命名确认，重要程度：不重要
                                    # KcgSubTaskType == 2时，会有以下参数，写到RULE内，强制GR时会在任务报文提供这些GR参数
                                    "JamMode": -1,  # 1表示噪声GR, 5表示精瞄频, 6表示梳状谱
                                    "fJamRF": -1,
                                    "fJamSigBW": -1,
                                    "JamPointAZ": -1,
                                    "JamPointEL": -1  # FIXME END
                                }
                        }
                    ],
                    "SetFreqControl":[
                        {
                            "iProtectRFNum": 1,
                            "pProtectRFInfo": [
                                {
                                    "fStartRF": 6,
                                    "fEndRF": 10
                                }
                            ]
                        }
                    ]
                },  # OldTask, RadarNum = 1
                'Step3': {
                    "SetRadarReconTask": [],
                    "SetRadarJamTask":[
                        {
                            "SetRadarJamTask":
                                {
                                    "KcgTaskType": 103,  # 101 ZC 102 TC 103 GR 104 一体化
                                    "KcgSubTaskType": 1,  # 1表示雷达ZCGR, 2表示强制GR, 3表示自主GR
                                    "TargetID": 1,
                                    "TargetRadius": 1,  # FIXME START 命名确认，重要程度：不重要
                                    # KcgSubTaskType == 2时，会有以下参数，写到RULE内，强制GR时会在任务报文提供这些GR参数
                                    "JamMode": -1,  # 1表示噪声GR, 5表示精瞄频, 6表示梳状谱
                                    "fJamRF": -1,
                                    "fJamSigBW": -1,
                                    "JamPointAZ": -1,
                                    "JamPointEL": -1  # FIXME END
                                }
                        }
                    ],
                    "SetFreqControl":[
                        {
                            "iProtectRFNum": 1,
                            "pProtectRFInfo": [
                                {
                                    "fStartRF": 6,
                                    "fEndRF": 10
                                }
                            ]
                        }
                    ]
                },  # NewTask, RadarNum = 2
                'Step4': {
                    "SetRadarReconTask": [],
                    "SetRadarJamTask":[
                        {
                            "SetRadarJamTask":
                                {
                                    "KcgTaskType": 103,  # 101 ZC 102 TC 103 GR 104 一体化
                                    "KcgSubTaskType": 2,  # 1表示雷达ZCGR, 2表示强制GR, 3表示自主GR
                                    "TargetID": 1,
                                    "TargetRadius": 1,  # FIXME START 命名确认，重要程度：不重要
                                    # KcgSubTaskType == 2时，会有以下参数，写到RULE内，强制GR时会在任务报文提供这些GR参数
                                    "JamMode": 0,  # 1表示噪声GR, 5表示精瞄频, 6表示梳状谱
                                    "fJamRF": 30.0,
                                    "fJamSigBW": 20.0,
                                    "JamPointAZ": 0.0,
                                    "JamPointEL": 0.0  # FIXME END
                                }
                        }
                    ],
                    "SetFreqControl":[
                        {
                            "iProtectRFNum": 1,
                            "pProtectRFInfo": [
                                {
                                    "fStartRF": 6,
                                    "fEndRF": 10
                                }
                            ]
                        }
                    ]
                },  # NewTask, 强制GR
                'Step5': {
                    "SetRadarReconTask": [],
                    "SetRadarJamTask":[
                        {
                            "SetRadarJamTask":
                                {
                                    "KcgTaskType": 103,  # 101 ZC 102 TC 103 GR 104 一体化
                                    "KcgSubTaskType": 2,  # 1表示雷达ZCGR, 2表示强制GR, 3表示自主GR
                                    "TargetID": 1,
                                    "TargetRadius": 1,  # FIXME START 命名确认，重要程度：不重要
                                    # KcgSubTaskType == 2时，会有以下参数，写到RULE内，强制GR时会在任务报文提供这些GR参数
                                    "JamMode": 0,  # 1表示噪声GR, 5表示精瞄频, 6表示梳状谱
                                    "fJamRF": 30.0,
                                    "fJamSigBW": 20.0,
                                    "JamPointAZ": 0.0,
                                    "JamPointEL": 0.0  # FIXME END
                                }
                        }
                    ],
                    "SetFreqControl":[
                        {
                            "iProtectRFNum": 1,
                            "pProtectRFInfo": [
                                {
                                    "fStartRF": 6,
                                    "fEndRF": 10
                                }
                            ]
                        }
                    ]
                }   # OldTask, 强制GR
            }
        }
        self.FreqInfo = {
            "iProtectRFNum": 1,
            "pProtectRFInfo": [{
                "fStartRF": 6,
                "fEndRF": 10
            }]
        }

        self.recon_task_step = [0, 1, 2, 3, 4, 5, 6]
        self.jam_task_step = [0, 1, 2, 3, 4, 4, 6]   # 列表中的数字代表执行step几。

        self.iter = 1

    def Get_Recon_Obs(self, info_manager, pProtectRFInfo) -> np.array(list):
        """
        此函数用来构建LZC任务的观测空间

        Args:
            info_manager(dict): 数据总线
            pProtectRFInfo(list[tuple]): 保护频段
        Returns:
            np.array[list]: ReconAgent定制的网络输入
        Notes:
            返回值形状：
            8 * ParaDeclaration,

            ParaDeclaration = [
                "TargetID",         # 0\n
                "PlatType",         # 1\n
                "AZ",               # 2\n
                "EL",               # 3\n
                "pRF_max",          # 4\n
                "pRF_min",          # 5\n
                "pPRI_max",         # 6\n
                "pPRI_min",         # 7\n
                "pPW_max",          # 8\n
                "pPW_min",          # 9\n
                "DangerClass"       # 10\n
                "CaptureProb"       # 11\n
            ]
        """
        self.ReconObs = [[-1, -1, 0, 0, -1, -1, 0, 0, -1, -1, -1, -1] for _ in range(8)]  # 用非法值初始化，省去不足八个补足八个的逻辑
        self.ProbList = [-1 for _ in range(8)]
        self.TargetIDList = [-1 for _ in range(8)]
        self.MinProbIndex = 0
        self.ObsTop = 0

        reconRadarPara = info_manager.raw_obs.extra_info_dict['obs']['data']['reconRadarPara']
        for ParaIndex in range(len(reconRadarPara)):  # 遍历任务信息
            # 判断是不是我的RADAR数据
            if self.EquipID != reconRadarPara[ParaIndex]['ReconID']:
                continue

            # NOTE 方位可能存在歧义，可能不以东为0，此时要以初始化的基线做基线

            self.myReconID = reconRadarPara[ParaIndex]['ReconID']  # NOTE 设备id，传给ReconRule？
            ReconDetectRadar = reconRadarPara[ParaIndex]['ReconRadarPara']
            RadarNum = reconRadarPara[ParaIndex]['RadarNum']

            for DetectRadar in range(RadarNum):  # DetectRadar:int  遍历所有发现的雷达
                ReconResult = ReconDetectRadar[DetectRadar]['ReconResult']
                DangerClass = ReconDetectRadar[DetectRadar]['DangerClass']
                TargetID = ReconResult['TargetID']
                PlatType = ReconDetectRadar[DetectRadar]['PlatType']
                AZ = ReconResult['AZ']
                EL = ReconResult['EL']
                pRF = copy.deepcopy(ReconResult['pRF'])  # 载频数组
                pPRI = copy.deepcopy(ReconResult['pPRI'])  # 重频数组
                pPRI_max, pPRI_min = (0, 0) if len(pPRI) == 0 else (max(pPRI), min(pPRI))
                pPW = copy.deepcopy(ReconResult['pPW'])  # 脉宽数组
                (pPW_max, pPW_min) = (0, 0) if len(pPW) == 0 else (max(pPW), min(pPW))
                CaptureProb = ReconResult['CaptureProb']

                # 利用保护频段筛选保护频段外的数据
                for i in range(len(pRF)):
                    for protectRFtuple in pProtectRFInfo:
                        if protectRFtuple[0] <= pRF[i] <= protectRFtuple[1]:
                            pRF[i] = -1

                pRF = [RF for RF in pRF if RF != -1]
                if not pRF:
                    continue

                (pRF_max, pRF_min) = (0, 0) if len(pRF) == 0 else (max(pRF), min(pRF))

                ThisRadar = [TargetID, PlatType, AZ, EL, pRF_max, pRF_min, pPRI_max, pPRI_min, pPW_max, pPW_min,
                             DangerClass, CaptureProb]

                # TargetID 相同，这个判断要在最前面，
                if TargetID in self.TargetIDList:
                    if CaptureProb > self.ProbList[self.TargetIDList.index(TargetID)]:
                        SameTargetIndex = self.TargetIDList.index(TargetID)
                        self.ReconObs[SameTargetIndex] = ThisRadar
                        self.ProbList[SameTargetIndex] = CaptureProb
                        self.MinProbIndex = self.ProbList.index(min(self.ProbList[:]))
                    continue

                # 前8个直接入列
                if self.ObsTop < 8:
                    self.ReconObs[self.ObsTop] = ThisRadar
                    self.ProbList[self.ObsTop] = CaptureProb
                    self.TargetIDList[self.ObsTop] = TargetID
                    self.ObsTop += 1
                    if self.ObsTop == 7:
                        self.MinProbIndex = self.ProbList.index(min(self.ProbList[:]))
                    continue

                # 如果CaptureProb 小于目前最小的，跳过
                if CaptureProb < self.ProbList[self.MinProbIndex]:
                    continue

                self.MinProbIndex = self.ProbList.index(min(self.ProbList[:]))  # 更新最小prob的索引
                self.ReconObs[self.MinProbIndex] = ThisRadar  # 用ThisRadar覆盖目前prob最小的Radar
                self.TargetIDList[self.MinProbIndex] = TargetID  # 更新对应行的TargetID
                self.ProbList[self.MinProbIndex] = CaptureProb  # 更新对应行的CaptureProb

        return np.array(self.ReconObs).flatten()

    def Get_Com_Obs(self, info_manager) -> np.array(list):
        """
        此函数用来构建L通信任务的观测空间

        Args:
            info_manager (dict): 数据总线
        Returns:
            list[float]: ComAgent定制的网络输入
        Notes:
            返回值形状：
            8 * ParaDeclaration,

            ParaDeclaration = [
                'TrgID',  # 目标ID\n
                'Bandwidth',  # 带宽\n
                'CMD', # 调制样式\n
                'SignalType', # 目标型号 0未知 1常规定频 2常规跳频 5数据链 5001 11  5004 4A\n
                'InfoType', # 基带信息类型\n
                'startRF',  # 频率最小值mhz\n
                'endRF',  # 频率最大值mhz\n
                'Duration', # 信号持续时间\n
                'fLon', # 目标经度\n
                'fLat', # 目标纬度\n
                'iHopRate',  # 跳速\n
                'FreqNo',  # 频点个数\n
                'FreqSet',  # 频率集\n
                'AZ',  # 目标方位，度\n
                'EL',  # 目标俯仰，度\n
                'fCaptureProb',  # 截获概率 0~1\n
            ]
        """

        self.ComObs = [[-1.0, -1.0, -1.0, -1.0, -1.0, -1.0,
                        -1.0, -1.0, -1.0, -1.0, -1.0, -1.0,
                        -1.0, -1.0, -1.0, -1.0, -1.0] for _ in range(8)]  # 用非法值初始化，省去不足八个补足八个的逻辑
        self.ProbList = [-1 for _ in range(8)]
        self.TrgIDList = [-1 for _ in range(8)]
        self.MinProbIndex = 0
        self.ObsTop = 0

        comDetectPara = info_manager.raw_obs.extra_info_dict['obs']['data']['comMdetectPara']

        for ParaIdx in range(len(comDetectPara)):
            # NOTE 此处是不是取EquipID？
            if self.EquipID != comDetectPara[ParaIdx]['ReconID']:
                continue
            nTrgNum = comDetectPara[ParaIdx]['nTrgNum']
            TrgPara = comDetectPara[ParaIdx]['TrgPara']

            for TrgIdx in range(nTrgNum):
                TrgID = TrgPara[TrgIdx]['TrgID']
                Bandwidth = TrgPara[TrgIdx]['Bandwidth']
                CMD = TrgPara[TrgIdx]['CMD']
                SignalType = TrgPara[TrgIdx]['SignalType']
                InfoType = TrgPara[TrgIdx]['InfoType']
                Duration = TrgPara[TrgIdx]['Duration']
                AZ = TrgPara[TrgIdx]['AZ']  # 目标方位：度
                EL = TrgPara[TrgIdx]['EL']  # 目标俯仰：度
                fLon = TrgPara[TrgIdx]['fLon']  # 目标方位：度
                fLat = TrgPara[TrgIdx]['fLat']  # 目标俯仰：度
                endRF = TrgPara[TrgIdx]['endRF']
                startRF = TrgPara[TrgIdx]['startRF']
                iHopRate = TrgPara[TrgIdx]['iHopRate']
                FreqNo = TrgPara[TrgIdx]['FreqNo']
                FreqSet = copy.deepcopy(TrgPara[TrgIdx]['FreqSet'])
                FreqMax = np.max(FreqSet)
                FreqMin = np.min(FreqSet)
                fCaptureProb = TrgPara[TrgIdx]['fCaptureProb']

                ThisTrg = [TrgID, Bandwidth, CMD, SignalType, InfoType, startRF, endRF,
                           Duration, fLon, fLat, iHopRate, FreqNo, FreqMax, FreqMin, AZ, EL, fCaptureProb]

                # TargetID 相同，这个判断要在最前面，
                if TrgID in self.TrgIDList:
                    if fCaptureProb > self.ProbList[self.TargetIDList.index(TrgID)]:
                        SameTargetIndex = self.TargetIDList.index(TrgID)
                        self.ComObs[SameTargetIndex] = ThisTrg
                        self.ProbList[SameTargetIndex] = fCaptureProb
                        self.MinProbIndex = self.ProbList.index(min(self.ProbList[:]))
                    continue

                # 前8个直接入列
                if self.ObsTop < 8:
                    self.ComObs[self.ObsTop] = ThisTrg
                    self.ProbList[self.ObsTop] = fCaptureProb
                    self.TrgIDList[self.ObsTop] = TrgID
                    self.ObsTop += 1
                    if self.ObsTop == 7:
                        self.MinProbIndex = self.ProbList.index(min(self.ProbList[:]))
                    continue

                # 如果CaptureProb 小于目前最小的，跳过
                if fCaptureProb < self.ProbList[self.MinProbIndex]:
                    continue

                self.MinProbIndex = self.ProbList.index(min(self.ProbList[:]))  # 更新最小prob的索引
                self.ComObs[self.MinProbIndex] = ThisTrg  # 用ThisRadar覆盖目前prob最小的Radar
                self.TrgIDList[self.MinProbIndex] = TrgID  # 更新对应行的TargetID
                self.ProbList[self.MinProbIndex] = fCaptureProb  # 更新对应行的CaptureProb

        return np.array(self.ComObs).flatten()

    def ReconProps(self, IllegalNW=None, silent: bool = False):
        """
        此函数用于构造step函数输出的Recon部分，包括RuleSc， RuleInput, AgentSC, AgentNw

        Args:
            IllegalNW(list): 网络非法值
            silent(bool): 是否为待机状态
        Returns:
            ReconOut(dict)
        """
        if silent:
            ReconOut = {
                "LReconRuleInput": RuleNodeOutput.create_message_output({}),
                "LReconRuleSC": RuleNodeOutput.create_scheduler_output(False),
                "LReconAgentSC": RuleNodeOutput.create_scheduler_output(False),
                "LReconAgentNW": RuleNodeOutput.create_network_output(IllegalNW)
            }
            return ReconOut

        # 如果是旧任务，不作处理，只将上次输出的IsNewTask属性置False即可return
        if not self.NewReconTask:
            self.LastReconOut["LReconRuleInput"]._output["IsNewTask"] = False
            return self.LastReconOut

        DefaultTask = {
            "IsNewTask": True,
            "KcgTaskType": 101,  # 101雷达ZC模式  102雷达TC模式 103 电子GR模式   104是一体化模式
            "KcgSubTaskType": 1,  # 1表示搜索, 2表示监视
            "fStartRF": 6,  # 起始频率
            "fEndRF": 18,  # 终止频率
            "fStartAZ": 0.0,  # ZC起始方位
            "fEndAZ": 180.0,  # 侦查终止方位
            "fStartEL": 2.0,  # 俯仰起始
            "fEndEL": 30.0,  # 俯仰终止
        }

        ReconTaskInfo = self.LastReconTask if self.LastReconTask else DefaultTask

        raw_LReconRuleSC = True
        raw_LReconAgentSC = True

        raw_LReconRuleInput = {
            'IsNewTask': self.NewReconTask,
            "KcgTaskType": ReconTaskInfo['KcgTaskType'],
            "KcgSubTaskType": ReconTaskInfo['KcgSubTaskType'],
            "fStartRF": ReconTaskInfo['fStartRF'],
            "fEndRF": ReconTaskInfo['fEndRF'],
            "fStartEL": ReconTaskInfo['fStartEL'],
            "fEndEL": ReconTaskInfo['fEndEL'],
            "fStartAZ": ReconTaskInfo['fStartAZ'],
            "fEndAZ": ReconTaskInfo['fEndAZ'],
            "iProtectRFNum": self.FreqInfo['iProtectRFNum'],
            "pProtectRFInfo": [tuple(dict1.values()) for dict1 in self.FreqInfo['pProtectRFInfo']] \
                if len(self.FreqInfo['pProtectRFInfo']) > 0 else [],  # 保护
        }

        raw_LReconAgentNW = list(np.concatenate([self.Get_Recon_Obs(info_manager, raw_LReconRuleInput['pProtectRFInfo']),
                                      self.Get_Com_Obs(info_manager)]))

        ReconOut = {
            "LReconRuleInput": RuleNodeOutput.create_message_output(raw_LReconRuleInput),
            "LReconRuleSC": RuleNodeOutput.create_scheduler_output(raw_LReconRuleSC),
            "LReconAgentSC": RuleNodeOutput.create_scheduler_output(raw_LReconAgentSC),
            "LReconAgentNW": RuleNodeOutput.create_network_output(raw_LReconAgentNW),
        }

        return ReconOut

    def JamProps(self, IllegalNW = None, silent: bool = False):
        """
        此函数用于构造step函数输出的Jam部分，包括RuleSc, RuleInput, AgentSC, AgentNw

        Args:
            IllegalNW(list): 网络非法值
            silent(bool): 是否处于待机状态
        Returns:
            JamProps(dict)
        """
        if silent:
            JamOut = {
                "LJamRuleInput": RuleNodeOutput.create_message_output({}),
                "LJamRuleSC": RuleNodeOutput.create_scheduler_output(False),
                "LJamAgentSC": RuleNodeOutput.create_scheduler_output(False),
                "LJamAgentNW": RuleNodeOutput.create_network_output(IllegalNW)
            }
            return JamOut

        # 如果是旧任务，不作处理，只将上次输出的IsNewTask属性置False即可return
        if not self.NewJamTask:
            self.LastJamOut["LJamRuleInput"]._output["IsNewTask"] = False
            return self.LastJamOut

        raw_LJamRuleSC = True
        raw_LJamAgentSC = True

        raw_LJamRuleInput = {
            'IsNewTask': self.NewJamTask,
            "KcgTaskType": self.LastJamTask['KcgTaskType'],
            "KcgSubTaskType": self.LastJamTask['KcgSubTaskType'],  # FIXME
            "JamMode": self.LastJamTask['JamMode'],  # 1表示噪声GR, 5表示精瞄频, 6表示梳状谱
            "fJamRF": self.LastJamTask['fJamRF'],
            "fJamSigBW": self.LastJamTask['fJamSigBW'],
            "JamPointAZ": self.LastJamTask['JamPointAZ'],
            "JamPointEL": self.LastJamTask['JamPointEL'],  # FIXME END
            "iProtectRFNum": self.FreqInfo['iProtectRFNum'],
            "pProtectRFInfo": [tuple(dict1.values()) for dict1 in self.FreqInfo['pProtectRFInfo']] \
                if len(self.FreqInfo['pProtectRFInfo']) > 0 else [],  # 保护
        }

        raw_LJamAgentNW = list(np.concatenate([self.Get_Recon_Obs(info_manager, raw_LJamRuleInput['pProtectRFInfo']),
                                      self.Get_Com_Obs(info_manager)]))

        JamOut = {
            "LJamRuleInput": RuleNodeOutput.create_message_output(raw_LJamRuleInput),
            "LJamRuleSC": RuleNodeOutput.create_scheduler_output(raw_LJamRuleSC),
            "LJamAgentSC": RuleNodeOutput.create_scheduler_output(raw_LJamAgentSC),
            "LJamAgentNW": RuleNodeOutput.create_network_output(raw_LJamAgentNW),
        }

        self.LastJamOut = JamOut

        return JamOut

    def step(self, info_manager, message, blackboard=None):
        """
        LTaskControl的step函数

        Args:
            info_manager(dict): 数据总线,
            blackboard: ,
            message: 上游props,
        Returns:
            cmds, NodeResult, output
        """
        task_info = self.task_manager["recon_task_info"][f"Step{self.recon_task_step[self.iter]}"]
        # task_info = self.task_manager["jam_task_info"][f"Step{self.jam_task_step[self.iter]}"]

        # self.iter += 1 if self.iter < len(self.recon_task_step) else -(len(self.recon_task_step)-1)
        self.iter += 1 if self.iter < len(self.jam_task_step) else -(len(self.jam_task_step)-1)

        # 预处理
        IllegalNW = list(np.concatenate([
            np.array([[-1.0, -1.0, 0.0, 0.0, -1.0, -1.0, 0.0, 0.0, -1.0, -1.0, -1.0, -1.0]
                      for _ in range(8)], dtype=object).flatten(),
            np.array([[-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0,
                       -1.0, -1.0, -1.0, -1.0, -1.0]
                      for _ in range(8)], dtype=object).flatten()
        ]))
        # print(f"IllegalNW:{len(IllegalNW)}")  # 232

        LReconTaskExist: bool = ("SetRadarReconTask" in task_info.keys() and
                                 len(task_info["SetRadarReconTask"]) > 0)  # L有ZC任务
        LJamTaskExist: bool = ("SetRadarJamTask" in task_info.keys() and
                               len(task_info["SetRadarJamTask"]) > 0)  # L有GR任务

        self.EquipID = Get_EquipID(info_manager)
        assert self.EquipID and self.EquipID != -1, "Invalid EquipID"

        if self.EquipID == None:
            raise(KeyError("EquipID is not Exist in info_manager"))

        if self.LastReconTask == None:
            if LReconTaskExist:
                self.LastReconTask = task_info["SetRadarReconTask"][0]["SetRadarReconTask"]
                self.NewReconTask = True
        else:
            if not LReconTaskExist or self.LastReconTask == task_info["SetRadarReconTask"][0]["SetRadarReconTask"]:
                self.NewReconTask = False
            else:
                self.LastReconTask = task_info["SetRadarReconTask"][0]["SetRadarReconTask"]
                self.NewReconTask = True

        if self.LastJamTask == None:
            if LJamTaskExist:
                self.LastJamTask = task_info["SetRadarJamTask"][0]["SetRadarJamTask"]
                self.NewJamTask = True
        else:
            if not LJamTaskExist or self.LastJamTask == task_info["SetRadarJamTask"][0]["SetRadarJamTask"]:
                self.NewJamTask = False
            else:
                self.LastJamTask = task_info["SetRadarJamTask"][0]["SetRadarJamTask"]
                self.NewJamTask = True

        # NOTE: 这里结束，所有的Last都是Latest

        if self.LastJamTask:
            if int(task_info["SetRadarJamTask"][0]["SetRadarJamTask"]["KcgSubTaskType"]) == 2:
                if self.NewJamTask:
                    self.JamValid = True
            elif int(task_info["SetRadarJamTask"][0]["SetRadarJamTask"]["KcgSubTaskType"]) == 1:
                if self.NewJamTask:
                    self.JamValid = True
                    self.NeedRecon = True
                    self.NewReconTask = True

        if self.LastReconTask:
            self.ReconValid = True

        elif self.NeedRecon:
            self.ReconValid = True

        self.LastReconOut = self.ReconProps() if self.ReconValid else self.ReconProps(IllegalNW=IllegalNW, silent=True)
        self.LastJamOut = self.JamProps() if self.JamValid else self.JamProps(IllegalNW=IllegalNW, silent=True)
        output = {}
        output.update(self.LastReconOut)
        output.update(self.LastJamOut)

        return [], BehaviorTreeNodeResult.SUCCESS, output

if __name__ == '__main__':
    from DictDisplay import MyDict
    import json

    LTaskControler = LTaskControl()
    with open('../local_bt_actions/info_manager_for_LTC.json', 'r', encoding='utf-8') as f:
        info_manager = json.load(f)
    # Recon + Jam
    _, _, output = LTaskControler.step(info_manager=info_manager, blackboard=None, message=None)
    myDict = MyDict(output)
    print('------------------------>@output:\n')
    myDict.show()
    print('\n')
    # Recon
    _, _, OutputnoJam = LTaskControler.step(info_manager=info_manager, blackboard=None, message=None)
    myDicTnoJam = MyDict(OutputnoJam)
    print('------------------------>@OutputnoJam:\n')
    myDicTnoJam.show()
    print('\n')
    # Jam
    _, _, OutputnoRecon = LTaskControler.step(info_manager=info_manager, blackboard=None, message=None)
    myDicTnoRecon = MyDict(OutputnoRecon)
    print('------------------------>@OutputnoRecon:\n')
    myDicTnoRecon.show()
    print('\n')
