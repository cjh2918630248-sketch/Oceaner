# Oceaner 项目架构与设计文档

> 一款克苏鲁风格的 2D 回合制 RPG 游戏

---

## 目录

- [1. 项目概述](#1-项目概述)
- [2. 技术栈](#2-技术栈)
- [3. 整体架构](#3-整体架构)
- [4. 目录结构](#4-目录结构)
- [5. 核心系统设计](#5-核心系统设计)
  - [5.1 游戏主循环与场景管理](#51-游戏主循环与场景管理)
  - [5.2 角色系统](#52-角色系统)
  - [5.3 武器系统](#53-武器系统)
  - [5.4 战斗系统](#54-战斗系统)
  - [5.5 队伍系统](#55-队伍系统)
  - [5.6 背包与道具系统](#56-背包与道具系统)
  - [5.7 金钱与商店系统](#57-金钱与商店系统)
  - [5.8 地图系统](#58-地图系统)
  - [5.9 UI 系统](#59-ui-系统)
  - [5.10 结局系统](#510-结局系统)
  - [5.11 数据与存档系统](#511-数据与存档系统)
- [6. 数据结构设计](#6-数据结构设计)
- [7. 后续扩展方向](#7-后续扩展方向)

---

## 1. 项目概述

**Oceaner** 是一款以克苏鲁神话为背景的**纯单机** 2D 回合制 RPG 游戏。玩家扮演调查员深入被"海蚀"侵染的世界，探索地图、与 NPC 互动、招募同伴组建小队（最多 4 人），与普通敌人、精英怪和 BOSS 展开回合制战斗，并在相斥的剧情分支中走向 A/B/C/D 四种结局之一。

### 核心玩法

| 玩法 | 说明 |
|------|------|
| 地图探索 | 基于 Tiled 制作的 2D 瓦片地图，自由移动探索 |
| NPC 互动 | 对话、获取情报、招募队友 |
| 回合制战斗 | 小队 vs 敌人，使用技能与道具进行策略战斗 |
| 武器构筑 | 角色伤害完全由武器决定：大剑、船锚、电锯、长槊、渔叉与特殊的"法杖" |
| 队伍养成 | 最多 4 人小队，管理成员属性与武器；战斗获取经验值，升级提升基本属性 |
| 金钱与商店 | 战斗与任务获取金钱，在商人处购买装备、道具、武器 |
| 多结局 | A（普通）/ B（伪）/ C（隐藏）/ D（真）四结局，A、B 两线相斥 |
| 克苏鲁要素 | "海蚀"作为独特的伤害体系贯穿全程——无法被抵抗的真实伤害，只能被增幅 |

---

## 2. 技术栈

| 技术 | 用途 |
|------|------|
| **C++ (C++17+)** | 核心开发语言 |
| **Raylib** | 渲染、输入、音频、窗口管理 |
| **raylib-tiled** | 解析并渲染 Tiled 地图（.tmx / .tsx） |
| **Tiled 地图编辑器** | 关卡与地图制作工具（导出 .tmx） |
| **nlohmann/json** | 配置文件、游戏数据、存档的序列化/反序列化 |
| **CMake** | 构建系统（推荐） |

---

## 3. 整体架构

采用**分层架构 + 状态机驱动**的设计，各层职责单一、低耦合：

```
┌─────────────────────────────────────────────────────┐
│                    应用层 (Game)                     │
│          主循环 / 窗口管理 / 全局资源初始化            │
├─────────────────────────────────────────────────────┤
│                 场景层 (Scene Manager)               │
│   标题场景 │ 探索场景 │ 战斗场景 │ 背包场景 │ 对话场景  │
├─────────────────────────────────────────────────────┤
│                  逻辑层 (Game Systems)               │
│  角色系统 │ 战斗系统 │ 队伍系统 │ 道具系统 │ 对话系统   │
├─────────────────────────────────────────────────────┤
│                 基础设施层 (Infrastructure)           │
│ 渲染封装 │ 资源管理 │ 输入管理 │ 音频 │ JSON 序列化   │
├─────────────────────────────────────────────────────┤
│                    数据层 (Data)                     │
│   角色配置 │ 技能表 │ 道具表 │ 地图文件 │ 存档文件      │
└─────────────────────────────────────────────────────┘
```

### 设计原则

1. **数据驱动**：角色、技能、道具、敌人等全部由 JSON 配置定义，代码只负责逻辑，方便调整数值与扩展内容。
2. **场景状态机**：游戏流程由场景管理器统一调度（探索 ⇄ 战斗 ⇄ 背包 ⇄ 对话），场景之间通过事件/参数传递数据。
3. **组合优于继承**：角色差异尽量用数据和组件描述，继承层次保持浅（`Character` 一层派生即可）。
4. **渲染与逻辑分离**：逻辑按固定回合/帧推进，渲染只读取状态，便于后续做战斗动画与表现层优化。

---

## 4. 目录结构

```
Oceaner/
├── CMakeLists.txt
├── ARCHITECTURE.md            # 本文档
├── assets/                    # 游戏资源
│   ├── maps/                  # Tiled 地图 (.tmx / .tsx)
│   ├── textures/              # 角色、敌人、UI 贴图
│   ├── audio/                 # 音乐与音效
│   └── fonts/                 # 字体（含中文字体）
├── data/                      # 数据配置 (JSON)
│   ├── characters.json        # 主角与可招募 NPC 属性
│   ├── npcs.json              # NPC 定义（类型、对话、位置）
│   ├── enemies.json           # 敌人定义（普通/精英/BOSS）
│   ├── weapons.json           # 武器表（面板、补正、可用技能）
│   ├── skills.json            # 技能表
│   ├── items.json             # 道具表
│   ├── dialogues.json         # 对话脚本
│   ├── shops.json             # 商店表（商人货架与价格）
│   └── endings.json           # 结局定义与触发条件
├── saves/                     # 玩家存档
├── src/
│   ├── main.cpp
│   ├── core/                  # 应用层与基础设施
│   │   ├── Game.h/.cpp        # 主循环
│   │   ├── SceneManager.h/.cpp
│   │   ├── ResourceManager.h/.cpp
│   │   ├── InputManager.h/.cpp
│   │   ├── AudioManager.h/.cpp
│   │   └── EventBus.h/.cpp    # 模块间事件通信
│   ├── scenes/                # 场景层
│   │   ├── Scene.h            # 场景基类
│   │   ├── TitleScene.h/.cpp
│   │   ├── ExploreScene.h/.cpp
│   │   ├── BattleScene.h/.cpp
│   │   ├── InventoryScene.h/.cpp
│   │   └── DialogueScene.h/.cpp
│   ├── entities/              # 角色实体
│   │   ├── Character.h/.cpp   # 角色基类（含战斗属性）
│   │   ├── Player.h/.cpp      # 主角
│   │   ├── Npc.h/.cpp         # NPC（互动型 / 可招募型）
│   │   ├── Enemy.h/.cpp       # 敌人（普通/精英/BOSS）
│   │   └── Weapon.h/.cpp      # 武器（面板与补正数据）
│   ├── systems/               # 逻辑系统
│   │   ├── BattleSystem.h/.cpp
│   │   ├── DamageCalculator.h/.cpp  # 伤害结算（武器+补正+buff）
│   │   ├── PartySystem.h/.cpp
│   │   ├── InventorySystem.h/.cpp
│   │   ├── SkillSystem.h/.cpp
│   │   ├── DialogueSystem.h/.cpp
│   │   ├── ShopSystem.h/.cpp        # 商店买卖逻辑
│   │   └── EndingSystem.h/.cpp      # 结局路线锁定与结局判定
│   ├── map/                   # 地图系统
│   │   ├── TiledMap.h/.cpp    # raylib-tiled 封装
│   │   └── Collision.h/.cpp   # 碰撞与触发区域
│   ├── ui/                    # UI 组件
│   │   ├── HUD.h/.cpp
│   │   ├── BattleUI.h/.cpp
│   │   ├── InventoryUI.h/.cpp
│   │   ├── ShopUI.h/.cpp
│   │   └── DialogueBox.h/.cpp
│   └── data/                  # 数据加载与存档
│       ├── DataLoader.h/.cpp  # JSON 配置加载
│       └── SaveManager.h/.cpp # 存档读写
└── third_party/               # 第三方库（raylib、nlohmann、paho 等）
```

---

## 5. 核心系统设计

### 5.1 游戏主循环与场景管理

游戏由 `Game` 类驱动主循环，`SceneManager` 以**栈式状态机**管理场景切换：

```
TitleScene ──开始游戏──▶ ExploreScene ──遭遇敌人──▶ BattleScene
                            │  ▲                      │
                    打开背包 │  │ 关闭       战斗结束返回 │
                            ▼  │                      ▼
                      InventoryScene ◀───────────(战斗中也可开背包)
                            
ExploreScene ──靠近NPC按互动键──▶ DialogueScene（对话结束弹出返回）
```

- **栈式管理**：背包、对话等场景以"压栈"方式打开，关闭后弹出并恢复下层场景，探索状态不丢失。
- 每帧流程：`处理输入 → 更新当前场景逻辑 → 渲染当前场景（必要时半透明渲染下层场景）`。

### 5.2 角色系统

#### 类层次

```
Character (基类：战斗属性 + 位置 + 动画)
├── Player   主角（玩家操作对象，探索场景中接受输入）
├── Npc      NPC
│    ├── 互动型 NPC（InteractOnly）：只能对话、给情报/任务
│    ├── 可招募 NPC（Recruitable）：满足条件后可加入队伍
│    └── 商人 NPC（Merchant）：互动后打开商店界面，出售装备/道具/武器（见 5.7）
└── Enemy    敌人
     ├── Normal  普通敌人
     ├── Elite   精英怪（属性强化，可能带特殊技能）
     └── Boss    BOSS（多阶段、专属技能与机制）
```

NPC 类型与敌人等级用**枚举 + JSON 配置**区分，而非继续派生子类，保证扩展新 NPC/敌人只需要改配置：

```cpp
enum class NpcType  { InteractOnly, Recruitable, Merchant };
enum class EnemyRank { Normal, Elite, Boss };
```

#### 战斗属性（所有可战斗角色共有）

| 属性 | 字段 | 说明 |
|------|------|------|
| 等级 | `level` | 经验值满后 +1，提升基本属性（见下文"等级与成长"） |
| 经验值 | `exp` | 战斗胜利获取，达到当前等级所需上限后升级 |
| 血量 | `hp / maxHp` | 归零则倒下（敌人死亡 / 队员退场） |
| 物理防御力 | `defense` | 减免物理伤害 |
| 海蚀力 | `seaPower` | 类似传统 RPG 的"智力"，为海蚀伤害提供角色属性补正；搭配法杖可释放法杖专属技能 |
| 持有武器 | `weaponId` | 角色**本身不存在攻击力属性**，全部伤害基于持有武器计算（见 5.3） |
| 可用技能 | `skills[]` | 技能 ID 列表，指向技能表 |
| 可用道具 | 队伍共享背包 | 战斗中可消耗道具 |

> **重要**：角色没有"攻击力"，也没有"海蚀抵抗力"。伤害输出由武器决定；海蚀伤害是**无法被抵抗的真实伤害**（见 5.4 伤害公式）。

#### 等级与成长

- 战斗胜利后，**存活的全体出战成员**获得敌人配置的 `exp`。
- 经验值达到当前等级上限后升级：`exp` 扣除上限、`level + 1`，溢出经验保留继续累积（可连续升级）。
- 升级曲线（初版）：`所需经验 = 50 × level^1.5`，具体系数通过配置调参。
- 升级时按角色各自的**成长模板**提升基本属性（血量上限、物理防御力、海蚀力），并回复满血：

```
升级后属性 = 基础属性 + 成长值 × (level − 1)
```

- 成长值在 `characters.json` 中按角色配置（见第 6 章示例），例如战士型队员血量成长高，而"信仰海神者"海蚀力成长高，拉开队员定位差异。

#### 关于敌人的伤害面板

敌人不装备武器。敌人的物理攻击力 / 海蚀力直接在 `enemies.json` 中作为"天生武器"面板配置，走同一套伤害公式，保证结算逻辑统一。

### 5.3 武器系统

角色的伤害输出**完全由武器决定**。武器由 `weapons.json` 数据驱动，装备在角色的武器槽上。

#### 武器种类

| 武器 | 类型 | 定位 |
|------|------|------|
| 大剑 | 物理 | 高面板攻击、重击型 |
| 船锚 | 物理 | 极重型钝器，攻高速慢，可附带控制类技能 |
| 电锯 | 物理 | 类似《血源诅咒》的变形武器，多段连击型 |
| 长槊 | 物理 | 中距长柄，攻防均衡 |
| 渔叉 | 物理 | 轻型快速武器，可能附带流血/穿刺类技能 |
| **法杖（特殊）** | 海蚀 | 面板为**海蚀力**而非物理攻击；解锁"法杖专属技能"，所有法杖技能均造成海蚀伤害 |

#### 武器数据构成

| 字段 | 说明 |
|------|------|
| `physAttack` | 武器面板物理攻击力（法杖通常为 0 或极低） |
| `seaPower` | 武器面板海蚀力（法杖的主面板；部分被海蚀侵染的物理武器也可拥有少量） |
| `physScaling` | 武器物理补正系数 |
| `seaScaling` | 武器海蚀补正系数（决定角色 `seaPower` 属性对海蚀伤害的转化率） |
| `skills[]` | 武器附带技能（如法杖专属技能） |

#### 技能与武器的关系

- **所有角色都能释放技能**，不依赖武器种类。
- 技能可声明 `requiresWeapon` 字段（如 `"staff"`），此类技能**仅在装备对应武器时可用**——即"法杖专属技能"。
- 所有法杖专属技能的伤害类型固定为**海蚀伤害**，以海蚀力结算。

### 5.4 战斗系统

回合制战斗由 `BattleSystem` 以**战斗状态机**驱动：

```
BattleStart（入场、播报遭遇）
   │
   ▼
TurnStart（按速度/固定顺序确定行动次序）
   │
   ▼
┌─ PlayerTurn ──选择成员──选择指令(攻击/技能/道具/防御/逃跑)──选择目标──结算
│      │
│      ▼
│  EnemyTurn ──敌人 AI 选择行动──结算
│      │
│      ▼
└─ TurnEnd（结算回合末状态：中毒/增益减益倒计时等）
       │
       ├── 敌方全灭 ──▶ Victory（经验/金钱/掉落结算，经验满则升级）──▶ 返回探索
       ├── 我方全灭 ──▶ Defeat（游戏结束/读档）
       └── 否则回到 TurnStart
```

- **指令集**：攻击（使用武器普攻）、技能（消耗资源，法杖专属技能需装备法杖）、道具（使用共享背包）、防御（减物理伤害）、逃跑（普通战斗可逃，BOSS 战不可）。
- **敌人 AI**：初版按权重随机选择技能与目标；精英/BOSS 可在 JSON 中配置行动脚本（如"血量低于 50% 时释放某技能"）。
- **战斗触发**：探索场景中与敌人碰撞、或踩中 Tiled 中标记的遭遇区域时，携带敌人编组 ID 切入战斗场景。

#### 伤害公式

伤害结算集中在 `DamageCalculator`，分物理 / 海蚀两条线：

**物理伤害**（可被物理防御力减免）：

```
物理伤害 = max(1, 武器物理攻击力 × 武器物理补正 × 技能倍率 × (1 + 物理buff加成) − 目标物理防御力)
```

**海蚀伤害**（真实伤害，双向规则相同——不论己方打敌人还是敌人打己方，都**无法被任何属性减免**，只能被增幅）：

```
海蚀伤害 = (技能/武器面板海蚀力 + 武器面板海蚀力 × 武器海蚀补正 + 角色海蚀力 × 属性补正) × 技能倍率 × (1 + 海蚀buff加成)
```

设计要点：

- 海蚀伤害没有任何对应的防御/抗性属性，命中即按公式全额结算，体现克苏鲁式"不可名状之力"的压迫感。
- buff/debuff 只作用于**增幅侧**（提高己方海蚀输出、或被诅咒后受到的海蚀伤害加深），不存在"海蚀减伤"。
- 各补正系数与面板数值全部来自 `weapons.json` / `skills.json` / `characters.json`，便于调参。

### 5.5 队伍系统

- 队伍上限 **4 人**（主角固定占 1 席）。
- 可招募 NPC 满足条件（对话选项、任务完成等）后加入队伍；队伍满员时提示无法加入（后备队机制留作扩展）。
- 队伍数据由 `PartySystem` 统一持有，战斗场景与背包场景均从此处读取成员属性。
- 探索场景中仅渲染主角（跟随队员的"小队列车"表现留作扩展）。

### 5.6 背包与道具系统

- 背包为**队伍共享**，随时可在探索中打开（战斗中通过"道具"指令访问）。
- 背包界面顶部常驻显示**队伍金钱**（见 5.7），两个页签：
  1. **队伍属性页**：查看每名成员的等级、经验值、血量、物理防御力、海蚀力、当前装备的武器（含武器面板与补正）、已学技能。
  2. **道具页**：道具列表（名称、数量、描述），支持使用/丢弃；武器在此页签中查看并进行装备/更换。
- 道具类型：

| 类型 | 示例 | 说明 |
|------|------|------|
| 武器 | 大剑、船锚、电锯、长槊、渔叉、法杖 | 装备到角色武器槽，决定伤害输出（见 5.3） |
| 消耗品 | 绷带、镇静剂 | 恢复血量或解除异常，战斗内外均可用 |
| 战斗道具 | 圣水、深海盐晶 | 仅战斗中使用，对敌方生效 |
| 关键道具 | 古籍、船票 | 任务/剧情用，不可丢弃 |
| 装备（扩展） | 护符、外套 | 武器以外的防具/饰品槽位，初版可暂缓 |

### 5.7 金钱与商店系统

#### 金钱

- 金钱为**队伍共享**（与背包一致），由 `PartySystem` 持有，字段 `gold`。
- 获取途径：战斗胜利掉落（敌人配置 `gold` 字段）、任务奖励、向商人出售物品。
- 用途：在商人处购买**装备、道具、武器**。

#### 商店

- 与商人 NPC（`NpcType::Merchant`）互动后打开商店界面，由 `ShopSystem` 驱动。
- 商店货架数据驱动，定义在 `shops.json`：每个商人引用一个商店 ID，配置在售商品与价格；不同地区/剧情阶段的商人可挂不同货架。
- 支持**购买**与**出售**（出售价为标价的一定折扣，如 50%）；关键道具不可出售。
- 货架可通过剧情 flags 解锁新商品（如进入 B 线后商人上架海蚀侵染武器）。

#### 商店配置示例（`data/shops.json`）

```json
{
  "harbor_trader": {
    "name": "码头商人",
    "sellRate": 0.5,
    "goods": [
      { "itemId": "bandage",    "price": 20 },
      { "itemId": "greatsword", "price": 350 },
      { "itemId": "coral_staff", "price": 500, "requireFlags": { "route": "B" } }
    ]
  }
}
```

### 5.8 地图系统

- 地图使用 **Tiled** 编辑器制作，通过 **raylib-tiled** 加载渲染。
- 图层约定：

| 图层 | 类型 | 用途 |
|------|------|------|
| `ground` | 瓦片层 | 地面 |
| `decoration` | 瓦片层 | 装饰物（渲染在角色下方/上方各一层） |
| `collision` | 对象层 | 碰撞区域（不可通行） |
| `npc_spawn` | 对象层 | NPC 出生点（自定义属性: npcId） |
| `enemy_zone` | 对象层 | 遭遇区域（自定义属性: encounterGroupId） |
| `portal` | 对象层 | 地图传送点（自定义属性: targetMap, targetX/Y） |

- 相机使用 Raylib `Camera2D` 跟随主角，并限制在地图边界内。

### 5.9 UI 系统

- 基于 Raylib 立即模式绘制，封装通用组件：面板、按钮、列表、血条、对话框。
- 主要界面：
  - **探索 HUD**：队伍简要血条、交互提示（"按 E 交谈"）。
  - **战斗 UI**：我方成员状态栏、指令菜单、目标选择光标、伤害飘字、战斗日志。
  - **背包 UI**：页签式（属性页 / 道具页），顶部显示队伍金钱。
  - **商店 UI**：商品列表（名称、价格、描述）、购买/出售切换、余额显示与确认弹窗。
  - **对话框**：打字机效果文本 + 选项分支（选项可触发招募、开店、任务等事件）。
- 注意加载**中文字体**（Raylib 需通过 `LoadFontEx` 指定字符集范围）。

### 5.10 结局系统

游戏共有 **4 种结局**，由 `EndingSystem` 基于剧情 flags 判定：

| 结局 | 性质 | 触发方式 |
|------|------|------|
| **A** 普通结局 | 可独立成局 | 进入 A 线并完成 A 线主线；未满足 C 的延长条件时，A 直接作为最终结局 |
| **B** 伪结局 | 可独立成局 | 进入 B 线并完成 B 线主线；未满足 D 的延长条件时，B 直接作为最终结局 |
| **C** 隐藏结局 | A 线延长 | 在 A 结局的基础上，**击败 B 线原定的最终 BOSS** 后剧情继续推动，最终到达 C |
| **D** 真结局 | B 线延长 | 在 B 结局的基础上，满足条件后剧情继续推动，最终到达 D |

#### 路线流程

```
              ┌─ 完成 A 线主线 ──────────────────────────▶ 结局 A（普通结局）
 主线分歧点 ──┤  选择 A 线（B 线支线立即断线）
              └─ A 线基础上击败"B 线原定最终 BOSS"，剧情继续 ─▶ 结局 C（隐藏结局）

              ┌─ 完成 B 线主线 ──────────────────────────▶ 结局 B（伪结局）
              ┤  选择 B 线（A 线支线立即断线）
              └─ B 线基础上满足条件，剧情继续推动 ──────────▶ 结局 D（真结局）
```

#### 设计要点

- **A / B 两线相斥**：在主线分歧点选定一条路线后，存档 flags 写入 `route`（`"A"` 或 `"B"`），另一条线的支线与主线任务立即**断线**——相关 NPC 对话切换为不可推进状态，任务列表标记为"已断"，本周目无法再完成或推进。
- **C / D 是延长而非分支**：C 不是独立入口，必须先走完 A 线（并在过程中满足隐藏条件、击败 B 线原定最终 BOSS）；D 同理挂在 B 线之后。判定顺序为"先看延长条件，不满足则落回 A / B"。
- **数据驱动**：结局定义与触发条件写在 `endings.json`，由 `EndingSystem` 在关键剧情节点检查 flags：

```json
{
  "A": { "type": "normal", "require": { "route": "A", "a_mainline_done": true } },
  "B": { "type": "false",  "require": { "route": "B", "b_mainline_done": true } },
  "C": { "type": "hidden", "require": { "route": "A", "a_mainline_done": true, "b_final_boss_defeated": true } },
  "D": { "type": "true",   "require": { "route": "B", "b_mainline_done": true, "d_extension_done": true } }
}
```

- **断线的实现**：对话与任务的可用性条件均引用 `route` flag（如 B 线任务要求 `route != "A"`），无需为断线单独写逻辑，复用 flags 判定即可。

### 5.11 数据与存档系统

- `DataLoader` 启动时加载 `data/` 下所有 JSON 配置到内存表（技能表、道具表、敌人表等），运行期只读。
- `SaveManager` 负责存档，存档内容：

```json
{
  "version": 1,
  "map": "town_innsmouth.tmx",
  "position": { "x": 320, "y": 480 },
  "gold": 240,
  "party": [
    { "id": "hero", "level": 5, "exp": 130, "hp": 42, "weapon": "harpoon", "skills": ["slash", "ward"] }
  ],
  "inventory": [ { "itemId": "bandage", "count": 3 }, { "itemId": "greatsword", "count": 1 } ],
  "flags": { "route": "A", "recruited_fisherman": true, "b_final_boss_defeated": false }
}
```

- `flags` 字典记录剧情/任务进度，对话系统、招募条件、商店货架解锁与结局判定（见 5.10）均基于 flags 判断。

---

## 6. 数据结构设计

### 角色配置示例（`data/characters.json`）

```json
{
  "hero": {
    "name": "调查员",
    "texture": "textures/hero.png",
    "stats": { "maxHp": 100, "defense": 8, "seaPower": 12 },
    "growth": { "maxHp": 8, "defense": 1, "seaPower": 2 },
    "weapon": "harpoon",
    "skills": ["slash", "first_aid"]
  }
}
```

> `stats` 为 1 级基础属性，`growth` 为每级成长值：`当前属性 = 基础属性 + 成长值 × (level − 1)`。

### 武器配置示例（`data/weapons.json`）

```json
{
  "greatsword": {
    "name": "大剑",
    "type": "physical",
    "physAttack": 25, "seaPower": 0,
    "physScaling": 1.2, "seaScaling": 0.0
  },
  "anchor": {
    "name": "船锚",
    "type": "physical",
    "physAttack": 32, "seaPower": 0,
    "physScaling": 1.0, "seaScaling": 0.0,
    "skills": ["anchor_slam"]
  },
  "chainsaw": {
    "name": "电锯",
    "type": "physical",
    "physAttack": 14, "seaPower": 0,
    "physScaling": 1.1, "seaScaling": 0.0,
    "skills": ["rev_combo"]
  },
  "pike": {
    "name": "长槊",
    "type": "physical",
    "physAttack": 20, "seaPower": 0,
    "physScaling": 1.1, "seaScaling": 0.0
  },
  "harpoon": {
    "name": "渔叉",
    "type": "physical",
    "physAttack": 15, "seaPower": 3,
    "physScaling": 1.0, "seaScaling": 0.2
  },
  "coral_staff": {
    "name": "珊瑚法杖",
    "type": "staff",
    "physAttack": 3, "seaPower": 22,
    "physScaling": 0.3, "seaScaling": 1.3,
    "skills": ["tide_bolt", "abyss_gaze"]
  }
}
```

### 技能配置示例（`data/skills.json`）

```json
{
  "slash": {
    "name": "挥砍",
    "damageType": "physical",
    "multiplier": 1.2,
    "target": "single_enemy",
    "cost": 0
  },
  "tide_bolt": {
    "name": "潮涌之矢",
    "damageType": "sea",
    "requiresWeapon": "staff",
    "baseSeaPower": 10,
    "multiplier": 1.5,
    "target": "single_enemy"
  },
  "brine_curse": {
    "name": "咸腥诅咒",
    "damageType": "none",
    "target": "single_enemy",
    "effect": { "type": "debuff", "stat": "seaTakenAmp", "value": 0.25, "turns": 2 }
  }
}
```

> `requiresWeapon: "staff"` 表示法杖专属技能；`seaTakenAmp` 是"受到的海蚀伤害增幅"——海蚀伤害没有减免属性，debuff 只能往增幅方向作用。

### 敌人配置示例（`data/enemies.json`）

敌人的 `innateWeapon` 即"天生武器"面板，与武器走同一套伤害公式：

```json
{
  "deep_one": {
    "name": "深潜者",
    "rank": "Normal",
    "texture": "textures/deep_one.png",
    "stats": { "maxHp": 60, "defense": 5, "seaPower": 8 },
    "innateWeapon": { "physAttack": 12, "seaPower": 6, "physScaling": 1.0, "seaScaling": 1.0 },
    "skills": ["claw", "brine_spit"],
    "drops": [ { "itemId": "fish_scale", "chance": 0.5 } ],
    "exp": 25,
    "gold": 15
  },
  "dagon_avatar": {
    "name": "大衮化身",
    "rank": "Boss",
    "stats": { "maxHp": 800, "defense": 15, "seaPower": 35 },
    "innateWeapon": { "physAttack": 30, "seaPower": 25, "physScaling": 1.2, "seaScaling": 1.2 },
    "skills": ["tidal_crush", "abyss_call"],
    "ai": [ { "when": "hp<0.5", "cast": "abyss_call" } ],
    "canFlee": false,
    "exp": 600,
    "gold": 800
  }
}
```

### 核心类骨架（示意）

```cpp
struct Stats {
    int maxHp, hp;
    int defense;    // 物理防御力
    int seaPower;   // 海蚀力（类似传统 RPG 的智力）
    // 注意：没有攻击力（由武器决定），也没有海蚀抗性（海蚀伤害不可减免）
};

struct Growth {
    int maxHp, defense, seaPower;   // 每级成长值
};

struct Weapon {
    std::string id, name;
    WeaponType type;      // Greatsword / Anchor / Chainsaw / Pike / Harpoon / Staff
    int physAttack;       // 武器面板物理攻击力
    int seaPower;         // 武器面板海蚀力
    float physScaling;    // 物理补正
    float seaScaling;     // 海蚀补正
    std::vector<std::string> skillIds;  // 武器附带/专属技能
};

class Character {
public:
    virtual ~Character() = default;
    void TakeDamage(int amount, DamageType type);  // 海蚀伤害无视 defense 全额结算
    bool IsAlive() const { return stats.hp > 0; }

protected:
    std::string id, name;
    int level = 1;
    int exp = 0;                      // 升级所需：50 × level^1.5（可调参）
    Stats stats;
    Growth growth;                    // 升级时按成长模板提升 stats
    const Weapon* weapon = nullptr;   // 玩家侧为装备武器；敌人侧指向天生武器面板
    std::vector<std::string> skillIds;
    Vector2 position;
};

// 派生关系见 5.2
class Player : public Character { /* 探索输入、移动 */ };
class Npc    : public Character { NpcType type; std::string dialogueId; };
class Enemy  : public Character { EnemyRank rank; /* AI、掉落、经验 */ };
```

---

## 7. 后续扩展方向

- **理智值（San 值）系统**：契合克苏鲁题材，目睹怪异降低理智，影响战斗表现甚至触发幻觉事件。
- **武器变形机制**：参考《血源诅咒》，电锯等武器可在战斗中切换形态，改变面板与技能组。
- **武器强化/侵染**：用素材提升武器面板，或让物理武器被"海蚀侵染"获得海蚀面板。
- **防具与饰品**：武器以外的护具/护符槽位，提供防御与海蚀力加成。
- **后备队**：招募人数超过 4 人时可在营地更换出战成员。
- **战斗速度/行动条**：引入速度属性，替代固定行动顺序。
- **周目继承（New Game+）**：多结局设计天然适合多周目，通关后继承武器/海蚀力开启新周目，降低集齐 ABCD 结局的重复成本。
- **成就与统计**：本地记录战斗、探索与结局达成数据。

---

*文档版本 v0.4 — 随开发进度持续更新。*

*变更记录：*

- *v0.4：新增金钱与商店系统（商人处购买装备/道具/武器）；新增经验值与等级成长系统。*
- *v0.3：删除网络模块（改为纯单机游戏）；新增结局系统（A/B/C/D 四结局，A、B 两线相斥）。*
- *v0.2：新增武器系统；移除攻击力/海蚀抵抗力，新增海蚀力属性；海蚀伤害改为不可减免的真实伤害。*
