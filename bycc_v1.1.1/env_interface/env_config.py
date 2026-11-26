import os

env_config = {
    # 'server_ip': '127.0.0.1',
    'server_ip': '10.0.0.23',   # 本地推演时的仿真ip地址（非训练仿真ip）
    'server_port': 50000,  # 本地推演时的仿真端口地址
    'sim_speed': 1,   # 仿真加速倍数
    'max_game_time': 3000,
    'action_interval': 20,   # 智能体决策间隔（仿真时间，单位秒）

    'use_docker': False,
    # 'use_docker': True,
    'docker_server_port': 30089,
    'image_name': 'registry.inspir.ai:5000/ewx_dev_amd64:v3.1.9.5',
    'volume_maps': [["/project/scenario/", "/home/ewx/demos/grpc_scenario"]]
}

