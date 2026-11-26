# -*- coding: utf-8 -*-
import logging
import time

import grpc

from env_interface.env.ewx_cmds import RjamActions
from env_interface.env.raw_obs import RawObs
from env_interface.protos.output.SimuMetadata_pb2 import Enum_SimStateCtrl, Enum_SimState
from env_interface.protos.output.ai_pb2 import (Actions, SimRate, SimCtrlCMD, REQUEST_STATES, SimtimePiece, REPLY_STATES)
from env_interface.protos.output.ai_pb2_grpc import AI_ServiceStub
from typing import Union, Dict, List

class EnvClient():
    def __init__(self, ip='127.0.0.1', port=None):
        self.ip = ip
        self.port = port
        if self.ip and self.port:
            # 创建至服务器的gRPC通道
            channel = grpc.insecure_channel(f'{self.ip}:{self.port}')

            # 创建服务器客户端存根
            self.ai_service = AI_ServiceStub(channel)

    def get_sim_states(self):
        """
        获取仿真的态势信息
        """
        response_obs = self.get_raw_obs()
        obs_dict = RawObs(response_obs).to_dict()
        return obs_dict

    def get_raw_obs(self) -> REPLY_STATES:
        """
        获取仿真的原始态势信息
        """
        try:
            request = REQUEST_STATES(site='1')
            response_obs = self.ai_service.GetSimStates(request, timeout=1)
            return response_obs

        except Exception as e:
            logging.error("get sim state error")
            raise e

    def get_proto_obs(self) -> REPLY_STATES:
        """
        获取转换字符串后的仿真的原始态势信息
        """
        response_obs = self.get_raw_obs()
        return RawObs(response_obs).proto

    def set_sim_speed(self, speed):
        cmd = SimRate(rate=speed)
        self.ai_service.SetSimRate(cmd)

    def sim_control_start(self):
        cmd = SimCtrlCMD(CMD=Enum_SimStateCtrl.Enum_Start_1)
        # self.ai_service.SimControl(cmd)
        print(self.ai_service.SimControl(cmd))

    def sim_control_pause(self):
        cmd = SimCtrlCMD(CMD=Enum_SimStateCtrl.Enum_Pause_2)
        self.ai_service.SimControl(cmd)

    def sim_control_resume(self):
        cmd = SimCtrlCMD(CMD=Enum_SimStateCtrl.Enum_Resume_3)
        self.ai_service.SimControl(cmd)

    def sim_control_reset(self):
        cmd = SimCtrlCMD(CMD=Enum_SimStateCtrl.Enum_Reset_4)
        self.ai_service.SimControl(cmd)

    def sim_control_stop(self):
        cmd = SimCtrlCMD(CMD=Enum_SimStateCtrl.Enum_Stop_5)
        self.ai_service.SimControl(cmd)

    # def send_SixDoF_cmds(self, platform_name: Union[str, int], yaw=0, pitch=0, roll=0, throttle=0):
    #     # 发出测试控制动作报文（飞行器6自由度控制）
    #     from SimuModelDataOut_pb2 import sP6DOF_CONTROL
    #     six_dof_cmd = sP6DOF_CONTROL(aPlatIndex=platform_name,  # todo
    #                                  dYawRate=yaw,  # 0到1
    #                                  dPitchRate=pitch,  # 0到1
    #                                  dRollRate=roll,  # 0到1
    #                                  dThrottle=throttle, )  # 0到2
    #     response = self.ai_service.SetSixDoF(six_dof_cmd)
    #     print(f"收到的回复为{response.STATUS}")
    #     return response

    def step_piece_time(self, timeInterval):
        # 仿真在每次StepPieceTime后自动暂停，且暂停状态下StepPieceTime无效
        self.sim_control_resume()
        request = SimtimePiece(timeInterval=timeInterval)
        self.ai_service.StepPieceTime(request)
        # 不停获取态势，直到仿真暂定(推演完成)
        obs = self.get_raw_obs()
        while obs.metaData.SIM_STATE != Enum_SimState.Enum_PAUSEING:
            obs = self.get_raw_obs()
            time.sleep(0.5)
        return obs

    # def Advance_to_SimTimestamp(self, simTimestamp):
    #     # todo 可以用 StepPieceOfTime 实现
    #     pass

    def take_actions(self, actions: Dict[str, List]):
        try:
            # 发送智能体动作报文
            cmds = []
            for player, act_list in actions.items():
                cmds.extend(act_list)
            response = self.ai_service.TakeAction(Actions(actions=cmds))
            return response
        except Exception as e:
            # self.sim_control_pause()
            # print(e)
            logging.error("take action error")
            raise e
            # print_exc()
            # while True:
            #     time.sleep(1)


