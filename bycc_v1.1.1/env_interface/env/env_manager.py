import os
import random
import time

add_registry_host_cmd = "echo 10.0.0.200 registry.inspir.ai >> /etc/hosts"
os.system(add_registry_host_cmd)
add_gitlab_host_cmd = "echo 10.0.0.200 gitlab.inspir.ai >> /etc/hosts"
os.system(add_gitlab_host_cmd)


class EnvManager(object):
    
    def __init__(
        self,
        env_id,
        base_port=30089,
        # volume_maps=[["/plat_data/EWX_v3.8.1/grpc_scenario/", "/home/ewx/demos/grpc_scenario"]],
        volume_maps=[["/job/project/grpc_scenario/", "/home/ewx/demos/grpc_scenario"]],
        image_name='registry.inspir.ai:5000/ewx_dev_amd64:v3.1.8.8',
        start_cmds="/home/ewx/ewx_env_init.sh",
        scenarios_weights_dict={}
    ):
        """
        params:
            env_id: 训练云分配给当前仿真实例的id
            base_port: 映射出来的供智能体访问的基础端口号
            env_inner_ports: 仿真中需要映射出来的端口号列表
            image_name：仿真镜像registry地址
            start_cmds: 随仿真容器运行启动的脚本
        """
        self._env_id = env_id
        self._base_port = base_port
        self._volume_maps = volume_maps
        self._image_name = image_name
        self._start_cmds = start_cmds
        self._docker_name = f"env_{self._env_id}"
        self.port = int(self._env_id) + int(self._base_port)

        self._scenarios = list(scenarios_weights_dict.keys())
        self._scenario_weights = list(scenarios_weights_dict.values())

        self.reset()

    def start_docker(self):
        scenario = random.choices(self._scenarios, weights=self._scenario_weights, k=1)[0]
        volumes_str = f"-v {scenario}:/data/scenario "
        for volume_map in self._volume_maps:
            volumes_str += f"-v {volume_map[0]}:{volume_map[1]} "

        start_cmds = f'-c "{self._start_cmds}"' if self._start_cmds else ""
        
        docker_run_cmd = (f'docker run -itd --name {self._docker_name} {volumes_str} '
                          f'-p {self.port}:{self._base_port} {self._image_name} '
                          f'bash -c "source /data/EWX/init_dev_run_env; cd /data/EWX/bin; '
                          f'/data/EWX/bin/EWX.Mission -rt /data/scenario/Start_Up.txt;"')
            
        print(f"仿真启动指令： {docker_run_cmd}")
        
        os.system(docker_run_cmd)
        
        time.sleep(20)
        
    def stop_docker(self):
        docker_stop_cmd = f"docker stop {self._docker_name}"
        os.system(docker_stop_cmd)
        time.sleep(1)
        
        docker_rm_cmd = f"docker rm {self._docker_name}"
        os.system(docker_rm_cmd)
        time.sleep(1)

    def reset(self):
        self.stop_docker()
        self.start_docker()

    def get_server_port(self):
        return self.port

