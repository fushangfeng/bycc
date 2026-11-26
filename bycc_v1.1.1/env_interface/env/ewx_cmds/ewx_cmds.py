import json
from env_interface.protos.output.ai_pb2 import Action
from typing import Union, Dict, List


def make_action(actionName: str, actionDescriptionDict: Dict):
    # 发送智能体动作报文
    action_discription_json = json.dumps(actionDescriptionDict)
    action = Action(actionName=actionName, actionDescription=action_discription_json)
    return action


# Updated by Gaoxiang Wu
class PlatActions:

    # debug
    @classmethod
    def make_action_SetWorkModeAction(cls, nLeaderPlatId: int, nSetWorkModeAction: List):
        # 设置工作模式
        json_cmd = json.dumps(dict(id=nLeaderPlatId,
                                   MissionMode=nSetWorkModeAction[0]))  #
        print("id,MissionMode"+str(nLeaderPlatId)+str(",")+str(nSetWorkModeAction[0]))
        action = Action(modelType="Multifunction", actionName='SetWorkModeAction', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_SetRecoPara(cls, nLeaderPlatId: int, nSetRecoPara: List):
        # 设置ZC参数
        json_cmd = json.dumps(dict(id=nLeaderPlatId,
                                   Type=nSetRecoPara[0],
                                   SightDistance=nSetRecoPara[1],
                                   Filter=nSetRecoPara[2],
                                   AttenValue=nSetRecoPara[3],
                                   PolarizeIdentity=nSetRecoPara[4]))  #
        print("id,Type,SightDistance,Filter,AttenValue,PolarizeIdentity:" + str(nLeaderPlatId)+str(",")+str(nSetRecoPara))
        action = Action(modelType="RadarRecon", actionName='SetRecoPara', actionDescription=json_cmd)
        return action

    # def make_action_SetRecoFilter(cls, nLeaderPlatId:int, nSetRecoFilter:List):
    #     # 设置工作模式
    #     json_cmd = json.dumps(dict(nPlatId=nLeaderPlatId,
    #                                nWingPlatList=nSetRecoFilter))  #
    #     action = Action(modelType="RadarRecon", actionName='SetRecoFilter', actionDescription=json_cmd)
    #     return action
    @classmethod
    def make_action_SetRecSpectrThresh(cls, nLeaderPlatId: int, nSetRecSpectrThresh: List):
        # 频谱门限控制（仅对样机）
        json_cmd = json.dumps(dict(id=nLeaderPlatId,
                                   FixDetectThreldSet=nSetRecSpectrThresh[0]))  #
        action = Action(modelType="RadarRecon", actionName='SetRecSpectrThresh', actionDescription=json_cmd)
        return action

    # @classmethod
    # def make_action_SetJamOnoff(cls, nLeaderPlatId:int, nSetJamOnoff:List):
    #     # GR启停控制
    #     json_cmd = json.dumps(dict(nPlatId=nLeaderPlatId,
    #                                nWingPlatList=nSetJamOnoff))  #
    #     action = Action(modelType="RadarRecon", actionName='SetJamOnoff', actionDescription=json_cmd)
    #     return action

    @classmethod
    def make_action_SetJamTrgPra(cls, nLeaderPlatId: int, nSetJamTrgPra: List):
        # GR引导参数控制
        json_cmd = json.dumps(dict(id=nLeaderPlatId,
                                   Type=nSetJamTrgPra[0],
                                   onoff=nSetJamTrgPra[1],
                                   SubArr=nSetJamTrgPra[2],
                                   DecisionModel=nSetJamTrgPra[3]))  #
        action = Action(modelType="RadarJam", actionName='SetJamTrgPra', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_SetRadarJamType(cls, nLeaderPlatId: int, nSetRadarJamType: List):
        # 雷达GR样式控制
        json_cmd = json.dumps(dict(id=nLeaderPlatId,
                                   Type=nSetRadarJamType[0],
                                   TargetID=nSetRadarJamType[1],
                                   Fangwei=nSetRadarJamType[2],
                                   Fuyang=nSetRadarJamType[3],
                                   Pinlv=nSetRadarJamType[4],
                                   Jihua=nSetRadarJamType[5],
                                   GanraoYangshi=nSetRadarJamType[6],
                                   GanraoCanshu=nSetRadarJamType[7:-1]))  #
        action = Action(modelType="RadarJam", actionName='SetRadarJamType', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_SetRadarAntiJamCtrl(cls, nLeaderPlatId: int, nSetRadarAntiJam: List):
        # 抗GR控制
        json_cmd = json.dumps(dict(nPlatId=nLeaderPlatId,
                                   Type=nSetRadarAntiJam[0]))  #
        action = Action(modelType="Radar", actionName='SetRadarAntiJamCtrl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_SetKcgSdjTimeCtrl(cls, nLeaderPlatId: int, nSetKcgSdjTimeCtrl: List):
        # 侦探干时间控制
        json_cmd = json.dumps(dict(id=nLeaderPlatId,
                                   Zhouqi=nSetKcgSdjTimeCtrl[0],
                                   ZGB=nSetKcgSdjTimeCtrl[1]))  #
        action = Action(modelType="Multifunction", actionName='SetKcgSdjTimeCtrl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_SetKcgSdjSubModeCtrl(cls, nLeaderPlatId: int, nSetKcgSdjSubModeCtrl: List):
        # 小模式控制
        json_cmd = json.dumps(dict(id=nLeaderPlatId,
                                   ZCmode=nSetKcgSdjSubModeCtrl[0],
                                   TCmode=nSetKcgSdjSubModeCtrl[1],
                                   GRmode=nSetKcgSdjSubModeCtrl[2]))  #
        action = Action(modelType="Multifunction", actionName='SetKcgSdjSubModeCtrl', actionDescription=json_cmd)
        return action


    # debug

    # Update by Gaoxiang Wu
    # 机动平台编队控制指令
    @classmethod
    def make_action_PlatFormCtl(cls, nLeaderPlatId: int, nWingPlatList: List):
        # nWingPlatList为僚机id组成的List
        json_cmd = json.dumps(dict(nPlatId=nLeaderPlatId,
                                   nWingPlatList=nWingPlatList))  #
        action = Action(modelType="PlatForm", actionName='PlatFormCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_FormStyleCtl(cls, nLeaderPlatId: int, FormationInfo: List):
        """
        FormationInfo是编队类型包含参数所组成的List(队形名(string)、编队相邻平台间隔(double)、夹角度数(double)、顶角度数(double)、排数(int))
        固定长度顺序传值，不需要的值需占位
        {"VLine": ”纵向直线”，编队内相邻平台间隔（double）},
		{"ALine": ”横向直线”，编队内相邻平台间隔（double）},
		{"V": ”V型”，夹角度数(double)：范围[0,180]，编队内相邻平台间隔（double）},
		{"X": ”X型”，编队内相邻平台间隔（double）},
		{"Square": ” 矩形”，排数(int)：范围[1,N],N为编队内平台个数，编队内相邻平台间隔（double）},
		{"Triangle": ”三角形”，顶角度数(double)：范围[0,180]，编队内相邻平台间隔（double）},
		{"Wedeg": ”楔形”，夹角度数(double)：范围[0,90]，编队内相邻平台间隔（double）}
        """
        json_cmd = json.dumps(dict(nLeaderPlatId=nLeaderPlatId,
                                   nFormationShape=FormationInfo))  #
        action = Action(modelType="PlatForm", actionName='FormStyleCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_FormDeploymentCtl(cls, nFormId: int, nFlyPath: List):
        # nFlyPath是路径类型包含参数所组成的List
        # (起始点(WsfGeoPoint)航向角（double）路径长度（double）路径夹角（double）路径宽度（double）速度（double）加速度（double）转弯半径（double）转弯方向（double）正面距离（double）相对方位（double）num（double）)
        json_cmd = json.dumps(dict(nFormId=nFormId,
                                   nDirection=nFlyPath))  #
        action = Action(modelType="PlatForm", actionName='FormDeploymentCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_GrdPlatFormCtl(cls, nLeaderPlatId, nWingPlatList):
        # nWingPlatList为从设备id组成的List
        json_cmd = json.dumps(dict(nLeaderPlatId=nLeaderPlatId,
                                   nWingPlatList=nWingPlatList))  #
        action = Action(modelType="GroundForm", actionName='GrdPlatFormCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_GrdFormDeploymentCtl(cls, nLeaderPlatId: int, nFormationShape: List):
        # nFormationShape是编队类型包含参数所组成的List(队形名(string)、编队相邻平台间隔(double)、夹角度数(double)、顶角度数(double)、排数(int))
        json_cmd = json.dumps(dict(nLeaderPlatId=nLeaderPlatId,
                                   nFormationShape=nFormationShape))  #
        action = Action(modelType="GroundForm", actionName='GrdFormDeploymentCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_GrdFormDirCtl(cls, nFormId: int, nDirection: List):
        json_cmd = json.dumps(dict(nFormId=nFormId,
                                   nDirection=nDirection))  #
        action = Action(modelType="GroundForm", actionName='GrdFormDirCtl', actionDescription=json_cmd)
        return action

    # 地面平台的控制指令
    @classmethod
    def make_action_PlatDirCtl(cls, nPlatId: int, direction: float):
        json_cmd = json.dumps(dict(nPlatId=nPlatId,
                                   pDirection=direction, ))  #
        action = Action(modelType="GroundPlat", actionName='PlatDirCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_PlatPosCtl(cls, nPlatId: int, pPostion: List):
        json_cmd = json.dumps(dict(nPlatId=nPlatId,
                                   pPostion=pPostion, ))  #
        action = Action(modelType="GroundPlat", actionName='PlatPosCtl', actionDescription=json_cmd)
        return action

    # Update by Gaoxiang Wu
    # 1v1 空战增加动作函数
    @classmethod
    def make_action_SetPlatDir(cls, nPlatId, speed: int, direction: List):
        json_cmd = json.dumps(dict(nPlatId=nPlatId,
                                   pSpeed=speed,
                                   pDirection=direction, ))  #
        action = Action(modelType="PlanePlat", actionName='PlatDirCtl', actionDescription=json_cmd)
        return action

    @classmethod
    # 纬度、经度、高度
    def make_action_SetPlatPos(cls, nPlatId, speed, postion=[0, 0, 0]):
        json_cmd = json.dumps(dict(nPlatId=nPlatId,
                                   pSpeed=speed,
                                   pPostion=postion, ))
        action = Action(modelType="PlanePlat", actionName='PlatPosCtl', actionDescription=json_cmd)
        return action

    # Update by Gaoxiang Wu
    @classmethod
    def make_action_SetPlatAutoDodge(cls, nPlatId, open=0):
        json_cmd = json.dumps(dict(nPlatId=nPlatId,
                                   bopen=open, ))
        action = Action(modelType="PlanePlat", actionName='PlatAutoDodgeCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_SetPlatAutoFire(cls, nPlatId, open=False):
        # 飞机打弹使能控制
        json_cmd = json.dumps(dict(nPlatId=nPlatId,
                                   bopen=open, ))
        action = Action(modelType="PlanePlat", actionName='PlatAutoFireCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_SetPlatFireCtl(cls, nPlatId, attack_trackId=0, attack_postion=[0, 0, 0], num_missle=0):
        json_cmd = json.dumps(dict(nPlatId=nPlatId,  # todo
                                   nAttackTrackId=attack_trackId,
                                   nAttackPostion=attack_postion,
                                   NumMissle=num_missle, ))
        action = Action(modelType="PlanePlat", actionName='PlatFireCtl', actionDescription=json_cmd)
        return action

    # Update by Gaoxiang Wu

    @classmethod
    def make_action_SetPlatSixDoF(cls, platform_name: Union[str, int], yaw=0, pitch=0, roll=0, throttle=0):
        # 飞行器6自由度控制报文
        json_cmd = json.dumps(dict(nPlatId=platform_name,  # todo
                                   dYawRate=yaw,  # 0到1
                                   dPitchRate=pitch,  # 0到1
                                   dRollRate=roll,  # 0到1
                                   dThrottle=throttle, ))  # 0到2
        action = Action(modelType="PlanePlat", actionName='PlatSixDoFCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_SetPlatPatrol(cls, nPlatId, sRouteStyle, StyleParamsList, dSpeed):
        # 飞行器巡逻控制报文
        json_cmd = json.dumps(dict(nPlatId=nPlatId,
                                   sRouteStyle=sRouteStyle,
                                   StyleParamsList=StyleParamsList,
                                   dSpeed=dSpeed, ))
        action = Action(modelType="PlanePlat", actionName='PlatPatrolCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_SetPlatLeader(cls, nPlatId, nLeaderId):
        # 为单架副机指定长机
        json_cmd = json.dumps(dict(nPlatId=nPlatId,
                                   nLeaderId=nLeaderId, ))
        action = Action(modelType="PlanePlat", actionName='PlatFormationLeaderCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_SetPlatFormationMap(cls, PlatId2LeaderIdMap):
        # 为所有飞机指定长机
        json_cmd = json.dumps(dict(PlatId2LeaderIdMap=PlatId2LeaderIdMap, ))
        action = Action(modelType="PlanePlat", actionName='PlatFormationMapCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_SetPlatFormationStyle(cls, nPlatId, sFormationStyle, FormationStyleParamsList):
        # 飞机编队样式控制
        json_cmd = json.dumps(dict(nPlatId=nPlatId,
                                   sFormationStyle=sFormationStyle,
                                   FormationStyleParamsList=FormationStyleParamsList, ))
        action = Action(modelType="PlanePlat", actionName='PlatFormationStyleCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_SetPlatDodge(cls, nPlatId, bopen):
        # 飞机规避使能控制
        json_cmd = json.dumps(dict(nPlatId=nPlatId,
                                   bopen=bopen, ))
        action = Action(modelType="PlanePlat", actionName='PlatDodgeCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_SetPlatSelfDefense(cls, nPlatId, bopen):
        # 飞机自卫GR使能
        json_cmd = json.dumps(dict(nPlatId=nPlatId,
                                   bopen=bopen, ))
        action = Action(modelType="PlanePlat", actionName='PlatSelfDefenseCtl', actionDescription=json_cmd)
        return action


class ReconActions:
    @classmethod
    def make_action_recon_workon(cls, nRReconId, bWorkOn):
        # 雷达ZC装备 开关机报文
        json_cmd = json.dumps(dict(nRReconId=nRReconId,
                                   bWorkOn=bWorkOn, ))
        action = Action(modelType="RadarRecon", actionName='WorkOnCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_recon_SetTrg(cls, nRReconId, nTargetIndex):
        # 雷达ZC装备
        json_cmd = json.dumps(dict(nRReconId=nRReconId,
                                   nTargetIndex=nTargetIndex, ))
        action = Action(modelType="RadarRecon", actionName='WorkOnCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_recon_SetWorkAglRng(cls, nRReconId, dStartAz, dEndAz, dStartEl, dEndEl):
        # 雷达ZC装备 ZC范围控制报文
        json_cmd = json.dumps(dict(nRReconId=nRReconId,
                                   dStartAz=dStartAz,
                                   dEndAz=dEndAz,
                                   dStartEl=dStartEl,
                                   dEndEl=dEndEl, ))
        action = Action(modelType="RadarRecon", actionName='WorkAglRngCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_recon_SetRRecWorkFregRng(cls, nRReconId, dRFMin, dRFMax):
        # 雷达ZC装备 ZC频率控制报文
        json_cmd = json.dumps(dict(nRReconId=nRReconId,
                                   dRFMin=dRFMin,
                                   dRFMax=dRFMax, ))
        action = Action(modelType="RadarRecon", actionName='WorkFreqRngCtl', actionDescription=json_cmd)
        return action


class RjamActions:
    @classmethod
    def make_action_rjam_WorkOnAction(cls, nRJamId, bWorkOn, JamMode=0):
        # 雷达GR装备 开关机报文
        json_cmd = json.dumps(dict(nRJamId=nRJamId,
                                   bWorkOn=bWorkOn,
                                   JamMode=JamMode, ))
        action = Action(modelType="RadarJam", actionName='WorkOnCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_rjam_type_Action(cls, nRJamId, JamMode=0):
        # 雷达GR装备
        json_cmd = json.dumps(dict(nRJamId=nRJamId,
                                   JamMode=JamMode, ))
        action = Action(modelType="RadarJam", actionName='JamTypeCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_rjam_type_Action(cls, nRJamId, eJamMode=0):
        # 雷达GR装备 GR样式控制报文  GR样式枚举值，压制、欺骗    todo：仿真还没做
        json_cmd = json.dumps(dict(nRJamId=nRJamId,
                                   eJamMode=eJamMode))
        action = Action(modelType="RadarJam", actionName='JamTypeCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_rjam_SetWorkAglRng(cls, nRJamId, dStartAz, dEndAz, dStartEl, dEndEl):
        # 雷达GR装备 GR范围控制报文
        json_cmd = json.dumps(dict(nRJamId=nRJamId,
                                   dStartAz=dStartAz,
                                   dEndAz=dEndAz,
                                   dStartEl=dStartEl,
                                   dEndEl=dEndEl, ))
        action = Action(modelType="RadarJam", actionName='WorkAglRngCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_rjam_SetRJamWorkFregRng(cls, nRJamId, dTarFreMin, dTarFreMax):
        # 雷达GR装备 GR频率控制报文
        json_cmd = json.dumps(dict(nRJamId=nRJamId,
                                   dRFMin=dTarFreMin,
                                   dRFMax=dTarFreMax, ))
        action = Action(modelType="RadarJam", actionName='WorkFreqRngCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_rjam_SetRadarJamTrg(cls, nRJamId, nTargetIndex: List, JamMode=0, dCenterFreg=-1, dBandWidth=-1):
        # 雷达GR装备 GR目标控制报文
        # todo nRJamId改为List类型
        json_cmd = json.dumps(dict(nRJamId=nRJamId,
                                   nTargetIndex=nTargetIndex,
                                   JamMode=JamMode,
                                   dCenterFreg=dCenterFreg,
                                   dBandWidth=dBandWidth, ))
        action = Action(modelType="RadarJam", actionName='TrgCtl', actionDescription=json_cmd)
        return action


class RadarActions:
    @classmethod
    def make_action_radar_WorkOnAction(cls, nRadarId, bWorkOn):
        # 雷达开关机控制
        json_cmd = json.dumps(dict(nRadarId=nRadarId,
                                   bWorkOn=bWorkOn, ))
        action = Action(modelType="Radar", actionName='WorkOnCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_radar_SetWorkAglRng(cls, nRadarId, dStartAz, dEndAz, dStartEl, dEndEl):
        # 雷达参数控制
        json_cmd = json.dumps(dict(nRadarId=nRadarId,
                                   dStartAz=dStartAz,
                                   dEndAz=dEndAz,
                                   dStartEl=dStartEl,
                                   dEndEl=dEndEl, ))
        action = Action(modelType="Radar", actionName='WorkAglRngCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_radar_SetWorkFregSel(cls, nRadarId, dTarFreMin, dTarFreMax):
        # 雷达频率控制
        json_cmd = json.dumps(dict(nRadarId=nRadarId,
                                   dTarFreMin=dTarFreMin,
                                   dTarFreMax=dTarFreMax, ))
        action = Action(modelType="Radar", actionName='WorkFreqRngCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_radar_SetAntiJamMode(cls, nRadarId, AntiJamMode):
        # 雷达抗GR措施控制
        json_cmd = json.dumps(dict(nRadarId=nRadarId,
                                   AntiJamMode=AntiJamMode, ))
        action = Action(modelType="Radar", actionName='AntiJamModeCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_radar_SetTrackTrgID(cls, nRadarId, TrackIdList):
        # 设置雷达跟踪航迹目标id
        json_cmd = json.dumps(dict(nRadarId=nRadarId,
                                   TrackIdList=TrackIdList, ))
        action = Action(modelType="Radar", actionName='TrackTrgIDCtl', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_radar_GuidCmdAction(cls, nRadarId, bguid):
        # 雷达制导控制指令
        json_cmd = json.dumps(dict(nRadarId=nRadarId,
                                   bguid=bguid, ))
        action = Action(modelType="Radar", actionName='GuidCmdAction', actionDescription=json_cmd)
        return action

    @classmethod
    def make_action_radar_SetWorkMode(cls, nRadarId, RadarWorkMode):
        # 雷达工作模式
        json_cmd = json.dumps(dict(nRadarId=nRadarId,
                                   RadarWorkMode=RadarWorkMode, ))
        action = Action(modelType="Radar", actionName='WorkModeCtl', actionDescription=json_cmd)
        return action