if __name__ == '__main__':
    env = EnvClient(ip='10.0.0.120',
                    port='50000')

    # env.sim_control_reset()
    # reset 之后不能直接发命令，需要sleep一小段时间
    # time.sleep(5)
    # speed = 5
    # env.set_sim_speed(speed)
    # print(f"set_sim_speed（{speed}）")
    #
    # env.sim_control_start()
    # obs = env.get_sim_states()
    # t0, sim_t0 = time.time(), obs['meta_data'].SIM_TIME
    # time.sleep(5)
    # obs = env.get_sim_states()
    # t1, sim_t1 = time.time(), obs['meta_data'].SIM_TIME
    # print(
    #     f"当前倍速为{obs['meta_data'].SIM_RATE}，现发送sim_control_start指令，并sleep5，现实世界过去{t1 - t0}秒，仿真内经过{sim_t1 - sim_t0}秒，"
    #     f"当前仿真状态为{obs['meta_data'].SIM_STATE}，当前仿真时刻为{obs['meta_data'].SIM_TIME}")

    # obs = env.get_sim_states()
    # t0,sim_t0 = time.time(),obs['meta_data'].SIM_TIME
    # env.StepPieceOfTime(10)
    # # obs = env.get_sim_states()
    # t1,sim_t1 = time.time(),obs['meta_data'].SIM_TIME
    # print(f"当前倍速为{obs['meta_data'].SIM_RATE}，现发送StepPieceOfTime(10)指令，现实世界过去{t1-t0}秒，仿真内经过{sim_t1-sim_t0}秒，"
    #       f"当前仿真时刻为{obs['meta_data'].SIM_TIME}，当前仿真时刻为{obs['meta_data'].SIM_TIME}")
    #
    # env.sim_control_resume()
    # obs = env.get_sim_states()
    # t0,sim_t0 = time.time(),obs['meta_data'].SIM_TIME
    # time.sleep(5)
    # obs = env.get_sim_states()
    # t1,sim_t1 = time.time(),obs['meta_data'].SIM_TIME
    # print(f"当前倍速为{obs['meta_data'].SIM_RATE}，现发送sim_control_resume指令，并sleep5，现实世界过去{t1-t0}秒，仿真内经过{sim_t1-sim_t0}秒，"
    #       f"当前仿真状态为{obs['meta_data'].SIM_STATE}，当前仿真时刻为{obs['meta_data'].SIM_TIME}")
    #
    # env.sim_control_pause()
    # obs = env.get_sim_states()
    # t0,sim_t0 = time.time(),obs['meta_data'].SIM_TIME
    # time.sleep(5)
    # obs = env.get_sim_states()
    # t1,sim_t1 = time.time(),obs['meta_data'].SIM_TIME
    # print(f"当前倍速为{obs['meta_data'].SIM_RATE}，现发送sim_control_pause指令，并sleep5，现实世界过去{t1-t0}秒，仿真内经过{sim_t1-sim_t0}秒，"
    #       f"当前仿真状态为{obs['meta_data'].SIM_STATE}，当前仿真时刻为{obs['meta_data'].SIM_TIME}")
    #
    # env.sim_control_reset()
    # obs = env.get_sim_states()
    # t0,sim_t0 = time.time(),obs['meta_data'].SIM_TIME
    # time.sleep(5)
    # obs = env.get_sim_states()
    # t1,sim_t1 = time.time(),obs['meta_data'].SIM_TIME
    # print(f"当前倍速为{obs['meta_data'].SIM_RATE}，现发送sim_control_reset指令，并sleep5，现实世界过去{t1-t0}秒，仿真内经过{sim_t1-sim_t0}秒，"
    #       f"当前仿真状态为{obs['meta_data'].SIM_STATE}，当前仿真时刻为{obs['meta_data'].SIM_TIME}")

    # env.sim_control_stop()
    # obs = env.get_sim_states()
    # t0,sim_t0 = time.time(),obs['meta_data'].SIM_TIME
    # time.sleep(5)
    # obs = env.get_sim_states()
    # t1,sim_t1 = time.time(),obs['meta_data'].SIM_TIME
    # print(f"当前倍速为{obs['meta_data'].SIM_RATE}，现发送sim_control_stop指令，并sleep5，现实世界过去{t1-t0}秒，仿真内经过{sim_t1-sim_t0}秒，"
    #       f"当前仿真状态为{obs['meta_data'].SIM_STATE}，当前仿真时刻为{obs['meta_data'].SIM_TIME}")

    obs = env.get_sim_states()
    # print("当前获得的态势信息有", obs)
    # print("当前裁决信息",obs['raw_obs'].judgementdata)
    # 飞行平台控制指令
    # cmd = PlatActions.make_action_SetPlatSixDoF(platform_name=1,yaw=1,pitch=1,roll=1,throttle=1)
    # cmd = PlatActions.make_action_SetPlatPatrol(nPlatId=,sRouteStyle=,StyleParamsList=,dSpeed=)
    # cmd = PlatActions.make_action_SetPlatLeader(nPlatId=,nLeaderId=)
    # cmd = PlatActions.make_action_SetPlatFormationMap(PlatId2LeaderIdMap=)
    # cmd = PlatActions.make_action_SetPlatFormationStyle(nPlatId=,sFormationStyle=,FormationStyleParamsList=)
    # cmd = PlatActions.make_action_SetPlatDodge(nPlatId=,bopen=)
    # cmd = PlatActions.make_action_SetPlatAutoFire(nPlatId=,bopen=)
    # cmd = PlatActions.make_action_SetPlatSelfDefense(nPlatId=,bopen=)

    # 雷达ZC装备指令
    # cmd1 = ReconActions.make_action_recon_workon(nRReconId=55, bWorkOn=False)                                                    # ZC开关机控制
    # # todo 俯仰设置存疑，先不管
    # cmd2 = ReconActions.make_action_recon_SetWorkAglRng(nRReconId=55,dStartAz=10,dEndAz=30,dStartEl=30,dEndEl=40)            # ZC范围控制
    # cmd3 = ReconActions.make_action_recon_SetRRecWorkFregRng(nRReconId=55,dRFMin=2000,dRFMax=5000)                           # ZC频率控制

    # 雷达GR装备
    # cmd = RjamActions.make_action_rjam_WorkOnAction(nRJamId=57, bWorkOn=True, JamMode=0)  # GR开关机控制
    # cmd2 = RjamActions.make_action_rjam_SetWorkAglRng(nRJamId=57, dStartAz=10, dEndAz=20, dStartEl=30,
    #                                                   dEndEl=40)  # GR范围控制
    # # cmd3 = RjamActions.make_action_rjam_SetRJamWorkFregRng(nRJamId=,dTarFreMin=,dTarFreMax=)                    # GR频率控制
    if True:
        cmd3 = RjamActions.make_action_rjam_SetRadarJamTrg(nRJamId=57, nTargetIndex=[1,5,2,7,8], JamMode=0, dCenterFreg=50,
                                                       dBandWidth=100)  # GR目标控制

    # acts = Actions(actions=[cmd1, cmd2, cmd3])
    # response = env.take_actions(acts)

    # 雷达设备
    # cmd = RadarActions.make_action_radar_WorkOnAction(nRadarId=,bWorkOn=)                                        # 雷达开关机控制
    # cmd = RadarActions.make_action_radar_SetWorkAglRng(nRadarId=,dStartAz=,dEndAz=,dStartEl=,dEndEl=)            # 雷达参数控制
    # cmd = RadarActions.make_action_radar_SetWorkFregSel(nRadarId=,dTarFreMin=,dTarFreMax=)                       # 雷达频率控制
    # cmd = RadarActions.make_action_radar_SetAntiJamMode(nRadarId=,AntiJamMode=)                                  # 雷达抗GR措施控制
    # cmd = RadarActions.make_action_radar_SetTrackTrgID(nRadarId=,TrackIdList=)                                   # 设置雷达跟踪航迹目标id
    # cmd = RadarActions.make_action_radar_GuidCmdAction(nRadarId=,bguid=)                                         # 雷达制导控制指令
    # cmd = RadarActions.make_action_radar_SetWorkMode(nRadarId=,RadarWorkMode=)                                   # 雷达工作模式

    #测试1V1空战代码(Gaoxiang Wu)
    # cmd1 = PlatActions.make_action_SetPlatAutoFire(nPlatId=,open=)                                                 #飞机打弹使能控制 todo 1211不用测
    # cmd2 = PlatActions.make_action_SetPlatAutoDodge(nPlatId=,open=)                                                #飞机规避使能控制 todo 1211不用测
    # cmd3 = PlatActions.make_action_SetPlatFireCtl(nPlatId=, attack_trackId=, attack_postion=, num_missle=)         #飞机打弹控制
    # cmd4 = PlatActions.make_action_SetPlatDir(nPlatId, speed=, direction=)                                         #飞机机动方向控制
    # cmd5 = PlatActions.make_action_SetPlatPos(nPlatId=,speed=,postion=)                                            #飞机机动位置控制

    # 测试地面平台控制代码(Gaoxiang Wu)
    # cmd6 = PlatActions.make_action_PlatDirCtl(nPlatId=, direction=)
    # cmd7 = PlatActions.make_action_PlatPosCtl(nPlatId=, postion=)

      # cmd8 = PlatActions.make_action_GrdPlatFormCtl(nLeaderPlatId=,nWingPlatList=)
      # cmd9 = PlatActions.make_action_GrdFormDeploymentCtl(nLeaderPlatId=, nFormationShape=)
      # cmd10 = PlatActions.make_action_GrdFormDirCtl(nLeaderPlatId=, nFlyPath= )
      #
      # cmd11 = PlatActions.make_action_PlatFormCtl(nLeaderPlatId=,nWingPlatList=)
      # cmd12 = PlatActions.make_action_FormStyleCtl(nLeaderPlatId=,nFormationShape= )
      # cmd13 = PlatActions.make_action_FormDeploymentCtl(nLeaderPlatId=,nDirection=)
    # 动作平台代码
    # acts = Actions(actions=[cmd6])  #cmdx为待测试指令 如cmd1、cmd2
    # response = env.take_actions(acts)

    # print("当前得到的雷达ZC，开关机，对应的返回响应是：", response)
