
class DefaultValue:
    # 默认值
    default_int = -1
    default_float = -1.0
    default_str = ""
    default_bool = True
    default_list = []
    default_dict = {}
    position = [-1, -1, -1]
    direction = [-1, -1, -1]
    id = -1
    type = -1
    level = -1
    max_capacity = -1
    range = 100e3
    missile_nums = 5


# 需要的平台单位名称
NEED_DATA_NAME = ["radar_paras", "jam_paras", "jam_get_paras","recon_get_paras", "plat_paras"]

# 平台ZC、TC、GR得到的信息名称
NEED_INFO_NAME = ["radar_detect_infos", "recon_radar_paras", "jam_get_paras"]

total_atts = [1,2] # todo 需要从想定读取