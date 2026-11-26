# BYCC: BaiYang Command & Control



## 简介

本项目旨在提供一套接口和基础组件，用于快速构建强化学习智能体和规则智能体。

主要功能：
* 用户可通过配置文件自动构建强化学习智能体和规则智能体
* 用户可通过调用项目提供的基础接口和组件编写智能体代码
* 用户可通过定义标准态势和指令并实现态势和指令转换代码，使智能体在不同仿真平台的相似场景中具有一定程度的迁移能力
* 为强化学习智能体提供快速部署的能力

## 主要目录结构
```
├── bycc
│   ├── ai  # 智能体构建相关接口和组件
│   ├── data_types  # 数据类型定义
│   ├── environment  # 仿真环境接口
│   └── info  # info manager相关组件
├── bycc_tests  # 测试代码
├── examples  # 示例代码
└── flow_adapter  # 存放强化学习训练框架相关接口和组件，同时临时存放因适配训练框架而修改的bycc相关接口代码。会随着训练框架版本迭代更新
    └── v2  # 用于区分不同训练框架版本
```

## 业务组件
为方便用户对接业务及代码复用，提供业务开发接口和业务组件库，代码路径为：bycc/modules  
详细说明参见：[业务组件接口说明](docs/modules.md)

### common子模块处理
在实际开发过程中，可能存在不同类型的组件工程引用同一个common目录的情况，可使用git的子模块功能，让common工程被不同业务组件共享
```commandline
git submodule add -b <分支名> <公共库URL> <子模块路径>
# 如：git submodule add -b main https://github.com/user/common.git common
# 此操作会在.gitmodules 文件中记录子模块及其分支信息

# 本地调试时，想手动拉取带common子模块的业务组件工程，可通过以下命令拉取：
git clone --recursive <主仓库URL>  # 自动初始化子模块（若已配置分支）
cd 主仓库目录
git submodule update --init --remote  # 强制拉取分支最新提交

# --remote：让子模块跟踪远程分支的最新提交，而非主仓库记录的固定提交。
# 子模块将自动切换到配置的分支，并拉取最新代码。

# 后续再手动更新子模块时，使用以下命令：
git submodule update --remote
# 此命令会将所有子模块更新到其配置分支的最新提交。
```