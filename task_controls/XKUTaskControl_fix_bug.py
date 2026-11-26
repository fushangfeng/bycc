from bycc.agent.config_def import BehaviorTreeNodeResult
from bycc.agent.behavior_tree.nodes.bt_action import BTAction
from bycc.common.data_interface import RuleNodeOutput

# from FakeImport import BehaviorTreeNodeResult, BTAction, RuleNodeOutput     # 测试用

import numpy as np
import copy
from env_interface.utils.GetData import Get_EquipID

DECLARATION = {
    "name": "XKU任务控制",  # 组件名称，用于前端显示和后台索引
    "class": "XKUTaskControl",  # 组件类名
    "params": {},
    "description": "XKU任务控制组件"
}


class XKUTaskControl(BTAction):
    """
    XKU任务控制模块

    Methods:
        step(
            info_manager(dict): 数据总线
            blackboard(dict):   全局变量池
            message(dict):     上游组件的props
            task_info(dict):    任务报文
        )  ->  list, Enum, dict
    """

    def __init__(self):
        super().__init__()
        self.LastReconTask = None
        self.LastJamTask = None
        self.LastReconOut = None
        self.LastJamOut = None

        self.NeedRecon = False
        self.ReconValid = False
        self.JamValid = False
        self.EqupID = None
        # NOTE task_info本应该从info_manager中获取 但目前info_manager中没有 所以暂存为self属性处理
        # NOTE 目前只能人为区分jam和recon下的task_info进行测试

        self.task_manager = {
            "recon_task_info": {
                'Step0': {  # NewTask
                    "SetRadarReconTask": [
                        {
                            "SetRadarReconTask":
                                {
                                    "KcgTaskType": 201,  # 201雷达侦察模式  202雷达干扰模式 203 对星对抗模式   201和202是对机  203是对星
                                    "KcgSubTaskType": 1,  # 1表示搜索, 2表示监视
                                    "fStartRF": 12,  # 起始频率
                                    "fEndRF": 14,  # 终止频率
                                    "fStartAZ": 0.0,  # 侦察起始方位
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
                            "pProtectRFInfo": [
                                {
                                    "fStartRF": 6,
                                    "fEndRF": 10
                                }
                            ]
                        }
                    ]
                },  # NewTask, 有保护频段， 1, 搜索
                'Step1': {  # NoTask
                    "SetRadarReconTask": [
                        # {
                        #     "SetRadarReconTask":
                        #     {
                        #         "KcgTaskType":201, # 201雷达侦察模式  202雷达干扰模式 203 对星对抗模式   201和202是对机  203是对星
                        #         "KcgSubTaskType": 1, # 1表示搜索, 2表示监视
                        #         "fStartRF": 12,  #起始频率
                        #         "fEndRF": 14,  # 终止频率
                        #         "fStartAZ": 0.0,  # 侦察起始方位
                        #         "fEndAZ": 180.0, # 侦查终止方位
                        #         "fStartEL": 2.0,   # 俯仰起始
                        #         "fEndEL": 30.0,   # 俯仰终止
                        #     }
                        # }
                    ],
                    "SetRadarJamTask": [],
                    "SetFreqControl": [
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
                },  # NoTask
                'Step2': {  # OldTask
                    "SetRadarReconTask": [
                        {
                            "SetRadarReconTask":
                                {
                                    "KcgTaskType": 201,  # 201雷达侦察模式  202雷达干扰模式 203 对星对抗模式   201和202是对机  203是对星
                                    "KcgSubTaskType": 1,  # 1表示搜索, 2表示监视
                                    "fStartRF": 12,  # 起始频率
                                    "fEndRF": 14,  # 终止频率
                                    "fStartAZ": 0.0,  # 侦察起始方位
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
                            "pProtectRFInfo": [
                                {
                                    "fStartRF": 6,
                                    "fEndRF": 10
                                }
                            ]
                        }
                    ]
                },  # OldTask, 有保护频段， 1, 搜索
                'Step3': {  # NewTask
                    "SetRadarReconTask": [
                        {
                            "SetRadarReconTask":
                                {
                                    "KcgTaskType": 201,  # 201雷达侦察模式  202雷达干扰模式 203 对星对抗模式   201和202是对机  203是对星
                                    "KcgSubTaskType": 2,  # 1表示搜索, 2表示监视
                                    "fStartRF": 12,  # 起始频率
                                    "fEndRF": 14,  # 终止频率
                                    "fStartAZ": 0.0,  # 侦察起始方位
                                    "fEndAZ": 180.0,  # 侦查终止方位
                                    "fStartEL": 2.0,  # 俯仰起始
                                    "fEndEL": 30.0,  # 俯仰终止
                                }
                        }
                    ],
                    "SetRadarJamTask": [],
                    "SetFreqControl": [
                        {
                            "iProtectRFNum": 0,
                            "pProtectRFInfo": []
                        }
                    ]
                },  # NewTask, 无保护频段， 2, 监视
                'Step4': {  # NoTask
                    "SetRadarReconTask": [
                        # {
                        #     "SetRadarReconTask":
                        #     {
                        #         "KcgTaskType":201, # 201雷达侦察模式  202雷达干扰模式 203 对星对抗模式   201和202是对机  203是对星
                        #         "KcgSubTaskType": 2, # 1表示搜索, 2表示监视
                        #         "fStartRF": 12,  #起始频率
                        #         "fEndRF": 14,  # 终止频率
                        #         "fStartAZ": 0.0,  # 侦察起始方位
                        #         "fEndAZ": 180.0, # 侦查终止方位
                        #         "fStartEL": 2.0,   # 俯仰起始
                        #         "fEndEL": 30.0,   # 俯仰终止
                        #     }
                        # }
                    ],
                    "SetRadarJamTask": [],
                    "SetFreqControl": [
                        {
                            "iProtectRFNum": 0,
                            "pProtectRFInfo": []
                        }
                    ]
                },  # NoTask
                'Step5': {  # NoTask
                    "SetRadarReconTask": [
                        {
                            "SetRadarReconTask":
                                {
                                    "KcgTaskType": 201,  # 201雷达侦察模式  202雷达干扰模式 203 对星对抗模式   201和202是对机  203是对星
                                    "KcgSubTaskType": 2,  # 1表示搜索, 2表示监视
                                    "fStartRF": 12,  # 起始频率
                                    "fEndRF": 14,  # 终止频率
                                    "fStartAZ": 0.0,  # 侦察起始方位
                                    "fEndAZ": 180.0,  # 侦查终止方位
                                    "fStartEL": 2.0,  # 俯仰起始
                                    "fEndEL": 30.0,  # 俯仰终止
                                }
                        }
                    ],
                    "SetRadarJamTask": [],
                    "SetFreqControl": [
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
                    "SetRadarJamTask":
                        [
                            {
                                "SetRadarJamTask":
                                    {
                                        "KcgTaskType": 202,  # 201雷达侦察模式  202雷达干扰模式 203 对星对抗模式   201和202是对机  203是对星
                                        "KcgSubTaskType": 1,  # 1表示雷达侦察干扰, 2表示强制干扰, 3表示自主干扰
                                        "TargetID": 1,
                                        "TargetRadius": 1,  # FIXME START 命名确认，重要程度：不重要
                                        # KcgSubTaskType == 2时，会有以下参数，写到RULE内，强制干扰时会在任务报文提供这些干扰参数
                                        "JamMode": -1,  # 1表示噪声干扰, 5表示精瞄频, 6表示梳状谱
                                        "fJamRF": -1,
                                        "fJamSigBW": -1,
                                        "JamPointAZ": -1,
                                        "JamPointEL": -1  # FIXME END
                                    }
                            }
                        ],
                    "SetFreqControl":
                        [
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
                },  # ZSNewTask
                'Step1': {
                    "SetRadarReconTask": [],
                    "SetRadarJamTask":
                        [
                            {
                                "SetRadarJamTask":
                                    {
                                        "KcgTaskType": 202,  # 201雷达侦察模式  202雷达干扰模式 203 对星对抗模式   201和202是对机  203是对星
                                        "KcgSubTaskType": 1,  # 1表示雷达侦察干扰, 2表示强制干扰, 3表示自主干扰
                                        "TargetID": 1,
                                        "TargetRadius": 1,  # FIXME START 命名确认，重要程度：不重要
                                        # KcgSubTaskType == 2时，会有以下参数，写到RULE内，强制干扰时会在任务报文提供这些干扰参数
                                        "JamMode": -1,  # 1表示噪声干扰, 5表示精瞄频, 6表示梳状谱
                                        "fJamRF": -1,
                                        "fJamSigBW": -1,
                                        "JamPointAZ": -1,
                                        "JamPointEL": -1  # FIXME END
                                    }
                            }
                        ],
                    "SetFreqControl":
                        [
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
                },  # ZSOldTask
                'Step2': {
                    "SetRadarReconTask": [],
                    "SetRadarJamTask":
                        [
                            {
                                "SetRadarJamTask":
                                    {
                                        "KcgTaskType": 202,  # 201雷达侦察模式  202雷达干扰模式 203 对星对抗模式   201和202是对机  203是对星
                                        "KcgSubTaskType": 1,  # 1表示雷达侦察干扰, 2表示强制干扰, 3表示自主干扰
                                        "TargetID": 1,
                                        "TargetRadius": 1,  # FIXME START 命名确认，重要程度：不重要
                                        # KcgSubTaskType == 2时，会有以下参数，写到RULE内，强制干扰时会在任务报文提供这些干扰参数
                                        "JamMode": -1,  # 1表示噪声干扰, 5表示精瞄频, 6表示梳状谱
                                        "fJamRF": -1,
                                        "fJamSigBW": -1,
                                        "JamPointAZ": -1,
                                        "JamPointEL": -1  # FIXME END
                                    }
                            }
                        ],
                    "SetFreqControl":
                        [
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
                },  # ZSOldTask
                'Step3': {
                    "SetRadarReconTask": [],
                    "SetRadarJamTask":
                        [
                            {
                                "SetRadarJamTask":
                                    {
                                        "BeNew": 1,
                                        "KcgTaskType": 202,  # 201雷达侦察模式  202雷达干扰模式 203 对星对抗模式   201和202是对机  203是对星
                                        "KcgSubTaskType": 1,  # 1表示雷达侦察干扰, 2表示强制干扰, 3表示自主干扰
                                        "TargetID": 1,
                                        "TargetRadius": 1,  # FIXME START 命名确认，重要程度：不重要
                                        # KcgSubTaskType == 2时，会有以下参数，写到RULE内，强制干扰时会在任务报文提供这些干扰参数
                                        "JamMode": -1,  # 1表示噪声干扰, 5表示精瞄频, 6表示梳状谱
                                        "fJamRF": -1,
                                        "fJamSigBW": -1,
                                        "JamPointAZ": -1,
                                        "JamPointEL": -1  # FIXME END
                                    }
                            }
                        ],
                    "SetFreqControl":
                        [
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
                },  # ZSNewTask
                'Step4': {
                    "SetRadarReconTask": [],
                    "SetRadarJamTask":
                        [
                            {
                                # 新任务 --》 强制
                                "SetRadarJamTask":
                                    {
                                        "KcgTaskType": 202,  # 201雷达侦察模式  202雷达干扰模式 203 对星对抗模式   201和202是对机  203是对星
                                        "KcgSubTaskType": 2,  # 1表示雷达侦察干扰, 2表示强制干扰, 3表示自主干扰
                                        "TargetID": 1,
                                        "TargetRadius": 1,  # FIXME START 命名确认，重要程度：不重要
                                        # KcgSubTaskType == 2时，会有以下参数，写到RULE内，强制干扰时会在任务报文提供这些干扰参数
                                        "JamMode": 0,  # 1表示噪声干扰, 5表示精瞄频, 6表示梳状谱
                                        "fJamRF": 30.0,
                                        "fJamSigBW": 20.0,
                                        "JamPointAZ": 10.0,
                                        "JamPointEL": 25.0  # FIXME END
                                    }
                                # 新任务 --》 雷侦
                                # "SetRadarJamTask":
                                # {
                                #     "KcgTaskType":201, # 201雷达侦察模式  202雷达干扰模式 203 对星对抗模式   201和202是对机  203是对星
                                #     "KcgSubTaskType": 2, # 1表示雷达侦察干扰, 2表示强制干扰, 3表示自主干扰
                                #     "TargetID": 1,
                                #     "TargetRadius": 1,  # FIXME START 命名确认，重要程度：不重要
                                #     # KcgSubTaskType == 2时，会有以下参数，写到RULE内，强制干扰时会在任务报文提供这些干扰参数
                                #     "JamMode": 0,      # 1表示噪声干扰, 5表示精瞄频, 6表示梳状谱
                                #     "fJamRF": 30.0,
                                #     "fJamSigBW": 20.0,
                                #     "JamPointAZ": 0.0,
                                #     "JamPointEL": 0.0      # FIXME END
                                # }
                            }
                        ],
                    "SetFreqControl":
                        [
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
                },  # ZSNewTask, 强制干扰
                'Step5': {
                    "SetRadarReconTask": [],
                    "SetRadarJamTask":
                        [
                            {
                                # 新任务 --》 强制
                                "SetRadarJamTask":
                                    {
                                        "KcgTaskType": 202,  # 201雷达侦察模式  202雷达干扰模式 203 对星对抗模式   201和202是对机  203是对星
                                        "KcgSubTaskType": 2,  # 1表示雷达侦察干扰, 2表示强制干扰, 3表示自主干扰
                                        "TargetID": 1,
                                        "TargetRadius": 1,  # FIXME START 命名确认，重要程度：不重要
                                        # KcgSubTaskType == 2时，会有以下参数，写到RULE内，强制干扰时会在任务报文提供这些干扰参数
                                        "JamMode": 0,  # 1表示噪声干扰, 5表示精瞄频, 6表示梳状谱
                                        "fJamRF": 30.0,
                                        "fJamSigBW": 20.0,
                                        "JamPointAZ": 0.0,
                                        "JamPointEL": 0.0  # FIXME END
                                    }
                                # 新任务 --》 雷侦
                                # "SetRadarJamTask":
                                # {
                                #     "KcgTaskType":201, # 201雷达侦察模式  202雷达干扰模式 203 对星对抗模式   201和202是对机  203是对星
                                #     "KcgSubTaskType": 2, # 1表示雷达侦察干扰, 2表示强制干扰, 3表示自主干扰
                                #     "TargetID": 1,
                                #     "TargetRadius": 1,  # FIXME START 命名确认，重要程度：不重要
                                #     # KcgSubTaskType == 2时，会有以下参数，写到RULE内，强制干扰时会在任务报文提供这些干扰参数
                                #     "JamMode": 0,      # 1表示噪声干扰, 5表示精瞄频, 6表示梳状谱
                                #     "fJamRF": 30.0,
                                #     "fJamSigBW": 20.0,
                                #     "JamPointAZ": 0.0,
                                #     "JamPointEL": 0.0      # FIXME END
                                # }
                            }
                        ],
                    "SetFreqControl":
                        [
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
                },  # ZSOldTask, 强制干扰
            },
            "task_info": {
                'Step0': {
                    "SetRadarReconTask": [
                        {
                            "SetRadarReconTask":
                                {
                                    "KcgTaskType": 201,  # 201雷达侦察模式  202雷达干扰模式 203 对星对抗模式   201和202是对机  203是对星
                                    "KcgSubTaskType": 1,  # 1表示搜索, 2表示监视
                                    "fStartRF": 6000,  # 起始频率
                                    "fEndRF": 18000,  # 终止频率
                                    "fStartAZ": 0.0,  # 侦察起始方位
                                    "fEndAZ": 180.0,  # 侦查终止方位
                                    "fStartEL": 2.0,  # 俯仰起始
                                    "fEndEL": 30.0,  # 俯仰终止
                                }
                        }
                    ],
                    "SetRadarJamTask":
                        [
                            {
                                "SetRadarJamTask":
                                    {
                                        "KcgTaskType": 202,  # 201雷达侦察模式  202雷达干扰模式 203 对星对抗模式   201和202是对机  203是对星
                                        "KcgSubTaskType": 1,  # 1表示雷达侦察干扰, 2表示强制干扰, 3表示自主干扰
                                        "TargetID": 1,
                                        "TargetRadius": 1,  # FIXME START 命名确认，重要程度：不重要
                                        # KcgSubTaskType == 2时，会有以下参数，写到RULE内，强制干扰时会在任务报文提供这些干扰参数
                                        "JamMode": -1,  # 1表示噪声干扰, 5表示精瞄频, 6表示梳状谱
                                        "fJamRF": -1,
                                        "fJamSigBW": -1,
                                        "JamPointAZ": -1,
                                        "JamPointEL": -1  # FIXME END
                                    }
                            }
                        ],
                    "SetFreqControl":
                        [
                            {
                                "iProtectRFNum": 0,
                                "pProtectRFInfo": [
                                    # {
                                    #     "fStartRF": ,
                                    #     "fEndRF": 10
                                    # }
                                ]
                            }
                        ]
                },
                'Step1': {
                    "SetRadarReconTask": [
                        {
                            "SetRadarReconTask":
                                {
                                    "KcgTaskType": 201,  # 201雷达侦察模式  202雷达干扰模式 203 对星对抗模式   201和202是对机  203是对星
                                    "KcgSubTaskType": 1,  # 1表示搜索, 2表示监视
                                    "fStartRF": 6000,  # 起始频率
                                    "fEndRF": 18000,  # 终止频率
                                    "fStartAZ": 0.0,  # 侦察起始方位
                                    "fEndAZ": 180.0,  # 侦查终止方位
                                    "fStartEL": 2.0,  # 俯仰起始
                                    "fEndEL": 30.0,  # 俯仰终止
                                }
                        }
                    ],
                    "SetRadarJamTask":
                        [
                            {
                                "SetRadarJamTask":
                                    {
                                        "KcgTaskType": 202,  # 201雷达侦察模式  202雷达干扰模式 203 对星对抗模式   201和202是对机  203是对星
                                        "KcgSubTaskType": 1,  # 1表示雷达侦察干扰, 2表示强制干扰, 3表示自主干扰
                                        "TargetID": 1,
                                        "TargetRadius": 1,  # FIXME START 命名确认，重要程度：不重要
                                        # KcgSubTaskType == 2时，会有以下参数，写到RULE内，强制干扰时会在任务报文提供这些干扰参数
                                        "JamMode": -1,  # 1表示噪声干扰, 5表示精瞄频, 6表示梳状谱
                                        "fJamRF": -1,
                                        "fJamSigBW": -1,
                                        "JamPointAZ": -1,
                                        "JamPointEL": -1  # FIXME END
                                    }
                            }
                        ],
                    "SetFreqControl":
                        [
                            {
                                "iProtectRFNum": 0,
                                "pProtectRFInfo": [
                                    # {
                                    #     "fStartRF": ,
                                    #     "fEndRF": 10
                                    # }
                                ]
                            }
                        ]
                }
            }
        }

        self.FreqInfo = {
            "iProtectRFNum": 0,
            "pProtectRFInfo": [
                # {
                #     "fStartRF": 6,
                #     "fEndRF": 10
                # }
            ]
        }
        # Note 侦察测试报文
        #  新侦察任务 -> 无任务 -> 旧侦察任务 -> 新监视任务 -> 无任务 -> 旧监视任务 1, 2, 3, 4, 5, 6
        # self.recon_task_step = [0, 1, 2, 3, 4, 5]
        self.recon_task_step = [0, 0, 2, 0]

        self.jam_task_step = [0, 5, 0, 0, 0, 0]  # 列表中的数字代表执行step几。

        self.task_step = [0, 1]
        self.iter = 0

    def step(self, info_manager, message, blackboard=None):
        """
        XKUTaskControl的step函数

        Args:
            info_manager(dict): 数据总线,
            blackboard: ,
            message: 上游props,
        Returns:
            cmds, NodeResult, output
        """
        # task_info = self.task_manager["recon_task_info"][f"Step{self.recon_task_step[self.iter]}"]
        # task_info = self.task_manager["jam_task_info"][f"Step{self.jam_task_step[self.iter]}"]
        task_info = self.task_manager["task_info"][f"Step{self.task_step[self.iter]}"]
        # self.iter += 1 if self.iter < len(self.recon_task_step) else -(len(self.recon_task_step)-1)
        # self.iter += 1 if self.iter < len(self.jam_task_step) else -(len(self.jam_task_step)-1)
        self.iter += 1 if self.iter == 0 else 0

        # 预处理
        # 初始化网络非法值

        IllegalNW = list(np.array([[-1, -1, 0, 0, -1, -1, 0, 0, -1, -1, -1, -1] for _ in range(8)]).flatten())
        # print(f"IllegalNW:{len(IllegalNW)}")   96

        # NOTE 将IllegalNW写成单个网络

        # 检查当前轮是否收到了侦察任务
        XKUReconTaskExist: bool = ("SetRadarReconTask" in task_info.keys() and
                                   len(task_info["SetRadarReconTask"]) > 0)  # XKU是否有侦察任务
        # 检查当前轮次是否收到了干扰任务
        XKUJamTaskExist: bool = ("SetRadarJamTask" in task_info.keys() and
                                 len(task_info["SetRadarJamTask"]) > 0)  # XKU是否有干扰任务

        self.EqupID = Get_EquipID(info_manager)
        assert self.EqupID and self.EqupID != -1, "Invalid EqupID"

        # 判断前面所有轮的
        if self.LastReconTask == None:
            if XKUReconTaskExist:  # 最新的任务，第一次收到任务
                self.LastReconTask = task_info["SetRadarReconTask"][0]["SetRadarReconTask"]  # 直接复制并跳过
                self.NewReconTask = True  # 方便理解
        else:  # 有过任务
            if not XKUReconTaskExist or self.LastReconTask == task_info["SetRadarReconTask"][0][
                "SetRadarReconTask"]:  # 执行旧任务
                self.NewReconTask = False  # 标记为旧任务
            else:  # 执行新任务
                # 当前轮
                self.LastReconTask = task_info["SetRadarReconTask"][0]["SetRadarReconTask"]
                self.NewReconTask = True  # 标记为新任务
        # NOTE 其实self.LastReconTask走过上诉判断后将保持为最新任务

        if self.LastJamTask == None:
            if XKUJamTaskExist:
                self.LastJamTask = task_info["SetRadarJamTask"][0]["SetRadarJamTask"]
                self.NewJamTask = True
        else:
            if not XKUJamTaskExist or self.LastJamTask == task_info["SetRadarJamTask"][0]["SetRadarJamTask"]:
                self.NewJamTask = False
            else:
                self.LastJamTask = task_info["SetRadarJamTask"][0]["SetRadarJamTask"]
                self.NewJamTask = True
        # NOTE 同上

        if self.LastJamTask:  # 如果有干扰任务， NOTE: 还有一个干扰持续时间的说法，可能需要定时清楚LastJamTask为None, LastReconTask同理。
            if int(task_info["SetRadarJamTask"][0]["SetRadarJamTask"]["KcgSubTaskType"]) == 2:  # 强制干扰
                if self.NewJamTask:  # 新任务， 重新构造JamOut
                    self.JamValid = True
                    # self.NeedRecon = False   # TODO 前面侦察在开，收到强干需要关闭侦察吗？
            elif int(task_info["SetRadarJamTask"][0]["SetRadarJamTask"]["KcgSubTaskType"]) == 1:
                if self.NewJamTask:
                    self.JamValid = True
                    self.NeedRecon = True
                    self.NewReconTask = True

        if self.LastReconTask:
            self.ReconValid = True

        elif self.NeedRecon:
            self.ReconValid = True

        self.LastReconOut = self.ReconProps(info_manager) if self.ReconValid else self.ReconProps(info_manager,
                                                                                                  IllegalNW=IllegalNW,
                                                                                                  silent=True)
        self.LastJamOut = self.JamProps(info_manager) if self.JamValid else self.JamProps(info_manager,
                                                                                          IllegalNW=IllegalNW,
                                                                                          silent=True)
        output = {}
        output.update(self.LastReconOut)
        output.update(self.LastJamOut)

        return [], BehaviorTreeNodeResult.SUCCESS, output

    def Get_Recon_Obs(self, info_manager, pProtectRFInfo):
        """
        此函数用来构建XKU侦察任务的观测空间

        Args:
            info_manager (dict): 数据总线
            pProtectRFInfo(list[tuple]): 保护频段
        Returns:
            list[list]: ReconAgent定制的网络输入
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
        self.DangerClassList = [-1 for _ in range(8)]
        self.ProbList = [-1 for _ in range(8)]
        self.TargetIDList = [-1 for _ in range(8)]
        self.MinProbIndex = 0
        self.ObsTop = 0

        reconRadarPara = info_manager.raw_obs.extra_info_dict['obs']['data']['reconRadarPara']
        for ParaIndex in range(len(reconRadarPara)):  # 遍历任务信息
            # 判断是不是我的RADAR数据
            if self.EqupID != reconRadarPara[ParaIndex]['ReconID']:
                continue

            # NOTE 方位可能存在歧义，以正北为0，此时要以初始化的基线做基线

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
                if pRF == []:
                    continue

                (pRF_max, pRF_min) = (0, 0) if len(pRF) == 0 else (max(pRF), min(pRF))

                ThisRadar = [TargetID, PlatType, AZ, EL, pRF_max, pRF_min, pPRI_max, pPRI_min, pPW_max, pPW_min,
                             DangerClass, CaptureProb]

                # TargetID 相同，这个判断要在最前面，
                if TargetID in self.TargetIDList:
                    # 同一目标的威胁等级发生变化，优先级更高
                    if DangerClass < self.DangerClassList[self.TargetIDList.index(TargetID)]:
                        SameTargetIndex = self.TargetIDList.index(TargetID)
                        self.ReconObs[SameTargetIndex] = ThisRadar
                        self.DangerClassList[SameTargetIndex] = DangerClass
                        self.ProbList[SameTargetIndex] = CaptureProb
                        # self.MaxDangerClassIndex = self.DangerClassList.index(max(self.DangerClassList[:]))
                        # self.MinProbIndex = self.ProbList.index(min(self.ProbList[:]))
                    elif DangerClass == self.DangerClassList[self.TargetIDList.index(TargetID)]:
                        if CaptureProb > self.ProbList[self.TargetIDList.index(TargetID)]:
                            SameTargetIndex = self.TargetIDList.index(TargetID)
                            self.ReconObs[SameTargetIndex] = ThisRadar
                            self.ProbList[SameTargetIndex] = CaptureProb
                            # self.MaxDangerClassIndex = self.DangerClassList.index(max(self.DangerClassList[:]))
                            # self.MinProbIndex = self.ProbList.index(min(self.ProbList[:]))
                    continue

                # 前8个直接入列
                if self.ObsTop < 8:
                    self.ReconObs[self.ObsTop] = ThisRadar
                    self.DangerClassList[self.ObsTop] = DangerClass
                    self.ProbList[self.ObsTop] = CaptureProb
                    self.TargetIDList[self.ObsTop] = TargetID
                    self.ObsTop += 1
                    # 修改1 self.ObsTop == 7
                    if self.ObsTop == 8:
                        # NOTE 记录当前最大DangerClassIndex，可能存在复数个同威胁等级的，要取出其中截获概率最小的那个作为Index
                        # 修改2
                        # 找出威胁等级最低的目标
                        max_danger_value = max(self.DangerClassList[:])
                        # 获取所有威胁等级最低的目标的索引，放到列表里面
                        lowest_indices = [i for i in range(8) if self.DangerClassList[i] == max_danger_value]
                        # 在这些索引中找出CaptureProb最小的
                        self.MinProbIndex = min(lowest_indices, key=lambda i: self.ProbList[i])
                        # self.MinProbIndex = self.ProbList.index(min(self.ProbList[:]))
                    continue

                # 修改3：DangerClass小的威胁等级高，应该保留
                # 如果新目标威胁等级高于当前最弱的（即新目标的DangerClass更小或者DangerClass相同，CaptureProb更大），则替换
                if DangerClass < self.DangerClassList[self.MinProbIndex]:
                    # 替换最弱目标
                    self.ReconObs[self.MinProbIndex] = ThisRadar
                    self.DangerClassList[self.MinProbIndex] = DangerClass
                    self.ProbList[self.MinProbIndex] = CaptureProb
                    self.TargetIDList[self.MinProbIndex] = TargetID

                    # 修改4：更新后重新计算最弱目标索引
                    # 找出新的威胁等级最低（DangerClass最大）的目标
                    max_danger_value = max(self.DangerClassList[:])
                    # 找出所有威胁等级最低的目标
                    lowest_indices = [i for i in range(8) if self.DangerClassList[i] == max_danger_value]
                    # 在这些目标中找出截获概率最小的
                    self.MinProbIndex = min(lowest_indices, key=lambda i: self.ProbList[i])

                # 修改5：如果威胁等级与当前最弱目标相同
                elif DangerClass == self.DangerClassList[self.MinProbIndex]:
                    # 如果CaptureProb大于最弱目标的CaptureProb，则替换
                    if CaptureProb > self.ProbList[self.MinProbIndex]:
                        self.ReconObs[self.MinProbIndex] = ThisRadar
                        self.DangerClassList[self.MinProbIndex] = DangerClass
                        self.ProbList[self.MinProbIndex] = CaptureProb
                        self.TargetIDList[self.MinProbIndex] = TargetID

                        # 修改6：更新后重新计算最弱目标索引
                        max_danger_value = max(self.DangerClassList[:])
                        lowest_indices = [i for i in range(8) if self.DangerClassList[i] == max_danger_value]
                        self.MinProbIndex = min(lowest_indices, key=lambda i: self.ProbList[i])

        return np.array(self.ReconObs).flatten()

    def ReconProps(self, info_manager, IllegalNW=None, silent: bool = False):
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
                "XKUReconRuleInput": RuleNodeOutput.create_message_output({}),
                "XKUReconRuleSC": RuleNodeOutput.create_scheduler_output(False),
                "XKUReconAgentSC": RuleNodeOutput.create_scheduler_output(False),
                "XKUReconAgentNW": RuleNodeOutput.create_network_output(IllegalNW)
            }
            return ReconOut

        # 如果是旧任务，不作处理，只将上次输出的IsNewTask属性置False即可return
        if not self.NewReconTask:
            self.LastReconOut["XKUReconRuleInput"]._output["IsNewTask"] = False
            return self.LastReconOut

        DefaultTask = {
            "IsNewTask": True,
            "KcgTaskType": 201,  # 201雷达侦察模式  202雷达干扰模式 203 对星对抗模式   201和202是对机  203是对星
            "KcgSubTaskType": 1,  # 1表示搜索, 2表示监视
            "fStartRF": 6,  # 起始频率
            "fEndRF": 18,  # 终止频率
            "fStartAZ": 0.0,  # 侦察起始方位
            "fEndAZ": 180.0,  # 侦查终止方位
            "fStartEL": 2.0,  # 俯仰起始
            "fEndEL": 30.0,  # 俯仰终止
        }

        ReconTaskInfo = self.LastReconTask if self.LastReconTask else DefaultTask

        raw_XKUReconRuleSC = True
        raw_XKUReconAgentSC = True

        raw_XKUReconRuleInput = {
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

        raw_XKUReconAgentNW = list(
            np.array(self.Get_Recon_Obs(info_manager, raw_XKUReconRuleInput['pProtectRFInfo'])).flatten())

        # NOTE 侦察到多少个目标，就发多少个SC和NW
        ReconOut = {
            "XKUReconRuleInput": RuleNodeOutput.create_message_output(raw_XKUReconRuleInput),
            "XKUReconRuleSC": RuleNodeOutput.create_scheduler_output(raw_XKUReconRuleSC),
            "XKUReconAgentSC": RuleNodeOutput.create_scheduler_output(raw_XKUReconAgentSC),
            "XKUReconAgentNW": RuleNodeOutput.create_network_output(raw_XKUReconAgentNW),
        }

        return ReconOut

    def JamProps(self, info_manager, IllegalNW=None, silent: bool = False):
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
                "XKUJamRuleInput": RuleNodeOutput.create_message_output({}),
                "XKUJamRuleSC": RuleNodeOutput.create_scheduler_output(False),
                "XKUJamAgentSC": RuleNodeOutput.create_scheduler_output(False),
                "XKUJamAgentNW": RuleNodeOutput.create_network_output(IllegalNW)
            }
            return JamOut

        # 如果是旧任务，不作处理，只将上次输出的IsNewTask属性置False即可return
        if not self.NewJamTask:
            self.LastJamOut["XKUJamRuleInput"]._output["IsNewTask"] = False
            return self.LastJamOut

        raw_XKUJamRuleSC = True
        raw_XKUJamAgentSC = True

        raw_XKUJamRuleInput = {
            'IsNewTask': self.NewJamTask,
            "KcgTaskType": self.LastJamTask['KcgTaskType'],
            "KcgSubTaskType": self.LastJamTask['KcgSubTaskType'],  # FIXME
            "JamMode": self.LastJamTask['JamMode'],  # 1表示噪声干扰, 5表示精瞄频, 6表示梳状谱
            "fJamRF": self.LastJamTask['fJamRF'],
            "fJamSigBW": self.LastJamTask['fJamSigBW'],
            "JamPointAZ": self.LastJamTask['JamPointAZ'],
            "JamPointEL": self.LastJamTask['JamPointEL'],  # FIXME END
            "iProtectRFNum": self.FreqInfo['iProtectRFNum'],
            "pProtectRFInfo": [tuple(dict1.values()) for dict1 in self.FreqInfo['pProtectRFInfo']] \
                if len(self.FreqInfo['pProtectRFInfo']) > 0 else [],  # 保护
        }  # if XKUJamTaskExist else {}

        raw_XKUJamAgentNW = list(
            np.array(self.Get_Recon_Obs(info_manager, raw_XKUJamRuleInput['pProtectRFInfo'])).flatten())

        JamOut = {
            "XKUJamRuleInput": RuleNodeOutput.create_message_output(raw_XKUJamRuleInput),
            "XKUJamRuleSC": RuleNodeOutput.create_scheduler_output(raw_XKUJamRuleSC),
            "XKUJamAgentSC": RuleNodeOutput.create_scheduler_output(raw_XKUJamAgentSC),
            "XKUJamAgentNW": RuleNodeOutput.create_network_output(raw_XKUJamAgentNW),
        }

        return JamOut


if __name__ == '__main__':
    from DictDisplay import MyDict
    import json

    with open('../local_bt_actions/info_manager_for_XKUTC.json', 'r') as f:
        info_manager = json.load(f)

    XKUTaskControler = XKUTaskControl()
    # Recon + Jam
    _, _, output = XKUTaskControler.step(info_manager=info_manager, blackboard=None, message=None)
    myDict = MyDict(output)
    print('------------------------>@output:\n')
    myDict.show()
    print('\n')
