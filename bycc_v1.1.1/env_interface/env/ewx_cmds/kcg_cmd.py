import json

from env_interface.protos.output.ai_pb2 import Action
from typing import Union, Dict, List

class XKU_Actions:
    @classmethod
    def make_action_SetReconPara(cls, nRRconID: int, recon_cmds: List):
        # 设置雷达对抗ZC参数
        nPolicyNum = int(len(recon_cmds) / 2)
        ParaList = []
        for i in range(1, len(recon_cmds), 2):
            # temp_dict = {}
            # temp_dict['StartFreq'] = recon_cmds[i]['SetReconRFPara']['StartFreq']
            # temp_dict['EndFreq'] = recon_cmds[i]['SetReconRFPara']['EndFreq']
            # temp_dict['WorkPitNor'] = recon_cmds[i]['SetWorkPitNor']['WorkPitNor']
            # temp_dict['DwellTime'] = recon_cmds[i]['SetDwellTime']['DwellTime']
            ParaList.append(recon_cmds[i]['SetReconRFPara']['StartFreq'] * 1000)  # GHz -> MHz
            ParaList.append(recon_cmds[i]['SetReconRFPara']['EndFreq'] * 1000) # GHz -> MHz
            ParaList.append(recon_cmds[i]['SetWorkPitNor']['WorkPitNor']) # 度
            ParaList.append(recon_cmds[i]['SetDwellTime']['DwellTime']) # ms

        str_ParaList = ','.join(str(item) for item in ParaList)
        SetReconPara = f"{nRRconID},{nPolicyNum}," + str_ParaList
        SetReconParaDict = {
            "SetReconPara": SetReconPara,
        }
        # json_cmd = json.dumps(dict(nRRconID=nRRconID, nPolicyNum = nPolicyNum, ParaList=ParaList))
        json_cmd = json.dumps(SetReconParaDict)

        action = Action(modelType="RadarRecon", actionName='SetReconPara', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_SetAttenuator(cls, nRRconID: int, recon_cmds: List):
        # 设置雷达对抗ZC门限衰减值1
        Attenuator = recon_cmds[1]['SetDecayValue']['decayValue1']
        # json_cmd = json.dumps(dict(nRRconID=nRRconID,
        #                            Attenuator=Attenuator))
        SetAttenuator = f"{nRRconID},{Attenuator}"
        SetAttenuatorDict = {
            "SetAttenuator": SetAttenuator
        }
        json_cmd = json.dumps(SetAttenuatorDict)
        action = Action(modelType="RadarRecon", actionName='SetAttenuator', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_SetReconPolarType(cls, nRRconID: int, recon_cmds: List):
        # 设置雷达对抗ZC极化方式
        PolarType = recon_cmds[1]['SetReconPolarType']['PolarType']
        SetReconPolarType = f"{nRRconID},{PolarType}"
        SetReconPolarTypeDict = {
            "SetReconPolarType": SetReconPolarType
        }
        # json_cmd = json.dumps(dict(nRRconID=nRRconID,
        #                            PolarType=PolarType))
        json_cmd = json.dumps(SetReconPolarTypeDict)

        action = Action(modelType="RadarRecon", actionName='SetReconPolarType', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_SetJamOnoff(cls, nJamID: int, RadarJamParam: List):
        # 设置GR开关
        # 对GR开关设置参数进行处理
        nJamChannelNum = 8
        max_channel_id = 0
        ParaList = []
        for item in RadarJamParam:
            # 第一层保护：确保item是字典且包含'SetJamOnOff'键
            if isinstance(item, dict) and 'SetJamOnOff' in item:
                # 第二层保护：安全获取JamChannelList，如果不存在则用空列表
                for channel in item['SetJamOnOff'].get('JamChannelList', []):
                    # ParaList.append({
                    #     'ChannelID': channel.get('ChannelID'),
                    #     'TargetType': 0,
                    #     'Launch': channel.get('Onoff')
                    # })
                    ParaList.append(channel.get('ChannelID'))
                    ParaList.append(0)
                    ParaList.append(channel.get('Onoff'))
                    max_channel_id += 1

        # 补全剩余的通道到8个
        for i in range(max_channel_id + 1, nJamChannelNum + 1):
            # ParaList.append({
            #     'ChannelID': i,
            #     'TargetType': 0,
            #     'Launch': 0
            # })
            ParaList.append(i)
            ParaList.append(0)
            ParaList.append(0)

        str_ParaList = ','.join(str(item) for item in ParaList)
        SetJamOnOff = f"{nJamID},{nJamChannelNum}," + str_ParaList
        # json_cmd = json.dumps(dict(nJamID=nJamID,
        #                            nJamChannelNum=nJamChannelNum,
        #                            ParaList=ParaList))
        SetJamOnOffDict = {
            "SetJamOnOff": SetJamOnOff
        }
        json_cmd = json.dumps(SetJamOnOffDict)
        action = Action(modelType="RadarJam", actionName='SetJamOnOff', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_SetRadarJamPolar(cls, nJamID: int, RadarJamParam: List):
        # 设置GR极化
        nJamChannelNum = 0
        ParaList = []

        ChannelID = 0
        for item in RadarJamParam:
            # 确保item是字典且包含'SetRadarJamPolar'键
            if isinstance(item, dict) and 'SetRadarJamPolar' in item:
                ChannelID += 1
                polar_type = item['SetRadarJamPolar'].get('PolarType', 3)  # 默认值为3
                # ParaList.append({
                #     'ChannelID': i,
                #     'PolarType': polar_type
                # })
                ParaList.append(ChannelID)
                ParaList.append(polar_type)
                nJamChannelNum += 1
        str_ParaList = ','.join(str(item) for item in ParaList)
        SetRadarJamPolar = f"{nJamID},{nJamChannelNum}," + str_ParaList
        SetRadarJamPolarDict = {
            "SetRadarJamPolar": SetRadarJamPolar
        }
        # json_cmd = json.dumps(dict(nJamID=nJamID,
        #                            nJamChannelNum=nJamChannelNum,
        #                            ParaList=ParaList))
        json_cmd = json.dumps(SetRadarJamPolarDict)
        action = Action(modelType="RadarJam", actionName='SetRadarJamPolar', actionDescription=json_cmd)

        return action

    @classmethod
    def make_action_SetRadarJamTarget(cls, nJamID: int, RadarJamParam: List):
        # 设置GR目标
        nJamChannelNum = 0
        ParaList = []

        ChannelID = 0
        for item in RadarJamParam:
            # 确保item是字典且包含'SetRadarJamType'键
            if isinstance(item, dict) and 'SetRadarJamType' in item:
                # 第二层保护：安全获取JamChannelList，如果不存在则用空列表
                for channel in item['SetRadarJamType'].get('JamChannelList', []):
                    ChannelID += 1
                    targetID = channel.get('SetTargetID', -1)  # 如果没有设置为无效值
                    # ParaList.append({
                    #     'ChannelID': i,
                    #     'TargetID': targetID,
                    #     'Sign': 1
                    # })
                    ParaList.append(ChannelID)
                    ParaList.append(targetID)
                    ParaList.append(1)
                    nJamChannelNum += 1

        str_ParaList = ','.join(str(item) for item in ParaList)
        SetRadarJamTrg = f"{nJamID},{nJamChannelNum}," + str_ParaList
        SetRadarJamTrgDict = {
            "SetRadarJamTrg": SetRadarJamTrg
        }
        # json_cmd = json.dumps(dict(nJamID=nJamID,
        #                            nJamChannelNum=nJamChannelNum,
        #                            ParaList=ParaList))

        json_cmd = json.dumps(SetRadarJamTrgDict)
        action = Action(modelType="RadarJam", actionName='SetRadarJamTrg', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_SetRadarJamType(cls, nJamID: int, RadarJamParam: List):
        # 设置GR目标
        nJamChannelNum = 0
        ParaList = []

        ChannelID = 0
        for item in RadarJamParam:
            if isinstance(item, dict) and 'SetRadarJamType' in item:
                # 安全获取JamChannelList，如果不存在则用空列表
                for channel in item['SetRadarJamType'].get('JamChannelList', []):
                    ChannelID += 1
                    JamType = channel.get('SetJamType', -1)
                    JamParam = channel.get('JamParam', {})
                    BandWidth = JamParam['SetJamBandWidth']
                    RF = JamParam['SetJamRF']
                    NumRF = len(RF)
                    ParaList.append(ChannelID)
                    ParaList.append(JamType)
                    ParaList.append(BandWidth)
                    nJamChannelNum += 1
                    # 构建JamPara字典
                    # jam_para = {
                    #     'BandWidth': BandWidth,
                    #     'NumRF': NumRF,
                    #     'RF': RF
                    # }
                    if JamType == 201:
                        ParaList.append(NumRF)
                        for idx in range(NumRF):
                            ParaList.append(RF[idx])

                    elif JamType == 202:
                        for idx in range(NumRF):
                            ParaList.append(RF[idx])

                    # 只有当JamType为203时，才添加ReceiveTime和EmissionTime
                    elif JamType == 203:
                        SampleCheck = JamParam.get('SampleCheck', 0)
                        ReceiveTime = JamParam.get('ReceiveTime', 0)
                        EmissionTime = JamParam.get('EmissionTime', 0)

                        ParaList.append(SampleCheck)
                        ParaList.append(ReceiveTime)
                        ParaList.append(EmissionTime)


                        # jam_para['SampleCheck'] = SampleCheck
                        # jam_para['ReceiveTime'] = ReceiveTime
                        # jam_para['EmissionTime'] = EmissionTime
                    # ParaList.append({
                    #     'ChannelID': i,
                    #     'JamType': JamType,
                    #     'JamPara': jam_para
                    # })

        str_ParaList = ','.join(str(item) for item in ParaList)
        SetRadarJamType = f"{nJamID},{nJamChannelNum}," + str_ParaList
        SetRadarJamTypeDict = {
            "SetRadarJamType": SetRadarJamType
        }
        # json_cmd = json.dumps(dict(nJamID=nJamID,
        #                            nJamChannelNum=nJamChannelNum,
        #                            ParaList=ParaList))
        json_cmd = json.dumps(SetRadarJamTypeDict)
        action = Action(modelType="RadarJam", actionName='SetRadarJamType', actionDescription=json_cmd)
        return action


class L_Actions:
    @classmethod
    def make_action_SetReconPara(cls, nRRconID: int, recon_cmds: List):
        # 设置雷达对抗ZC参数
        nPolicyNum = len(recon_cmds) / 2
        SetReconPara = []
        SetReconPara.append(nRRconID)
        SetReconPara.append(nPolicyNum)
        for i in range(1, len(recon_cmds), 2):
            # temp_dict = {}
            # temp_dict['StartFreq'] = recon_cmds[i]['SetReconRFPara']['StartFreq']
            # temp_dict['EndFreq'] = recon_cmds[i]['SetReconRFPara']['EndFreq']
            # temp_dict['WorkPitNor'] = recon_cmds[i]['SetWorkPitNor']['WorkPitNor']
            # temp_dict['DwellTime'] = recon_cmds[i]['SetDwellTime']['DwellTime']
            ParaList = []
            ParaList.append(recon_cmds[i]['SetReconRFPara']['StartFreq'])
            ParaList.append(recon_cmds[i]['SetReconRFPara']['EndFreq'])
            ParaList.append(recon_cmds[i]['SetWorkPitNor']['WorkPitNor'])
            ParaList.append(recon_cmds[i]['SetDwellTime']['DwellTime'])
            SetReconPara.append(ParaList)

        # json_cmd = json.dumps(dict(nRRconID=nRRconID,
        #                            nPolicyNum=policy_num,
        #                            ParaList=ParaList
        #                            ))
        cmd = {'SetReconPara': SetReconPara}
        # action = Action(modelType="RadarRecon", actionName='SetReconPara', actionDescription=cmd)
        return cmd

    @classmethod
    def make_action_SetAttenuator(cls, nRRconID: int, recon_cmds: List):
        # 设置雷达对抗ZC门限衰减值1
        SetAttenuator = []
        SetAttenuator.append(nRRconID)
        Attenuator = recon_cmds[1]['SetDecayValue']['decayValue1']
        # json_cmd = json.dumps(dict(nRRconID=nRRconID,
        #                            Attenuator=Attenuator))
        SetAttenuator.append(Attenuator)
        cmd = {'SetAttenuator': SetAttenuator}

        # action = Action(modelType="RadarRecon", actionName='SetAttenuator', actionDescription=cmd)
        return cmd

    @classmethod
    def make_action_SetReconPolarType(cls, nRRconID: int, recon_cmds: List):
        # 设置雷达对抗ZC极化方式
        SetReconPolarType = []
        SetReconPolarType.append(nRRconID)
        PolarType = recon_cmds[1]['SetReconPolarType']['PolarType']

        # json_cmd = json.dumps(dict(nRRconID=nRRconID,
        #                            PolarType=PolarType))

        cmd = {'SetReconPolarType': PolarType}
        # action = Action(modelType="RadarRecon", actionName='SetReconPolarType', actionDescription=cmd)
        return cmd

    @classmethod
    # NOTE TargetType部分有点问题
    def make_action_SetJamOnoff(cls, nJamID: int, RadarJamParam: List):
        """
        设置GR开关
        根据每个通道的TargetType决定输出通道数：
        - TargetType=0: 8个通道都用于输出雷达GR命令
        - TargetType=1: 4个通道用于输出雷达GR命令
        - TargetType=2: 0个通道用于输出雷达GR命令

        RadarJamParam结构: [PolicyID_dict, Config_dict, PolicyID_dict, Config_dict, ...]
        """
        nJamChannelNum = 8
        ParaList = []

        # 存储每个通道的配置
        channel_configs = {}  # {channel_id: {'onoff': x, 'target_type': y}}

        # 解析RadarJamParam，提取每个PolicyID对应的配置
        current_policy_id = -1
        for i in range(len(RadarJamParam)):
            item = RadarJamParam[i]

            if not isinstance(item, dict):
                continue

            # 检查是否是PolicyID字典
            if 'PolicyID' in item:
                current_policy_id = item['PolicyID']
                continue

            # 这是配置字典，使用PolicyID作为ChannelID
            channel_id = current_policy_id

            # 初始化配置
            if channel_id not in channel_configs and channel_id > 0:
                channel_configs[channel_id] = {
                    'onoff': 0,
                    'target_type': 0
                }

            # 从SetJamOnOff获取开关状态
            if 'SetJamOnOff' in item:
                jam_onoff = item['SetJamOnOff']
                if 'JamChannelList' in jam_onoff and len(jam_onoff['JamChannelList']) > 0:
                    channel_info = jam_onoff['JamChannelList'][0]
                    if channel_id > 0:
                        channel_configs[channel_id]['onoff'] = channel_info.get('Onoff', 0)

            # 从SetRadarJamType获取TargetType
            if 'SetRadarJamType' in item:
                jam_type = item['SetRadarJamType']
                if 'JamChannelList' in jam_type and len(jam_type['JamChannelList']) > 0:
                    channel_info = jam_type['JamChannelList'][0]
                    if channel_id > 0:
                        channel_configs[channel_id]['target_type'] = channel_info.get('TargetType', 0)

        # NOTE 每个通道都有一个target_type，还是只有一个大的target_type，用于判断
        # NOTE 目前 确定所有通道中的最大TargetType（决定整体策略）
        # 如果有任何通道是TargetType=2，则所有通道都不输出
        # 如果最大是TargetType=1，则只有前4个通道输出
        # 如果都是TargetType=0，则8个通道都输出
        max_target_type = 0
        for config in channel_configs.values():
            if config['target_type'] > max_target_type:
                max_target_type = config['target_type']

        # 根据max_target_type决定可用通道数
        if max_target_type == 0:
            max_active_channels = 8  # 8个通道都可用
        elif max_target_type == 1:
            max_active_channels = 4  # 只有4个通道可用
        else:  # max_target_type == 2
            max_active_channels = 0  # 没有通道用于雷达GR

        # 生成最终的ParaList
        for i in range(1, nJamChannelNum + 1):
            if i in channel_configs:
                config = channel_configs[i]
                target_type = config['target_type']
                onoff = config['onoff']

                # 根据整体策略决定Launch值
                if i <= max_active_channels:
                    launch = onoff  # 在可用范围内，保持原设置
                else:
                    launch = 0  # 超出可用范围，强制关闭

                ParaList.append({
                    'ChannelID': i,
                    'TargetType': target_type,
                    'Launch': launch
                })
            else:
                # 未配置的通道，默认关闭
                ParaList.append({
                    'ChannelID': i,
                    'TargetType': 0,
                    'Launch': 0
                })

        json_cmd = json.dumps(dict(
            nJamID=nJamID,
            nJamChannelNum=nJamChannelNum,
            ParaList=ParaList
        ))

        action = Action(modelType="RadarJam", actionName='SetJamOnOff', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_SetRadarJamPolar(cls, nJamID: int, RadarJamParam: List):
        # 设置GR极化
        SetRadarJamPolar = []
        SetRadarJamPolar.append(nJamID)
        nJamChannelNum = 8
        SetRadarJamPolar.append(nJamChannelNum)
        ParaList = []

        i = 0
        for item in RadarJamParam:
            # 确保item是字典且包含'SetRadarJamPolar'键
            if isinstance(item, dict) and 'SetRadarJamPolar' in item:
                i += 1
                polar_type = item['SetRadarJamPolar'].get('PolarType', 3)  # 默认值为3
                ParaList.append({
                    'ChannelID': i,
                    'PolarType': polar_type
                })
        # 补全剩余的通道到8个
        for i in range(i + 1, nJamChannelNum + 1):
            ParaList.append({
                'ChannelID': i,
                'PolarType': 3
            })
        # json_cmd = json.dumps(dict(nJamID=nJamID,
        #                            nJamChannelNum=nJamChannelNum,
        #                            ParaList=ParaList))
        # action = Action(modelType="RadarJam", actionName='SetRadarJamPolar', actionDescription=json_cmd)
        SetRadarJamPolar.append(ParaList)
        cmd = {'SetRadarJamPolar': SetRadarJamPolar}
        return cmd

    @classmethod
    def make_action_SetRadarJamTarget(cls, nJamID: int, RadarJamParam: List):
        # 设置GR目标
        SetRadarJamTrg = []
        SetRadarJamTrg.append(nJamID)
        nJamChannelNum = 8
        SetRadarJamTrg.append(nJamChannelNum)
        ParaList = []

        i = 0
        for item in RadarJamParam:
            # 确保item是字典且包含'SetRadarJamType'键
            if isinstance(item, dict) and 'SetRadarJamType' in item:
                # 第二层保护：安全获取JamChannelList，如果不存在则用空列表
                for channel in item['SetRadarJamType'].get('JamChannelList', []):
                    i += 1
                    targetID = channel.get('SetTargetID', -1)  # 如果没有设置为无效值
                    ParaList.append({
                        'ChannelID': i,
                        'TargetID': targetID,
                        'Sign': 1
                    })
        # 补全剩余的通道到8个
        for i in range(i + 1, nJamChannelNum + 1):
            ParaList.append({
                'ChannelID': i,
                'TargetID': -1,
                'Sign': 0
            })
        # json_cmd = json.dumps(dict(nJamID=nJamID,
        #                            nJamChannelNum=nJamChannelNum,
        #                            ParaList=ParaList))
        # action = Action(modelType="RadarJam", actionName='SetRadarJamTrg', actionDescription=json_cmd)
        SetRadarJamTrg.append(ParaList)
        cmd = {'SetRadarJamTarget': SetRadarJamTrg}

        return cmd

    @classmethod
    def make_action_SetRadarJamType(cls, nJamID: int, RadarJamParam: List):
        # 设置GR目标
        SetRadarJamType = []
        SetRadarJamType.append(nJamID)
        nJamChannelNum = 8
        SetRadarJamType.append(nJamChannelNum)
        ParaList = []

        i = 0
        for item in RadarJamParam:
            if isinstance(item, dict) and 'SetRadarJamType' in item:
                # 安全获取JamChannelList，如果不存在则用空列表
                for channel in item['SetRadarJamType'].get('JamChannelList', []):
                    i += 1
                    JamType = channel.get('SetJamType', -1)
                    JamParam = channel.get('JamParam', {})
                    BandWidth = JamParam['SetJamBandWidth']
                    RF = JamParam['SetJamRF']
                    NumRF = len(RF)

                    # 构建JamPara字典
                    jam_para = {
                        'BandWidth': BandWidth,
                        'NumRF': NumRF,
                        'RF': RF
                    }
                    # 只有当JamType为103时，才添加ReceiveTime和EmissionTime
                    if JamType == 103:
                        SampleCheck = JamParam.get('SampleCheck', 0)
                        ReceiveTime = JamParam.get('ReceiveTime', 0)
                        EmissionTime = JamParam.get('EmissionTime', 0)
                        jam_para['SampleCheck'] = SampleCheck
                        jam_para['ReceiveTime'] = ReceiveTime
                        jam_para['EmissionTime'] = EmissionTime

                    ParaList.append({
                        'ChannelID': i,
                        'JamType': JamType,
                        'JamPara': jam_para
                    })
        # 补全剩余的通道到8个
        for i in range(i + 1, nJamChannelNum + 1):
            ParaList.append({
                'ChannelID': i,
                'JamType': -1,
                'JamPara': {
                    'BandWidth': -1,
                    'NumRF': 0,
                    'RF': []
                }
            })

        # json_cmd = json.dumps(dict(nJamID=nJamID,
        #                            nJamChannelNum=nJamChannelNum,
        #                            ParaList=ParaList))
        # action = Action(modelType="RadarJam", actionName='SetRadarJamType', actionDescription=json_cmd)
        # return action
        SetRadarJamType.append(ParaList)
        cmd = {'SetRadarJamType': SetRadarJamType}
        return cmd