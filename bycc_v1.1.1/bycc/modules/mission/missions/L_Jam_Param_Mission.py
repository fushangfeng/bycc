from bycc.common.mission import Mission, MissionStatus
from env_interface.utils.GetData import Get_EquipID
DECLARATION = {
    "name": "L雷达GR参数控制",  # 组件名称，用于前端显示和后台索引
    "class": "LJamParamMission",  # 组件类名
    "params": {  # 组件参数，用于前端显示参数信息
        "JamType_Ch1_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "GR样式Ch1索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "JamBandWidthSZP_Ch1_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "梳状谱GR带宽Ch1索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "JamBandWidth_Ch1_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "宽带噪声GR带宽Ch1索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "SampleCheck_Ch1_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "样本确认Ch1索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "ReceiveTime_Ch1_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "接收窗Ch1索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "EmissionTime_Ch1_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "发射窗Ch1索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "JamType_Ch2_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "GR样式Ch2索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "JamBandWidthSZP_Ch2_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "梳状谱GR带宽Ch2索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "JamBandWidth_Ch2_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "宽带噪声GR带宽Ch2索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "SampleCheck_Ch2_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "样本确认Ch2索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "ReceiveTime_Ch2_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "接收窗Ch2索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "EmissionTime_Ch2_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "发射窗Ch2索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "JamType_Ch3_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "GR样式Ch3索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "JamBandWidthSZP_Ch3_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "梳状谱GR带宽Ch3索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "JamBandWidth_Ch3_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "宽带噪声GR带宽Ch3索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "SampleCheck_Ch3_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "样本确认Ch3索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "ReceiveTime_Ch3_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "接收窗Ch3索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "EmissionTime_Ch3_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "发射窗Ch3索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "JamType_Ch4_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "GR样式Ch4索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "JamBandWidthSZP_Ch4_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "梳状谱GR带宽Ch4索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "JamBandWidth_Ch4_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "宽带噪声GR带宽Ch4索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "SampleCheck_Ch4_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "样本确认Ch4索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "ReceiveTime_Ch4_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "接收窗Ch4索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "EmissionTime_Ch4_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "发射窗Ch4索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "JamType_Ch5_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "GR样式Ch5索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "JamBandWidthSZP_Ch5_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "梳状谱GR带宽Ch5索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "JamBandWidth_Ch5_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "宽带噪声GR带宽Ch5索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "SampleCheck_Ch5_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "样本确认Ch5索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "ReceiveTime_Ch5_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "接收窗Ch5索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "EmissionTime_Ch5_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "发射窗Ch5索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "JamType_Ch6_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "GR样式Ch6索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "JamBandWidthSZP_Ch6_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "梳状谱GR带宽Ch6索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "JamBandWidth_Ch6_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "宽带噪声GR带宽Ch6索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "SampleCheck_Ch6_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "样本确认Ch6索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "ReceiveTime_Ch6_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "接收窗Ch6索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "EmissionTime_Ch6_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "发射窗Ch6索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "JamType_Ch7_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "GR样式Ch7索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "JamBandWidthSZP_Ch7_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "梳状谱GR带宽Ch7索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "JamBandWidth_Ch7_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "宽带噪声GR带宽Ch7索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "SampleCheck_Ch7_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "样本确认Ch7索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "ReceiveTime_Ch7_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "接收窗Ch7索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "EmissionTime_Ch7_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "发射窗Ch7索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "JamType_Ch8_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "GR样式Ch8索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "JamBandWidthSZP_Ch8_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "梳状谱GR带宽Ch8索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "JamBandWidth_Ch8_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "宽带噪声GR带宽Ch8索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "SampleCheck_Ch8_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "样本确认Ch8索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "ReceiveTime_Ch8_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "接收窗Ch8索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        },
        "EmissionTime_Ch8_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "发射窗Ch8索引",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        }
    },
    "description": "L雷达GR样式、带宽控制、样本检查和接发窗"  # 组件描述，用于前端显示
}

