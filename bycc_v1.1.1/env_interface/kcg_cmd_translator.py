from bycc.environment.translator.cmd_translator import CmdTranslator
from env_interface.env.ewx_cmds.kcg_cmd import XKU_Actions, L_Actions


class XKUCmdTranslator(CmdTranslator):
    def __init__(self):
        self.ReconID = None
        self.recon_KcgSubTaskType = None
        self.recon_KcgTaskType = None
        self.JammerID = None
        self.jam_KcgSubTaskType = None
        self.jam_KcgTaskType = None
        self.recon_cmds = []
        self.jam_cmds = []

    # 将网络的输出与rule的策略拼成同一级
    # 将mission输出的命令 与rule agent输出的命令拼接在一起 组成一个最终的命令
    def translate(self, std_cmd, raw_obs):
        total_cmds = {'1': []}
        # temp_cmds = {'SetReconParam': {}, 'SetJamParam': {}}
        recon_param_rule_list = []
        recon_param_agent_dict = {}
        jam_param_rule_list = []
        jam_param_agent_list = []
        # 红方为1
        red_side = std_cmd['1']
        # 循环取值
        for item in red_side:
            # 处理ZC参数 - Rule
            if "SetRadarReconParam_Rule" in item and item['SetRadarReconParam_Rule']['Scheduler'] == True:
                # self.recon_KcgTaskType = item['SetRadarReconParam_Rule']['KcgTaskType']
                # self.recon_KcgSubTaskType = item['SetRadarReconParam_Rule']['KcgSubTaskType']
                self.ReconID = item['SetRadarReconParam_Rule']['ReconID']
                recon_param_rule_list = item['SetRadarReconParam_Rule']['SetReconParaList']
            # 处理ZC参数 - Agent
            if "SetRadarReconParam_Agent" in item:
                recon_param_agent_dict = item["SetRadarReconParam_Agent"]
            # 处理GR参数 - Rule
            if "SetRadarJamParam_Rule" in item and item['SetRadarJamParam_Rule']['Scheduler'] == True:
                # self.jam_KcgTaskType = item['SetRadarJamParam_Rule']['KcgTaskType']
                # self.jam_KcgSubTaskType = item['SetRadarJamParam_Rule']['KcgSubTaskType']
                self.JammerID = item['SetRadarJamParam_Rule']['JammerID']
                jam_param_rule_list = item['SetRadarJamParam_Rule']['SetRadarJamParaList']
            # 处理GR参数 - Agent
            if "SetRadarJamParam_Agent" in item:
                jam_param_agent_list = item["SetRadarJamParam_Agent"]

        self.recon_cmds = self.reconCmdProcess(recon_param_rule_list, recon_param_agent_dict)
        self.jam_cmds = self.JamCmdProcess(jam_param_rule_list, jam_param_agent_list)

        # ZC和GR都进行，则需要再拼一次
        if len(self.recon_cmds) > 0 and len(self.jam_cmds) > 0:
            total_cmds['1'].append(
                XKU_Actions.make_action_SetReconPara(self.ReconID, self.recon_cmds))
            print("*{}:{}".format(XKU_Actions.make_action_SetReconPara(self.ReconID, self.recon_cmds).actionName,
                                 XKU_Actions.make_action_SetReconPara(self.ReconID, self.recon_cmds).actionDescription))
            total_cmds['1'].append(
                XKU_Actions.make_action_SetAttenuator(self.ReconID, self.recon_cmds))
            print("*{}:{}".format(XKU_Actions.make_action_SetAttenuator(self.ReconID, self.recon_cmds).actionName,
                                 XKU_Actions.make_action_SetAttenuator(self.ReconID,
                                                                       self.recon_cmds).actionDescription))
            total_cmds['1'].append(
                XKU_Actions.make_action_SetReconPolarType(self.ReconID, self.recon_cmds))
            print("*{}:{}".format(XKU_Actions.make_action_SetReconPolarType(self.ReconID, self.recon_cmds).actionName,
                                 XKU_Actions.make_action_SetReconPolarType(self.ReconID,
                                                                           self.recon_cmds).actionDescription))
            total_cmds['1'].append(
                XKU_Actions.make_action_SetJamOnoff(self.JammerID, self.jam_cmds))
            print("*{}:{}".format(XKU_Actions.make_action_SetJamOnoff(self.JammerID, self.jam_cmds).actionName,
                                 XKU_Actions.make_action_SetJamOnoff(self.JammerID, self.jam_cmds).actionDescription))
            total_cmds['1'].append(
                XKU_Actions.make_action_SetRadarJamPolar(self.JammerID, self.jam_cmds))
            print("*{}:{}".format(XKU_Actions.make_action_SetRadarJamPolar(self.JammerID, self.jam_cmds).actionName,
                                 XKU_Actions.make_action_SetRadarJamPolar(self.JammerID, self.jam_cmds).actionDescription))
            total_cmds['1'].append(
                XKU_Actions.make_action_SetRadarJamTarget(self.JammerID, self.jam_cmds))
            print("*{}:{}".format(XKU_Actions.make_action_SetRadarJamTarget(self.JammerID, self.jam_cmds).actionName,
                                 XKU_Actions.make_action_SetRadarJamTarget(self.JammerID,
                                                                          self.jam_cmds).actionDescription))
            total_cmds['1'].append(
                XKU_Actions.make_action_SetRadarJamType(self.JammerID, self.jam_cmds))
            print("*{}:{}".format(XKU_Actions.make_action_SetRadarJamType(self.JammerID, self.jam_cmds).actionName,
                                 XKU_Actions.make_action_SetRadarJamType(self.JammerID,
                                                                          self.jam_cmds).actionDescription))
            # temp_cmds['SetReconParam'] = self._build_recon_command()
            # temp_cmds['SetJamParam'] = self._build_jam_command()
        # ZC命令
        elif len(self.recon_cmds) > 0 and len(self.jam_cmds) == 0:
            # temp_cmds['SetReconParam'] = self._build_recon_command()
            total_cmds['1'].append(
                XKU_Actions.make_action_SetReconPara(self.ReconID, self.recon_cmds))
            print("{}:{}".format(XKU_Actions.make_action_SetReconPara(self.ReconID, self.recon_cmds).actionName,
                                 XKU_Actions.make_action_SetReconPara(self.ReconID, self.recon_cmds).actionDescription))
            total_cmds['1'].append(
                XKU_Actions.make_action_SetAttenuator(self.ReconID, self.recon_cmds))
            print("{}:{}".format(XKU_Actions.make_action_SetAttenuator(self.ReconID, self.recon_cmds).actionName,
                                 XKU_Actions.make_action_SetAttenuator(self.ReconID,
                                                                       self.recon_cmds).actionDescription))
            total_cmds['1'].append(
                XKU_Actions.make_action_SetReconPolarType(self.ReconID, self.recon_cmds))
            print("{}:{}".format(XKU_Actions.make_action_SetReconPolarType(self.ReconID, self.recon_cmds).actionName,
                                 XKU_Actions.make_action_SetReconPolarType(self.ReconID,
                                                                           self.recon_cmds).actionDescription))
        # GR命令
        elif len(self.recon_cmds) == 0 and len(self.jam_cmds) > 0:
            # temp_cmds['SetJamParam'] = self._build_jam_command()
            total_cmds['1'].append(
                XKU_Actions.make_action_SetJamOnoff(self.JammerID, self.jam_cmds))
            print("{}:{}".format(XKU_Actions.make_action_SetJamOnoff(self.JammerID, self.jam_cmds).actionName,
                                 XKU_Actions.make_action_SetJamOnoff(self.JammerID, self.jam_cmds).actionDescription))
            total_cmds['1'].append(
                XKU_Actions.make_action_SetRadarJamPolar(self.JammerID, self.jam_cmds))
            print("{}:{}".format(XKU_Actions.make_action_SetRadarJamPolar(self.JammerID, self.jam_cmds).actionName,
                                 XKU_Actions.make_action_SetRadarJamPolar(self.JammerID,
                                                                          self.jam_cmds).actionDescription))
            total_cmds['1'].append(
                XKU_Actions.make_action_SetRadarJamTarget(self.JammerID, self.jam_cmds))
            print("{}:{}".format(XKU_Actions.make_action_SetRadarJamTarget(self.JammerID, self.jam_cmds).actionName,
                                 XKU_Actions.make_action_SetRadarJamTarget(self.JammerID,
                                                                           self.jam_cmds).actionDescription))
            total_cmds['1'].append(
                XKU_Actions.make_action_SetRadarJamType(self.JammerID, self.jam_cmds))
            print("{}:{}".format(XKU_Actions.make_action_SetRadarJamType(self.JammerID, self.jam_cmds).actionName,
                                 XKU_Actions.make_action_SetRadarJamType(self.JammerID,
                                                                         self.jam_cmds).actionDescription))

        # total_cmds['1'].append({'SetReconParam':temp_cmds['SetReconParam']})
        # total_cmds['1'].append({'SetJamParam':temp_cmds['SetJamParam']})
        # 对cmds进行包装

        return total_cmds

    # 处理ZC命令
    def reconCmdProcess(self, recon_param_rule_list, recon_param_agent_dict):
        cmds = []
        # item是字典
        # 对recon_param_rule_list进行保护
        if len(recon_param_rule_list) == 0:
            pass
        else:
            for item in recon_param_rule_list:
                if 'PolicyID' in item:
                    # 先将PolicyID放进列表中
                    cmds.append(item)
                    continue
                else:
                    item['SetDecayValue'] = recon_param_agent_dict
                    cmds.append(item)
        return cmds

    # 处理GR命令
    def JamCmdProcess(self, jam_param_rule_list, jam_param_agent_list):
        cmds = []
        idx = 0
        # jam_param_rule_list进行保护
        if len(jam_param_rule_list) == 0:
            pass
        else:
            for rule_item in jam_param_rule_list:
                if 'PolicyID' in rule_item:
                    # 先将PolicyID放进列表中
                    cmds.append(rule_item)
                    continue
                else:
                    # 安全地获取 agent_list 中的数据
                    if idx < len(jam_param_agent_list):
                        agent_item = jam_param_agent_list[idx]

                        # 设置 JamType
                        rule_item['SetRadarJamType']['JamChannelList'][0]['SetJamType'] = \
                            agent_item.get('SetJamType', -1)

                        # 确保 JamParam 字典存在
                        if 'JamParam' not in rule_item['SetRadarJamType']['JamChannelList'][0]:
                            rule_item['SetRadarJamType']['JamChannelList'][0]['JamParam'] = {}

                        # 设置 BandWidth
                        if 'JamParam' in agent_item:
                            rule_item['SetRadarJamType']['JamChannelList'][0]['JamParam']['SetJamBandWidth'] = \
                                agent_item['JamParam'].get('SetJamBandWidth', -1)
                        else:
                            rule_item['SetRadarJamType']['JamChannelList'][0]['JamParam']['SetJamBandWidth'] = -1

                        # 根据 JamType 决定是否设置 SetDutyCycle
                        jam_type = agent_item.get('SetJamType', -1)

                        # 只有 JamType 为 203 时才设置 接发窗
                        if jam_type == 203:
                            rule_item['SetRadarJamType']['JamChannelList'][0]['JamParam']['SampleCheck'] = \
                                agent_item['SampleCheck']
                            rule_item['SetRadarJamType']['JamChannelList'][0]['JamParam']['ReceiveTime'] = \
                                agent_item['ReceiveTime']
                            rule_item['SetRadarJamType']['JamChannelList'][0]['JamParam']['EmissionTime'] = \
                                agent_item['EmissionTime']
                        # 用于循环取出网络的值
                        idx += 1
                    cmds.append(rule_item)
        return cmds

    # def _build_recon_command(self):
    #     """构建ZC命令"""
    #     return {
    #         'KcgTaskType': self.recon_KcgTaskType,
    #         'KcgSubTaskType': self.recon_KcgSubTaskType,
    #         'ReconID': self.ReconID,
    #         'SetRadarReconParaList': self.recon_cmds
    #     }
    #
    # def _build_jam_command(self):
    #     """构建GR命令"""
    #     return {
    #         'KcgTaskType': self.jam_KcgTaskType,
    #         'KcgSubTaskType': self.jam_KcgSubTaskType,
    #         'JamID': self.JammerID,
    #         'SetRadarJamParaList': self.jam_cmds
    #     }


