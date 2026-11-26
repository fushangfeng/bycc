# -*- coding: utf-8 -*-
import json
import typing

import pandas as pd

from env_interface.bycc_map import STATE_SPACE_MAP
from env_interface import data_types


def get_class_custom_attr(cls):
    return [
        key
        for key, value in cls.__dict__.items()
        if not key.startswith("__")
           and not callable(value)
    ]


def get_feature_json(e, attr_type_dict):
    feature_list = get_class_custom_attr(STATE_SPACE_MAP[e])

    feature_list = [
        {
            "description": f,
            "entity_filter": True if f in open_switch_feature_list else False,
            "feature": f,
            "name": f,
            "reward_switch": True if f in open_switch_feature_list else False,
            "statistics_switch": True if f in open_switch_feature_list else False,
            "type": attr_type_dict.get(f).__name__
        }
        for f in feature_list
    ]

    return json.dumps(feature_list)


def generate_csv(entity_list, csv_path):
    entity_feature_list = []

    for e in entity_list:
        if not STATE_SPACE_MAP.get(e):
            continue

        entity_info_class = getattr(data_types, f"{e}Info")
        attr_type_dict = typing.get_type_hints(entity_info_class)
        description = entity_info_class.get_entity_cls().__doc__.replace("\n", "")

        entity_feature_list.append(
            {
                "name": e,
                "state_name": e,
                "parent": "",
                "features": get_feature_json(e, attr_type_dict),
                "type": "2D",
                "description": description
            }
        )

    df = pd.DataFrame(entity_feature_list)
    df.to_csv(csv_path, index=False)


if __name__ == '__main__':
    # 该脚本需要 data_types 中实体的三个类名满足默认格式
    # 如 ReconRadar 的三个类分别为 ReconRadar，ReconRadarInfo, ReconRadarStateSpace
    # 且 STATE_SPACE_MAP的 key 和 entity_list 中对应
    # ReconRadarStateSpace 中定义的属性在 ReconRadarInfo 中均标注类型

    # 页面实体组件过滤打开字段，不在该列表默认关闭
    open_switch_feature_list = ["fLon", "fLat", "fHeight",
                                "WorkState", "PlatType", "SurvivalState", "ePlatType"
                                "iTrgNum", "iJamedTrgNum"]

    # 需转换的entity，和 STATE_SPACE_MAP的 key对应
    entity_list = ["ReconRadar", "RadarJammer", "RadarPara", "RadarDetect"]

    generate_csv(entity_list, csv_path="state.csv")
