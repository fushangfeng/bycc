from abc import abstractmethod


class Reward:

    def __init__(self, **kwargs):
        """
        接收奖励配置参数
        """
        raise NotImplementedError

    @abstractmethod
    def process(self, info_manager, done, mission_manager=None):
        """
        每步更新奖励信息
        如果是即时奖励，则每步返回reward值；
        如果是最终奖励，则done=True时返回reward值，其余step返回0
        return：reward 或 (reward, env_done)
        如果返回元组，env_done=True表示请求环境重启
        """
        raise NotImplementedError

    @abstractmethod
    def reset(self):
        """
        重置奖励函数
        """
        raise NotImplementedError
