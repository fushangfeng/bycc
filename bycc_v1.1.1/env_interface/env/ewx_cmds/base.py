import inspect
import json

from env_interface.protos.output.ai_pb2 import Action


class BaseAction:
    model_type: str = ''

    @classmethod
    def _make_action(cls, outer_vars):
        # 装饰智能体动作报文
        if not cls.model_type:
            raise NotImplementedError(f"class {cls.__name__} attribute model_type is not assigned")

        f_back = inspect.currentframe().f_back
        action_name = f_back.f_code.co_name # 使用调用帧的函数名作为actionName,函数名应与接口定义一致
        outer_vars.pop('cls', None) # 移除cls参数, 使用调用帧的实参/局部变量,应与接口定义一致
        action_description_json = json.dumps(outer_vars)
        action = Action(modelType=cls.model_type, actionName=action_name, actionDescription=action_description_json)
        return action