class LJamParamMission(Mission):

    def __init__(self, mission_id, mission_parameter, info_manager, mission_manager):
        super().__init__(mission_id, mission_parameter, info_manager, mission_manager)
        self.info_manger = info_manager

        # 获取EqupID
        self.EquipID = Get_EquipID(info_manager)
        assert self.EquipID and self.EquipID != -1, "Invalid EquipID"

        self.channelNum = 8

        self.JamTypeList = [101, 102, 103]
        self.JamBandWidthList = [0, 5, 10, 50, 100, 400]
        self.SampleCheck = [0, 1, 2, 3]

    def build(self):
        self.set_mission_status(MissionStatus.Ready)
        return self.status

    def step(self):
        raw_cmds = {}
        temp_cmds = []

        pPRI_list = self._get_pPRI_list()

        for i in range(len(pPRI_list)):
            # 直接从 params 字典获取当前通道的参数（而不是从实例属性）
            jam_type_idx = self.params.get(f'JamType_Ch{i + 1}_idx', 0)

            # 边界检查，确保索引不越界
            jam_type_idx = min(jam_type_idx, len(self.JamTypeList) - 1)

            # 转换为实际值
            jam_type = self.JamTypeList[jam_type_idx]

            if jam_type == 201:
                bandwidth_szp_value = self.params.get(f'JamBandWidthSZP{i + 1}_idx', 0)
                # 边界检查，确保索引不越界
                bandwidth = round((bandwidth_szp_value + 1) * 500)


            elif jam_type == 202 or jam_type == 203:
                bandwidth_wn_idx = self.params.get(f'JamBandWidth_Ch{i + 1}_idx', 0)
                # 边界检查，确保索引不越界
                bandwidth_wn_idx = min(bandwidth_wn_idx, len(self.JamBandWidthList) - 1)
                bandwidth = self.JamBandWidthList[bandwidth_wn_idx]

            # 基础配置 - 只包含必要的字段
            channel = {
                'SetJamType': jam_type,
                'JamParam': {
                    'SetJamBandWidth': bandwidth
                }
            }

            # 只有JamType=203时才添加接发窗
            if jam_type == 203:
                # 从params 获取接发窗参数
                sample_check_idx = self.params.get(f'SampleCheck_Ch{i + 1}_idx', 0)
                receive_time_value = self.params.get(f'ReceiveTime_Ch{i + 1}_idx', 0)
                emission_time_value = self.params.get(f'EmissionTime_Ch{i + 1}_idx', 0)

                # 边界检查，确保索引不越界
                sample_check_idx = min(sample_check_idx, len(self.SampleCheck) - 1)

                sample_check = self.SampleCheck[sample_check_idx]

                # 截断数据
                raw_receive = (receive_time_value * 4.5) + 5.5
                raw_emission = (emission_time_value * 22.5) + 27.5

                # pPRI_list是一个列表包含多个字典，字典个数等于ZC到的目标个数
                if pPRI_list[i]['iPRINum'] >= 1:
                    receive_time = min(pPRI_list[i]['pPRI']) * raw_receive
                    receive_time_rounded = round(receive_time)
                    emission_time = min(pPRI_list[i]['pPRI']) * raw_emission
                    emission_time_rounded = round(emission_time)
                else:
                    receive_time_rounded = 100000
                    emission_time_rounded = 500000

                # 添加到参数中
                channel['SampleCheck'] = sample_check
                channel['ReceiveTime'] = receive_time_rounded
                channel['EmissionTime'] = emission_time_rounded

            temp_cmds.append(channel)

        raw_cmds['SetRadarJamParam_Agent'] = temp_cmds

        self.set_mission_status(MissionStatus.Exited)

        return [raw_cmds]

    def _get_pPRI_list(self):
        pPRI_list = []
        DangerClassList = [-1 for _ in range(8)]
        ProbList = [-1 for _ in range(8)]
        TargetIDList = [-1 for _ in range(8)]
        MinProbIndex = 0
        ObsTop = 0

        reconRadarPara = self.info_manager.raw_obs.extra_info_dict['obs']['data']['reconRadarPara']
        for ParaIndex in range(len(reconRadarPara)):  # 遍历任务信息
            # 判断是不是我的RADAR数据
            if self.EquipID != reconRadarPara[ParaIndex]['ReconID']:
                continue

            ReconDetectRadar = reconRadarPara[ParaIndex]['ReconRadarPara']
            self.RadarNum = reconRadarPara[ParaIndex]['RadarNum']

            for DetectRadar in range(self.RadarNum):  # DetectRadar:int  便利所有发现的雷达
                ReconResult = ReconDetectRadar[DetectRadar]['ReconResult']
                DangerClass = ReconDetectRadar[DetectRadar]['DangerClass']
                TargetID = ReconResult['TargetID']
                iPRINum = ReconResult['iPRINum']  # 载频数组
                pPRI = ReconResult['pPRI']
                CaptureProb = ReconResult['CaptureProb']

                ThisRadar = {
                    'iPRINum': iPRINum,
                    'pPRI': pPRI,
                    'CaptureProb': CaptureProb
                }

                # TargetID 相同，则将CaptureProb大的替换列表里面的，这个判断要在最前面，
                if TargetID in TargetIDList:
                    # 同一目标的威胁等级发生变化，优先级更高
                    if DangerClass < DangerClassList[TargetIDList.index(TargetID)]:
                        SameTargetIndex = TargetIDList.index(TargetID)
                        pPRI_list[SameTargetIndex] = ThisRadar
                        DangerClassList[SameTargetIndex] = DangerClass
                        ProbList[SameTargetIndex] = CaptureProb
                        # MaxDangerClassIndex = DangerClassList.index(max(DangerClassList[:]))
                        # MinProbIndex = ProbList.index(min(ProbList[:]))
                    elif DangerClass == DangerClassList[TargetIDList.index(TargetID)]:
                        if CaptureProb > ProbList[TargetIDList.index(TargetID)]:
                            SameTargetIndex = TargetIDList.index(TargetID)
                            pPRI_list[SameTargetIndex] = ThisRadar
                            ProbList[SameTargetIndex] = CaptureProb
                            # MaxDangerClassIndex = DangerClassList.index(max(DangerClassList[:]))
                            # MinProbIndex = ProbList.index(min(ProbList[:]))
                    continue

                # 前8个直接入列
                if ObsTop < 8:
                    pPRI_list[ObsTop] = ThisRadar
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
                    pPRI_list[MinProbIndex] = ThisRadar
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
                        pPRI_list[MinProbIndex] = ThisRadar
                        DangerClassList[MinProbIndex] = DangerClass
                        ProbList[MinProbIndex] = CaptureProb
                        TargetIDList[MinProbIndex] = TargetID

                        # 修改6：更新后重新计算最弱目标索引
                        max_danger_value = max(DangerClassList[:])
                        lowest_indices = [i for i in range(8) if DangerClassList[i] == max_danger_value]
                        MinProbIndex = min(lowest_indices, key=lambda i: ProbList[i])  # 更新对应行的CaptureProb

        # 基于CaptureProb对pPRI_list进行排序
        ObsCopy = pPRI_list.copy()
        sorted_list = sorted(ObsCopy, key=lambda x: x['CaptureProb'], reverse=True)  # -1为CaptureProb的索引

        return sorted_list