from bycc.agent.config_def import BehaviorTreeNodeResult
from bycc.agent.behavior_tree.nodes.bt_action import BTAction
from bycc.common.data_interface import RuleNodeOutput

import numpy as np
import copy

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
        self.PlatID = None

        self.LastReconTask = None
        self.LastJamTask = None
        self.LastReconOut = None
        self.LastJamOut = None
        self.LastProtectRF = None

        self.NeedRecon = False
        self.ReconValid = False
        self.JamValid = False

        self.num_JamChannel = 8

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

        self.PlatID = self._get_PlatID(info_manager, 'X_KU_JAMMER')
        assert self.PlatID and self.PlatID != -1, "Invalid PlatID"

        TaskInfo, ProtectRFInfo = self._get_TaskInfo(info_manager)

        XKUReconTaskExist: bool = "SetRadarReconTask" in TaskInfo.keys()
        XKUJamTaskExist: bool = "SetRadarJamTask" in TaskInfo.keys()

        # 预处理
        # 初始化网络非法值
        """
            ParaDeclaration = [
                "TargetID",         # 0
                "PlatType",         # 1
                "Az",               # 2
                "El",               # 3
                "iRFNum",           # 4
                "pRF_max",          # 5
                "pRF_min",          # 6
                "iPRINum",          # 7
                "pPRI_max",         # 8
                "pPRI_min",         # 9
                "iPWNum",           # 10
                "pPW_max",          # 11
                "pPW_min",          # 12
                "fBandWidth",       # 13
                "DangerClass"       # 14   # 数值越小，威胁越大
                "CapNum"            # 15
            ]
        """
        SingleIllegalNW = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
        print(f"SingleIllegalNW:{len(SingleIllegalNW)}")

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
            #     if self.NewJamTask: # 新任务， 重新构造JamOut
            #         self.JamValid = True
            #         # self.NeedRecon = False   # TODO 前面侦察在开，收到强干需要关闭侦察吗？
            if int(TaskInfo["SetRadarJamTask"]["KcgSubTaskType"]) == 1:
                if self.NewJamTask:
                    self.JamValid = True
                    self.NeedRecon = True
                    self.NewReconTask = True

        if self.LastReconTask:
            self.ReconValid = True

        elif self.NeedRecon:
            self.ReconValid = True

        # 构造学习网络输入
        self.LastReconOut = self.ReconProps(info_manager) if self.ReconValid else \
            self.ReconProps(info_manager, IllegalNW=SingleIllegalNW, silent=True)
        self.LastJamOut = self.JamProps(info_manager) if self.JamValid else \
            self.JamProps(info_manager, IllegalNW=SingleIllegalNW, silent=True)
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

    def _get_rum_sub_mode_jam(self, int_mode):
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
        # NOTE 从sKCG_Get_PARA中获取当前装备的工作模式 和 子模式
        for Get_PARA in info_manager.raw_obs.extra_info_dict['obs']['data']['sKCG_Get_PARA']:
            if Get_PARA["PlatID"] == self.PlatID:
                self.sKCG_Get_PARA = Get_PARA
                if Get_PARA['WorkModeSet'] == 201:
                    New_Task_Type = 1
                    Cur_TaskInfo["SetRadarReconTask"]["KcgTaskType"] = Get_PARA['WorkModeSet']
                    Cur_TaskInfo["SetRadarReconTask"]["KcgSubTaskType"] = \
                        self._get_run_sub_mode_recon(Get_PARA['CurrRunSubMode'])
                elif Get_PARA['WorkModeSet'] == 202:
                    New_Task_Type = 2
                    Cur_TaskInfo["SetRadarJamTask"]["KcgTaskType"] = Get_PARA['WorkModeSet']
                    Cur_TaskInfo["SetRadarJamTask"]["KcgSubTaskType"] = \
                        self._get_run_sub_mode_recon(Get_PARA['CurrRunSubMode'])
                elif Get_PARA['WorkModeSet'] == 203:
                    New_Task_Type = 2
                    Cur_TaskInfo["SetRadarJamTask"]["KcgTaskType"] = Get_PARA['WorkModeSet']
                    Cur_TaskInfo["SetRadarJamTask"]["KcgSubTaskType"] = \
                        self._get_run_sub_mode_recon(Get_PARA['CurrRunSubMode'])

        # NOTE 从sKCG_XKu_Set_PARA中获取当前XKu的任务相关信息
        for XKu_Set_PARA in info_manager.raw_obs.extra_info_dict['obs']['data']['sKCG_XKu_Set_PARA']:
            if XKu_Set_PARA["PlatID"] == self.PlatID:
                self.sKCG_XKu_Set_PARA = XKu_Set_PARA
                if New_Task_Type == 1:
                    Cur_TaskInfo["SetRadarReconTask"]["fStartRF"] = XKu_Set_PARA['fStartRF']  # MHz
                    Cur_TaskInfo["SetRadarReconTask"]["fEndRF"] = XKu_Set_PARA['fEndRF']  # MHz
                    Cur_TaskInfo["SetRadarReconTask"]["fStartAz"] = XKu_Set_PARA['fStartAz']
                    Cur_TaskInfo["SetRadarReconTask"]["fEndAz"] = XKu_Set_PARA['fEndAz']
                    Cur_TaskInfo["SetRadarReconTask"]["fStartEl"] = XKu_Set_PARA['fStartEl']
                    Cur_TaskInfo["SetRadarReconTask"]["fEndEl"] = XKu_Set_PARA['fEndEl']

                elif New_Task_Type == 2:
                    # NOTE 干扰如果用到了下列信息，则默认强制干扰，采用宽带噪声
                    Cur_TaskInfo["SetRadarJamTask"]["JamMode"] = 202
                    Cur_TaskInfo["SetRadarJamTask"]["fJamRF"] = 10000.0  # MHz
                    Cur_TaskInfo["SetRadarJamTask"]["fJamSigBW"] = 1000.0  # MHz
                    Cur_TaskInfo["SetRadarJamTask"]["JamPointAz"] = XKu_Set_PARA['fAntAngAz']
                    Cur_TaskInfo["SetRadarJamTask"]["JamPointEl"] = XKu_Set_PARA['fAntAngEl']

                ProtectRFInfo["iProtectRFNum"] = XKu_Set_PARA['iProtectRFNum']
                ProtectRFInfo["pProtectRFInfo"] = XKu_Set_PARA['pProtectRFInfo']
                break

        return Cur_TaskInfo, ProtectRFInfo

    def _get_PlatID(self, info_manager, EquipmentType='X_KU_JAMMER'):
        ReconPlatID = JammerPlatID = None
        for i1 in range(len(info_manager.raw_obs.extra_info_dict['obs']['data']['reconGetPara'])):
            if info_manager.raw_obs.extra_info_dict['obs']['data']['reconGetPara'][i1][
                'EquipmentType'] == EquipmentType:
                ReconPlatID = info_manager.raw_obs.extra_info_dict['obs']['data']['reconGetPara'][i1]['PlatID']
                break

        for i1 in range(len(info_manager.raw_obs.extra_info_dict['obs']['data']['jamGetPara'])):
            if info_manager.raw_obs.extra_info_dict['obs']['data']['jamGetPara'][i1]['EquipmentType'] == EquipmentType:
                JammerPlatID = info_manager.raw_obs.extra_info_dict['obs']['data']['jamGetPara'][i1]['PlatID']
                break

        return JammerPlatID if JammerPlatID is not None else ReconPlatID

    def Get_Single_Recon_Obs(self, info_manager, pProtectRFInfo):
        """
        此函数用来构建XKU侦察任务的观测空间

        Args:
            info_manager (dict): 数据总线
            pProtectRFInfo(list[tuple]): 保护频段
        Returns:
            list: ReconAgent定制的网络输入
        Notes:
            返回值形状：
            1 * ParaDeclaration,

            ParaDeclaration = [
                "TargetID",         # 0\n
                "PlatType",         # 1\n
                "Az",               # 2\n
                "El",               # 3\n
                "iRFNum",           # 4\n
                "pRF_max",          # 5\n
                "pRF_min",          # 6\n
                "iPRINum",          # 7\n
                "pPRI_max",         # 8\n
                "pPRI_min",         # 9\n
                "iPWNum",           # 10\
                "pPW_max",          # 11\n
                "pPW_min",          # 12\n
                "fBandWidth",       # 13\n
                "DangerClass"       # 14\n      # 数值越小，威胁越大
                "CapNum"            # 15\n
            ]
        """

        self.ReconObs = [[0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0] for _ in
                         range(self.num_JamChannel)]  # 用非法值初始化，省去不足八个补足八个的逻辑
        self.CapNumList = [-1 for _ in range(self.num_JamChannel)]
        self.TargetIDList = [-1 for _ in range(self.num_JamChannel)]
        self.MinCapNumIndex = 0
        self.ObsTop = 0

        reconRadarPara = info_manager.raw_obs.extra_info_dict['obs']['data']['reconRadarPara']
        for ParaIndex in range(len(reconRadarPara)):  # 遍历任务信息
            # 判断是不是我的RADAR数据
            PlatID = reconRadarPara[ParaIndex]['PlatID']
            if PlatID != self.PlatID:
                continue

            # NOTE 方位均为以正北为0

            self.ReconID = reconRadarPara[ParaIndex]['ReconID']  # NOTE 设备id，传给ReconRule？
            ReconDetectRadar = reconRadarPara[ParaIndex]['ReconRadarPara']
            RadarNum = reconRadarPara[ParaIndex]['RadarNum']

            for DetectRadar_idx in range(RadarNum):  # DetectRadar:int  遍历所有发现的雷达
                ReconResult = ReconDetectRadar[DetectRadar_idx]['ReconResult']

                TargetID = ReconResult['TargetID']
                PlatType = ReconDetectRadar[DetectRadar_idx]['PlatType']
                Az = ReconResult['Az']
                El = ReconResult['El']
                iRFNum = ReconResult['iRFNum']
                pRF = copy.deepcopy(ReconResult['pRF'])  # 载频数组
                iPRINum = ReconResult['iPRINum']
                pPRI = copy.deepcopy(ReconResult['pPRI'])  # 重频数组
                pPRI_max, pPRI_min = (0, 0) if iPRINum == 0 else (max(pPRI), min(pPRI))
                iPWNum = ReconResult['iPWNum']
                pPW = copy.deepcopy(ReconResult['pPW'])  # 脉宽数组
                (pPW_max, pPW_min) = (0, 0) if iPWNum == 0 else (max(pPW), min(pPW))
                fBandWidth = ReconResult['fBandWidth']
                DangerClass = ReconDetectRadar[DetectRadar_idx]['DangerClass']
                CapNum = ReconResult['CapNum']

                # 利用保护频段筛选保护频段外的数据
                for i in range(iRFNum):
                    for protectRFtuple in pProtectRFInfo:
                        if protectRFtuple[0] <= pRF[i] <= protectRFtuple[1]:
                            pRF[i] = -1

                pRF = [RF for RF in pRF if RF != -1]
                if pRF == []:
                    continue

                (pRF_max, pRF_min) = (0, 0) if len(pRF) == 0 else (max(pRF), min(pRF))

                # FIXME 开展每个输入维度的-1～1归一化或者0～1归一化
                norm_PlatType = 2 * (PlatType / 16.0) - 1.0
                norm_Az = Az / 180.0  # 度
                norm_El = El / 90.0  # 度
                norm_iRFNum = 2 * iRFNum / 64.0 - 1.0  #
                norm_pRF_max = 2 * ((pRF_max - 6000.0) / (18000.0 - 6000.0)) - 1.0  # MHz
                norm_pRF_min = 2 * ((pRF_min - 6000.0) / (18000.0 - 6000.0)) - 1.0  # MHz
                norm_iPRINum = 2 * iPRINum / 64.0 - 1.0  #
                norm_pPRI_max = 2 * (pPRI_max / 1000.0) - 1.0  # us
                norm_pPRI_min = 2 * (pPRI_min / 1000.0) - 1.0  # us
                norm_iPWNum = 2 * (iPWNum / 64.0) - 1.0  #
                norm_pPW_max = 2 * (pPW_max / 100.0) - 1.0  # us
                norm_pPW_min = 2 * (pPW_min / 100.0) - 1.0  # us
                norm_fBandWidth = 2 * (fBandWidth / 1000.0) - 1.0  # MHz
                norm_DangerClass = 2 * (DangerClass / 10.0) - 1.0  #
                norm_CapNum = 2 * (CapNum / 20.0) - 1.0  #

                ThisRadar = [TargetID, norm_PlatType, norm_Az, norm_El, norm_iRFNum, norm_pRF_max, norm_pRF_min,
                             norm_iPRINum, norm_pPRI_max, norm_pPRI_min, norm_iPWNum, norm_pPW_max, norm_pPW_min,
                             norm_fBandWidth, norm_DangerClass, norm_CapNum]

                # TargetID 相同，这个判断要在最前面，
                if TargetID in self.TargetIDList:
                    if CapNum > self.CapNumList[self.TargetIDList.index(TargetID)]:
                        SameTargetIndex = self.TargetIDList.index(TargetID)
                        self.ReconObs[SameTargetIndex] = ThisRadar
                        self.CapNumList[SameTargetIndex] = CapNum
                        self.MinCapNumIndex = self.CapNumList.index(min(self.CapNumList[:]))
                    continue

                # 前8个直接入列
                if self.ObsTop < 8:
                    self.ReconObs[self.ObsTop] = ThisRadar
                    self.CapNumList[self.ObsTop] = CapNum
                    self.TargetIDList[self.ObsTop] = TargetID
                    self.ObsTop += 1
                    if self.ObsTop == 7:
                        self.MinCapNumIndex = self.CapNumList.index(min(self.CapNumList[:]))
                    continue

                # 如果CaptureProb 小于目前最小的，跳过
                if CapNum < self.CapNumList[self.MinCapNumIndex]:
                    continue

                self.MinCapNumIndex = self.CapNumList.index(min(self.CapNumList[:]))  # 更新最小prob的索引
                self.ReconObs[self.MinCapNumIndex] = ThisRadar  # 用ThisRadar覆盖目前prob最小的Radar
                self.TargetIDList[self.MinCapNumIndex] = TargetID  # 更新对应行的TargetID
                self.CapNumList[self.MinCapNumIndex] = CapNum  # 更新对应行的CaptureProb

        return np.array(self.ReconObs)

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
                "Az",               # 2\n
                "El",               # 3\n
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
        self.CapNumList = [-1 for _ in range(8)]
        self.TargetIDList = [-1 for _ in range(8)]
        self.MinCapNumIndex = 0
        self.ObsTop = 0

        reconRadarPara = info_manager.raw_obs.extra_info_dict['obs']['data']['reconRadarPara']
        for ParaIndex in range(len(reconRadarPara)):  # 遍历任务信息
            # 判断是不是我的RADAR数据
            PlatID = reconRadarPara[ParaIndex]['PlatID']
            if PlatID != self.PlatID:
                continue

            # NOTE 方位可能存在歧义，可能不以东为0，此时要以初始化的基线做基线

            self.ReconID = reconRadarPara[ParaIndex]['ReconID']  # NOTE 设备id，传给ReconRule？
            ReconDetectRadar = reconRadarPara[ParaIndex]['ReconRadarPara']
            RadarNum = reconRadarPara[ParaIndex]['RadarNum']

            for DetectRadar in range(RadarNum):  # DetectRadar:int  遍历所有发现的雷达
                ReconResult = ReconDetectRadar[DetectRadar]['ReconResult']
                DangerClass = ReconDetectRadar[DetectRadar]['DangerClass']
                TargetID = ReconResult['TargetID']
                PlatType = ReconDetectRadar[DetectRadar]['PlatType']
                Az = ReconResult['Az']
                El = ReconResult['El']
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

                ThisRadar = [TargetID, PlatType, Az, El, pRF_max, pRF_min, pPRI_max, pPRI_min, pPW_max, pPW_min,
                             DangerClass, CaptureProb]

                # TargetID 相同，这个判断要在最前面，
                if TargetID in self.TargetIDList:
                    if CaptureProb > self.CapNumList[self.TargetIDList.index(TargetID)]:
                        SameTargetIndex = self.TargetIDList.index(TargetID)
                        self.ReconObs[SameTargetIndex] = ThisRadar
                        self.CapNumList[SameTargetIndex] = CaptureProb
                        self.MinCapNumIndex = self.CapNumList.index(min(self.CapNumList[:]))
                    continue

                # 前8个直接入列
                if self.ObsTop < 8:
                    self.ReconObs[self.ObsTop] = ThisRadar
                    self.CapNumList[self.ObsTop] = CaptureProb
                    self.TargetIDList[self.ObsTop] = TargetID
                    self.ObsTop += 1
                    if self.ObsTop == 7:
                        self.MinCapNumIndex = self.CapNumList.index(min(self.CapNumList[:]))
                    continue

                # 如果CaptureProb 小于目前最小的，跳过
                if CaptureProb < self.CapNumList[self.MinCapNumIndex]:
                    continue

                self.MinCapNumIndex = self.CapNumList.index(min(self.CapNumList[:]))  # 更新最小prob的索引
                self.ReconObs[self.MinCapNumIndex] = ThisRadar  # 用ThisRadar覆盖目前prob最小的Radar
                self.TargetIDList[self.MinCapNumIndex] = TargetID  # 更新对应行的TargetID
                self.CapNumList[self.MinCapNumIndex] = CaptureProb  # 更新对应行的CaptureProb

        return np.array(self.ReconObs).flatten()

    def ReconProps(self, info_manager, IllegalNW=None, silent: bool = False):
        """
        此函数用于构造step函数输出的Recon部分，包括RuleSC， RuleInput, AgentSC, AgentNW

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
                f"XKUReconAgentSC": RuleNodeOutput.create_scheduler_output(False),
                f"XKUReconAgentNW": RuleNodeOutput.create_network_output(IllegalNW)
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
            "fStartAz": 0.0,  # 侦察起始方位
            "fEndAz": 180.0,  # 侦查终止方位
            "fStartEl": 2.0,  # 俯仰起始
            "fEndEl": 30.0,  # 俯仰终止
        }

        DefaultProtectRF = {
            "iProtectRFNum": 0,
            "pProtectRFInfo": []
        }

        ReconTaskInfo = self.LastReconTask if self.LastReconTask else DefaultTask
        ProtectRFInfo = self.LastProtectRF if self.LastProtectRF else DefaultProtectRF

        raw_XKUReconRuleSC = True
        raw_XKUReconAgentSC = True

        raw_XKUReconRuleInput = {
            'IsNewTask': self.NewReconTask,
            "KcgTaskType": ReconTaskInfo['KcgTaskType'],
            "KcgSubTaskType": ReconTaskInfo['KcgSubTaskType'],
            "fStartRF": ReconTaskInfo['fStartRF'],
            "fEndRF": ReconTaskInfo['fEndRF'],
            "fStartEl": ReconTaskInfo['fStartEl'],
            "fEndEl": ReconTaskInfo['fEndEl'],
            "fStartAz": ReconTaskInfo['fStartAz'],
            "fEndAz": ReconTaskInfo['fEndAz'],
            "iProtectRFNum": ProtectRFInfo['iProtectRFNum'],
            "pProtectRFInfo": [tuple(RF.values()) for RF in ProtectRFInfo['pProtectRFInfo']] \
                if len(ProtectRFInfo['pProtectRFInfo']) > 0 else [],  # 保护
        }

        raw_XKUReconAgentNW = list(self.Get_Single_Recon_Obs(info_manager, raw_XKUReconRuleInput['pProtectRFInfo']))

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
            "JamPointAz": self.LastJamTask['JamPointAz'],
            "JamPointEl": self.LastJamTask['JamPointEl'],  # FIXME END
            "iProtectRFNum": self.FreqInfo['iProtectRFNum'],
            "pProtectRFInfo": [tuple(dict1.values()) for dict1 in self.FreqInfo['pProtectRFInfo']] \
                if len(self.FreqInfo['pProtectRFInfo']) > 0 else [],  # 保护
        }  # if XKUJamTaskExist else {}

        raw_XKUJamAgentNW = list(
            np.array(self.Get_Recon_Obs(info_manager, raw_XKUJamRuleInput['pProtectRFInfo'])).flatten())

        JamOut = {
            "XKUJamRuleInput": RuleNodeOutput.create_message_output(raw_XKUJamRuleInput),
            "XKUJamRuleSC": RuleNodeOutput.create_scheduler_output(raw_XKUJamRuleSC),
        }
        # for i,item in enumerate(list1):
        #     if not item:
        #         JamOut.update(
        #         {
        #             f"XKUJamAgentCh{i}SC": RuleNodeOutput.create_scheduler_output(raw_XKUJamAgentSC),
        #             f"XKUJamAgentCh{i}NW": RuleNodeOutput.create_network_output(raw_XKUJamAgentNW),
        #             }
        #         )
        #     else:


        return JamOut


if __name__ == '__main__':
# from DictDisplay import MyDict
# import json
#
# with open('../local_bt_actions/info_manager_for_XKUTC.json', 'r') as f:
#     info_manager = json.load(f)
#
# XKUTaskControler = XKUTaskControl()
# # Recon + Jam
# _, _, output = XKUTaskControler.step(info_manager=info_manager, blackboard=None, message=None)
# myDict = MyDict(output)
# print('------------------------>@output:\n')
# myDict.show()
# print('\n')
