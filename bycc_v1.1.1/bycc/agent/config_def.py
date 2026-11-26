class FeatureType:
    COMMON = '1D'
    ENTITY = '2D'
    SPATIAL = 'spatial'
    INPUT = 'input'
    LABEL = 'label'


class ActionType:
    PREDICATE = 'predicate'
    SUBJECT = 'subject'
    OBJECT = 'object'
    PARAMETER = 'parameter'
    OUTPUT = 'io'


class ActionCategory:
    CATEGORICAL = 'categorical'
    SINGLE_SELECTIVE = 'single_selective'
    UNORDERED_MULTI_SELECTIVE = 'unordered_multi_selective'
    ORDERED_MULTI_SELECTIVE = 'ordered_multi_selective'
    GAUSSIAN = 'gaussian'
    MULTI_HEAD_GAUSSIAN = 'multi_head_gaussian'
    OUTPUT = 'output'


class OutputType:
    ACTION = 'action'
    LOGITS = 'logits'
    NETWORK = 'network'  # 添加对network类型的支持


class RewardOperation:
    SUM = 'sum'
    DIFF = 'diff'


class BehaviorTreeNodeType:
    SELECTOR = "select"
    SEQUENCE = "sequence"
    PARALLEL = "parallel"
    RECURRENT = "recurrent"
    RESTRICTED = "restricted"
    GATE = "gate"
    ACTION = "behavior"
    CONDITION = "condition"
    DECORATOR = "decorator"


class BehaviorTreeNodeResult:
    SUCCESS = "Success"
    FAILURE = "Failure"
    RUNNING = "Running"
    STOPPED = "Stopped"  # 终止执行的节点（后续step不再执行）


class GateNodeOperator:
    AND = "and"
    OR = "or"
    NOT = "not"


class IndicatorType:
    MISSION_IMPLEMENTATION = "mission_implementation"
    SELF_DAMAGE = "self_damage"
    ENEMY_DAMAGE = "enemy_damage"
    AMMO_CONSUME = "ammo_consume"
    COMPLETION_RATE = "completion_rate"
    COMPOSITE_VALUE = "composite_value"

    # UserDefinedIndicatorType:
    # SINGLE_VALUE = "single_value"
    # SINGLE_VALUE_PER_STEP = "single_value_per_step"  # 默认int/float
    # SINGLE_BOOOL = "single_bool"  # True/False
    # STR = "str"
    # COMPOSITE_VALUE = "composite_value"  # 默认int/float  {"1":2, "3":4}
    # CURVES = "curves"  # {"curve1": [(x1,y1),(x2,y2),...],"curve2":[(1,2),(3,4),...]}
    # PERIODS = "periods"  # {"task1": [(1,2),(2,3),....]],...}
