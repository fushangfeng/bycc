from abc import abstractmethod


class Statistic:

    def __init__(self, **kwargs):
        """
        接收统计配置参数
        """
        raise NotImplementedError

    @abstractmethod
    def update(self, info_manager):
        """
        每步更新统计信息
        """
        raise NotImplementedError

    def summary(self):
        """
        输出统计值（单个值）
        """
        raise NotImplementedError

    def reset(self):
        raise NotImplementedError