class LCmdTranslator(CmdTranslator):
    def __init__(self):
        self.ReconID = None
        self.recon_KcgSubTaskType = None
        self.recon_KcgTaskType = None
        self.JammerID = None
        self.jam_KcgSubTaskType = None
        self.jam_KcgTaskType = None
        self.recon_cmds = []
        self.jam_cmds = []

    # 将网络的输出与rule的策略拼成同一级
    # 将mission输出的命令 与rule agent输出的命令拼接在一起 组成一个最终的命令
    def translate(self, std_cmd, raw_obs):
        total_cmds = {'1': []}
        # temp_cmds = {'SetReconParam': {}, 'SetJamParam': {}}
        recon_param_rule_list = []
        recon_param_agent_dict = {}
        jam_param_rule_list = []
        jam_param_agent_list = []
        # 红方为1
        red_side = std_cmd['1']
        # 循环取值
        for item in red_side:
            # 处理ZC参数 - Rule
            if "SetRadarReconParam_Rule" in item and item['SetRadarReconParam_Rule']['Scheduler'] == True:
                # self.recon_KcgTaskType = item['SetRadarReconParam_Rule']['KcgTaskType']
                # self.recon_KcgSubTaskType = item['SetRadarReconParam_Rule']['KcgSubTaskType']
                self.ReconID = item['SetRadarReconParam_Rule']['ReconID']
                recon_param_rule_list = item['SetRadarReconParam_Rule']['SetReconParaList']
            # 处理ZC参数 - Agent
            if "SetRadarReconParam_Agent" in item:
                recon_param_agent_dict = item["SetRadarReconParam_Agent"]
            # 处理GR参数 - Rule
            if "SetRadarJamParam_Rule" in item and item['SetRadarJamParam_Rule']['Scheduler'] == True:
                # self.jam_KcgTaskType = item['SetRadarJamParam_Rule']['KcgTaskType']
                # self.jam_KcgSubTaskType = item['SetRadarJamParam_Rule']['KcgSubTaskType']
                self.JammerID = item['SetRadarJamParam_Rule']['JammerID']
                jam_param_rule_list = item['SetRadarJamParam_Rule']['SetRadarJamParaList']
            # 处理GR参数 - Agent
            if "SetRadarJamParam_Agent" in item:
                jam_param_agent_list = item["SetRadarJamParam_Agent"]

        self.recon_cmds = self.reconCmdProcess(recon_param_rule_list, recon_param_agent_dict)
        self.jam_cmds = self.JamCmdProcess(jam_param_rule_list, jam_param_agent_list)

        # ZC和GR都进行，则需要再拼一次
        if len(self.recon_cmds) > 0 and len(self.jam_cmds) > 0:
            total_cmds['1'].append(
                L_Actions.make_action_SetReconPara(self.ReconID, self.recon_cmds))
            total_cmds['1'].append(
                L_Actions.make_action_SetAttenuator(self.ReconID, self.recon_cmds))
            total_cmds['1'].append(
                L_Actions.make_action_SetReconPolarType(self.ReconID, self.recon_cmds))
            total_cmds['1'].append(
                L_Actions.make_action_SetJamOnoff(self.JammerID, self.jam_cmds))
            total_cmds['1'].append(
                L_Actions.make_action_SetRadarJamPolar(self.JammerID, self.jam_cmds))
            total_cmds['1'].append(
                L_Actions.make_action_SetRadarJamTarget(self.JammerID, self.jam_cmds))
            total_cmds['1'].append(
                L_Actions.make_action_SetRadarJamType(self.JammerID, self.jam_cmds))
            # temp_cmds['SetReconParam'] = self._build_recon_command()
            # temp_cmds['SetJamParam'] = self._build_jam_command()
        # ZC命令
        elif len(self.recon_cmds) > 0 and len(self.jam_cmds) == 0:
            # temp_cmds['SetReconParam'] = self._build_recon_command()
            total_cmds['1'].append(
                L_Actions.make_action_SetReconPara(self.ReconID, self.recon_cmds))
            total_cmds['1'].append(
                L_Actions.make_action_SetAttenuator(self.ReconID, self.recon_cmds))
            total_cmds['1'].append(
                L_Actions.make_action_SetReconPolarType(self.ReconID, self.recon_cmds))
        # GR命令
        elif len(self.recon_cmds) == 0 and len(self.jam_cmds) > 0:
            # temp_cmds['SetJamParam'] = self._build_jam_command()
            total_cmds['1'].append(
                L_Actions.make_action_SetJamOnoff(self.JammerID, self.jam_cmds))
            total_cmds['1'].append(
                L_Actions.make_action_SetRadarJamPolar(self.JammerID, self.jam_cmds))
            total_cmds['1'].append(
                L_Actions.make_action_SetRadarJamTarget(self.JammerID, self.jam_cmds))
            total_cmds['1'].append(
                L_Actions.make_action_SetRadarJamType(self.JammerID, self.jam_cmds))

        # total_cmds['1'].append({'SetReconParam':temp_cmds['SetReconParam']})
        # total_cmds['1'].append({'SetJamParam':temp_cmds['SetJamParam']})
        # 对cmds进行包装
        return total_cmds

    # 处理ZC命令
    def reconCmdProcess(self, recon_param_rule_list, recon_param_agent_dict):
        cmds = []
        # item是字典
        # 对recon_param_rule_list进行保护
        if len(recon_param_rule_list) == 0:
            pass
        else:
            for item in recon_param_rule_list:
                if 'PolicyID' in item:
                    # 先将PolicyID放进列表中
                    cmds.append(item)
                    continue
                else:
                    item['SetDecayValue'] = recon_param_agent_dict
                    cmds.append(item)
        return cmds

    # 处理GR命令
    def JamCmdProcess(self, jam_param_rule_list, jam_param_agent_list):
        cmds = []
        idx = 0
        # jam_param_rule_list进行保护
        if len(jam_param_rule_list) == 0:
            pass
        else:
            for rule_item in jam_param_rule_list:
                if 'PolicyID' in rule_item:
                    # 先将PolicyID放进列表中
                    cmds.append(rule_item)
                    continue
                else:
                    # 安全地获取 agent_list 中的数据
                    if idx < len(jam_param_agent_list):
                        agent_item = jam_param_agent_list[idx]

                        # 设置 JamType
                        rule_item['SetRadarJamType']['JamChannelList'][0]['SetJamType'] = \
                            agent_item.get('SetJamType', -1)

                        # 确保 JamParam 字典存在
                        if 'JamParam' not in rule_item['SetRadarJamType']['JamChannelList'][0]:
                            rule_item['SetRadarJamType']['JamChannelList'][0]['JamParam'] = {}

                        # 设置 BandWidth
                        if 'JamParam' in agent_item:
                            rule_item['SetRadarJamType']['JamChannelList'][0]['JamParam']['SetJamBandWidth'] = \
                                agent_item['JamParam'].get('SetJamBandWidth', -1)
                        else:
                            rule_item['SetRadarJamType']['JamChannelList'][0]['JamParam']['SetJamBandWidth'] = -1

                        # 根据 JamType 决定是否设置 SetDutyCycle
                        jam_type = agent_item.get('SetJamType', -1)

                        # 只有 JamType 为 203 时才设置 SetDutyCycle
                        if jam_type == 203 and 'SetDutyCycle' in agent_item:
                            rule_item['SetRadarJamType']['JamChannelList'][0]['JamParam']['SetDutyCycle'] = \
                                agent_item['SetDutyCycle']
                        # 用于循环取出网络的值
                        idx += 1
                    cmds.append(rule_item)
        return cmds

    # def _build_recon_command(self):
    #     """构建ZC命令"""
    #     return {
    #         'KcgTaskType': self.recon_KcgTaskType,
    #         'KcgSubTaskType': self.recon_KcgSubTaskType,
    #         'ReconID': self.ReconID,
    #         'SetRadarReconParaList': self.recon_cmds
    #     }
    #
    # def _build_jam_command(self):
    #     """构建GR命令"""
    #     return {
    #         'KcgTaskType': self.jam_KcgTaskType,
    #         'KcgSubTaskType': self.jam_KcgSubTaskType,
    #         'JamID': self.JammerID,
    #         'SetRadarJamParaList': self.jam_cmds
    #     }
