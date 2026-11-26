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
        self.EquipID = None

        self.LastReconTask = None
        self.LastJamTask = None
        self.LastReconOut = None
        self.LastJamOut = None
        self.LastProtectRF = None

        self.NeedRecon = False
        self.ReconValid = False
        self.JamValid = False

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

        self.EquipID = Get_EquipID(info_manager)
        assert self.EquipID and self.EquipID != -1, "Invalid ReconID or JammerID"

        TaskInfo, ProtectRFInfo = self._get_TaskInfo(info_manager)

        # 检查当前轮是否收到了侦察任务
        XKUReconTaskExist: bool = ("SetRadarReconTask" in TaskInfo.keys())  # XKU是否有侦察任务
        # 检查当前轮次是否收到了干扰任务
        XKUJamTaskExist: bool = ("SetRadarJamTask" in TaskInfo.keys())  # XKU是否有干扰任务

        # 预处理
        # 初始化网络非法值
        # NOTE 将IllegalNW写成单个网络
        IllegalNW = list(np.array([[-1, -1, 0, 0, -1, -1, 0, 0, -1, -1, -1, -1] for _ in range(8)]).flatten())
        # print(f"IllegalNW:{len(IllegalNW)}")   96

        # 判断前面所有轮的
        if self.LastReconTask == None:
            if XKUReconTaskExist:  # 最新的任务，第一次收到任务
                self.LastReconTask = TaskInfo["SetRadarReconTask"]  # 直接复制并跳过
                self.LastProtectRF = ProtectRFInfo
                self.NewReconTask = True  # 方便理解
        else:  # 有过任务
            if not XKUReconTaskExist or self.LastReconTask == TaskInfo["SetRadarReconTask"]:  # 执行旧任务
                self.NewReconTask = False  # 标记为旧任务
            else:  # 执行新任务
                # 当前轮
                self.LastReconTask = TaskInfo["SetRadarReconTask"]
                self.LastProtectRF = ProtectRFInfo
                self.NewReconTask = True  # 标记为新任务
        # NOTE 其实self.LastReconTask走过上诉判断后将保持为最新任务

        if self.LastJamTask == None:
            if XKUJamTaskExist:
                self.LastJamTask = TaskInfo["SetRadarJamTask"]
                self.LastProtectRF = ProtectRFInfo
                self.NewJamTask = True
        else:
            if not XKUJamTaskExist or self.LastJamTask == TaskInfo["SetRadarJamTask"]:
                self.NewJamTask = False
            else:
                self.LastJamTask = TaskInfo["SetRadarJamTask"]
                self.LastProtectRF = ProtectRFInfo
                self.NewJamTask = True
        # NOTE 同上

        if self.LastJamTask:  # 如果有干扰任务， NOTE: 还有一个干扰持续时间的说法，可能需要定时清楚LastJamTask为None, LastReconTask同理。
            # if int(TaskInfo["SetRadarJamTask"]["KcgSubTaskType"]) == 2:        # 强制干扰
            # if self.NewJamTask: # 新任务， 重新构造JamOut
            # self.JamValid = True
            # self.NeedRecon = False   # TODO 前面侦察在开，收到强干需要关闭侦察吗？
            if int(TaskInfo["SetRadarJamTask"]["KcgSubTaskType"]) == 1:
                if self.NewJamTask:
                    self.JamValid = True
                    self.NeedRecon = True
                    self.NewReconTask = True

        if self.LastReconTask:
            self.ReconValid = True

        elif self.NeedRecon:
            self.ReconValid = True

        self.LastReconOut = self.ReconProps(info_manager) if self.ReconValid else (
            self.ReconProps(info_manager, IllegalNW=IllegalNW, silent=True))
        self.LastJamOut = self.JamProps(info_manager) if self.JamValid else (
            self.JamProps(info_manager, IllegalNW=IllegalNW, silent=True))
        output = {}
        output.update(self.LastReconOut)
        output.update(self.LastJamOut)

        return [], BehaviorTreeNodeResult.SUCCESS, output

    def _get_run_sub_mode_recon(self, int_mode):
        sub_mode_bin_str = np.binary_repr(int_mode, width=5)
        if sub_mode_bin_str[-1] == 1:
            KcgSubTaskType = 1
        elif sub_mode_bin_str[-2] == 1:
            KcgSubTaskType = 2

        return KcgSubTaskType

    def _get_run_sub_mode_jam(self, int_mode):
        sub_mode_bin_str = np.binary_repr(int_mode, width=5)
        if sub_mode_bin_str[-3] == 1 or \
                sub_mode_bin_str[-4] == 1 or \
                sub_mode_bin_str[-5] == 1:
            KcgSubTaskType = 1

        return KcgSubTaskType

    def _get_TaskInfo(self, info_manager):
        Cur_TaskInfo = {}
        ProtectRFInfo = {}
        New_Task_Type = -1
        # NOTE 从kcgGetPara中获取当前装备的工作模式 和 子模式
        for Get_PARA in info_manager.raw_obs.extra_info_dict['obs']['data']['kcgGetPara']:
            if Get_PARA["EquipID"] == self.EquipID:
                self.kcgGetPara = Get_PARA
                if Get_PARA['WorkModeSet'] == 201:
                    New_Task_Type = 1
                    Cur_TaskInfo["SetRadarReconTask"]["KcgTaskType"] = Get_PARA['WorkModeSet']
                    Cur_TaskInfo["SetRadarReconTask"]["KcgSubTaskType"] = \
                        self._get_run_sub_mode_recon(Get_PARA['CurrRunSubMode'])
                elif Get_PARA['WorkModeSet'] == 202:
                    New_Task_Type = 2
                    Cur_TaskInfo["SetRadarJamTask"]["KcgTaskType"] = Get_PARA['WorkModeSet']
                    Cur_TaskInfo["SetRadarJamTask"]["KcgSubTaskType"] = \
                        self._get_run_sub_mode_jam(Get_PARA['CurrRunSubMode'])
                elif Get_PARA['WorkModeSet'] == 203:
                    New_Task_Type = 2
                    Cur_TaskInfo["SetRadarJamTask"]["KcgTaskType"] = Get_PARA['WorkModeSet']
                    Cur_TaskInfo["SetRadarJamTask"]["KcgSubTaskType"] = \
                        self._get_run_sub_mode_jam(Get_PARA['CurrRunSubMode'])

        # NOTE 从kcgXKuSetPara中获取当前XKu的任务相关信息
        for XKuSetPara in info_manager.raw_obs.extra_info_dict['obs']['data']['kcgXKuSetPara']:
            if XKuSetPara["EquipID"] == self.EquipID:
                self.kcgXKuSetPara = XKuSetPara
                if New_Task_Type == 1:
                    Cur_TaskInfo["SetRadarReconTask"]["fStartRF"] = XKuSetPara['fStartRF']  # MHz
                    Cur_TaskInfo["SetRadarReconTask"]["fEndRF"] = XKuSetPara['fEndRF']  # MHz
                    Cur_TaskInfo["SetRadarReconTask"]["fStartAz"] = XKuSetPara['fStartAz']
                    Cur_TaskInfo["SetRadarReconTask"]["fEndAz"] = XKuSetPara['fEndAz']
                    Cur_TaskInfo["SetRadarReconTask"]["fStartEl"] = XKuSetPara['fStartEl']
                    Cur_TaskInfo["SetRadarReconTask"]["fEndEl"] = XKuSetPara['fEndEl']

                elif New_Task_Type == 2:
                    # NOTE 干扰如果用到了下列信息，则默认强制干扰，采用宽带噪声
                    Cur_TaskInfo["SetRadarJamTask"]["JamMode"] = 202
                    Cur_TaskInfo["SetRadarJamTask"]["fJamRF"] = 10000.0  # MHz
                    Cur_TaskInfo["SetRadarJamTask"]["fJamSigBW"] = 1000.0  # MHz
                    Cur_TaskInfo["SetRadarJamTask"]["JamPointAz"] = XKuSetPara['fAntAngAz']
                    Cur_TaskInfo["SetRadarJamTask"]["JamPointEl"] = XKuSetPara['fAntAngEl']

                ProtectRFInfo["iProtectRFNum"] = XKuSetPara['iProtectRFNum']
                ProtectRFInfo["pProtectRFInfo"] = XKuSetPara['pProtectRFInfo']
                break

        return Cur_TaskInfo, ProtectRFInfo

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
        self.ProbList = [-1 for _ in range(8)]
        self.TargetIDList = [-1 for _ in range(8)]
        self.MinProbIndex = 0
        self.ObsTop = 0

        reconRadarPara = info_manager.raw_obs.extra_info_dict['obs']['data']['reconRadarPara']
        for ParaIndex in range(len(reconRadarPara)):  # 遍历任务信息
            # 判断是不是我的RADAR数据
            if self.EquipID != reconRadarPara[ParaIndex]['ReconID']:
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
        ProtectRFInfo = self.LastProtectRF

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
            "iProtectRFNum": ProtectRFInfo['iProtectRFNum'],
            "pProtectRFInfo": [tuple(dict1.values()) for dict1 in ProtectRFInfo['pProtectRFInfo']] \
                if len(ProtectRFInfo['pProtectRFInfo']) > 0 else [],  # 保护
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
            "iProtectRFNum": self.LastProtectRF['iProtectRFNum'],
            "pProtectRFInfo": [tuple(dict1.values()) for dict1 in self.LastProtectRF['pProtectRFInfo']] \
                if len(self.LastProtectRF['pProtectRFInfo']) > 0 else [],  # 保护
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
