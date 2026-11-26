# -*- coding: utf-8 -*-
"""
@Project: bycc
@File: feature.py
@Time: 2024/2/1 10:52
@Auth: ZhengShixin
@IDE: PyCharm
"""
from bycc.ai.network_constructor.utils.common import get_inputs_shape


class Feature:
    def __init__(self, name, config, backend):
        self.name = name
        self.config = config
        self.backend = backend
        self.max_num = self.config.max_num
        self.type = self.config.type
        # self.feature_classes: dict = self.feature_classes_parse()
        self.class_property: dict = self.class_property_parse()
        self.filters: dict = self.filters_parse()
        self._source = None
        self._layer = None

    # def feature_classes_parse(self):
    #     return self.config.get('class', [])

    def class_property_parse(self):
        return self.config.features

    def filters_parse(self):
        return self.config.filters

    @property
    def flatten_shape(self):
        if not hasattr(self, '_flatten_shape'):
            if (self.config.features is not None) and (self.config.features != []):
                # 处理字符串列表形式的features配置
                try:
                    # 尝试按原逻辑处理（如果class_property是特征对象列表）
                    self._flatten_shape = get_inputs_shape([feature_obj for feature, feature_obj in self.class_property])
                except (TypeError, ValueError) as e:
                    # 移除默认值假设，要求明确配置
                    raise ValueError(
                        f"Feature {self.name} (type: {self.type}) 无法从特征对象计算flatten_shape。"
                        f"原始错误: {e}。"
                        f"请检查配置：features={self.config.features}，"
                        f"或在配置中明确指定length字段。"
                        f"不同环境的特征维度差异很大，不应使用默认值假设。"
                    )
            elif self.config.length is not None:
                # 分层智能体input feature
                self._flatten_shape = self.config.length
            else:
                raise ValueError
        return self._flatten_shape

    @property
    def input_shape(self):
        if self.type == "2D":
            return self.max_num, self.flatten_shape,
        elif self.type == "spatial":
            # 最小化安全检查
            if not self.class_property or len(self.class_property) == 0:
                raise ValueError(f"Feature {self.name}: spatial类型需要class_property配置")
            
            spatial_info = self.class_property[0][1]
            return spatial_info.width, spatial_info.height, self.flatten_shape
        else:
            return self.flatten_shape,

    @property
    def input(self):
        if self.backend=='tensorflow':
            if not hasattr(self, '_input'):
                import keras
                self._input = keras.Input(shape=self.input_shape, name=self.name)
        elif self.backend=='paddle':
            if not hasattr(self, '_input'):
                import paddle
                # 需要加一个 batch_size 维
                self._input = paddle.zeros(shape=tuple([1]+list(self.input_shape)), name=self.name)
        return self._input
