# coding:gbk
from flow_adapter.v2.local.local import BPLocalRunner
from bycc_config.train_config import flow_config
import os

builder = flow_config['builder']
algo = flow_config['algorithm']

# model_info = {
#     '星际智能体-无负奖励_model': {
#         'model_file': os.path.abspath(os.path.join(os.path.dirname(__file__), 'models\\星际智能体-无负奖励_model_12000.npz')),
#         'mode': 'npz'
#     }
# }


# model_info = {
#     '8Mexhe1yat_model': {
#         'model_file': os.path.abspath(os.path.join(os.path.dirname(__file__), 'models\\1226\\1226noAutoReg_4600.npz')),
#         'mode': 'npz'
#     }
# }

model_info = None

runner = BPLocalRunner(builder, model_info, algo)

for i in range(1000):
    runner.debug()
    # runner.evaluate(max_step_num=10000, is_batch_inference=False)
