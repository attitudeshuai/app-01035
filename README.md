# 停车场管理系统

## 快速开始

### 方式一：Docker 运行（推荐）

```bash
# 构建镜像并直接启动程序（容器启动后自动进入交互界面）
docker compose up --build

# 自定义配置参数（容量和费率可配置）
PARKING_CAPACITY=200 PARKING_FEE_PER_HOUR=8.0 docker compose up --build

# 停止并清理
docker compose down
```

容器启动后会直接进入程序交互菜单，无需手动 `docker exec` 进入。

### 方式二：CMake 命令行编译

```bash
cd backend

# 配置构建
cmake -B build

# 编译
cmake --build build -j

# 运行
# Windows:
build\parking_system.exe
# Linux/macOS:
./build/parking_system
```

### 方式三：Visual Studio 2022 打开

Visual Studio 2017 及以上版本原生支持 CMake 项目：
1. 选择 **"打开本地文件夹"**，选择 `backend/` 目录
2. 或者直接打开 `backend/CMakeLists.txt`
3. VS 会自动识别 CMake 项目，按 F5 即可运行

新增源文件只需放到 `src/` 目录下，CMake 会自动发现，无需手动维护工程文件。

## 配置参数

业务参数通过环境变量配置，不硬编码：

| 环境变量 | 说明 | 默认值 |
|----------|------|--------|
| `PARKING_CAPACITY` | 停车场总车位数 | 100 |
| `PARKING_FEE_PER_HOUR` | 每小时停车费率（元） | 5.0 |

## Services

| 服务 | 说明 | 端口 |
|------|------|------|
| backend | C++ 停车场管理系统 | 控制台应用 |

## 测试数据

启动后输入 `0` 可添加5条测试数据：
- 京A12345、沪B67890、粤C11111、苏D22222、浙E33333

## 题目内容

调用visual stdio 2022 c++   编程序要求设计并实现一个停车场管理系统，即定义一个包含车辆信息（车牌号，进场时间，停车时长，应缴费用）的顺序表，顺序表中的序号可以看作是停车位编号，系统至少包含以下功能： 
（1）指定车辆数，逐个输入车辆信息； 
（2）逐个显示车辆管理表中所有车辆的相关信息； 
（3）给定一个车辆信息，插入到表中指定的位置； 
（4）删除指定位置的车辆记录，删除时给出车辆的停车时长和应缴费用。 
（5）统计表中车辆数； 
（6）利用直接插入排序或者折半插入排序按照车牌号进行排序； 
（7）利用快速排序按照车牌号进行排序； 
（8）根据车牌号进行折半查找，要求使用递归算法实现，成功返回此车辆的车牌号和和进场时间； 
（9）根据车牌号进行折半查找，要求使用非递归算法实现，成功返回此车辆的车牌号和和进场时间。1．建立车辆管理表 
2．根据要求对车辆进行查找

---

## 功能说明

### 数据结构

- **顺序表**：使用动态数组存储车辆信息
- **车辆结构体**：包含车牌号、进场时间、停车时长、应缴费用

### 算法实现

| 功能 | 算法 | 时间复杂度 |
|------|------|------------|
| 插入排序 | 直接插入排序 | O(n²) |
| 插入排序 | 折半插入排序 | O(n²) |
| 快速排序 | 分治法 | O(n log n) |
| 折半查找（递归） | 二分查找 | O(log n) |
| 折半查找（非递归） | 二分查找 | O(log n) |

### 收费标准

- 默认每小时 5 元（可通过环境变量 `PARKING_FEE_PER_HOUR` 配置）
- 费用 = 停车时长（分钟）/ 60 × 每小时费率

---

## 项目结构

```
├── .github/
│   └── workflows/
│       └── ci.yml              # GitHub Actions CI 配置
├── backend/
│   ├── src/
│   │   ├── main.cpp              # 主程序入口
│   │   ├── Vehicle.h             # 车辆结构体定义
│   │   ├── ParkingLot.h          # 停车场类声明
│   │   ├── ParkingLot.cpp        # 停车场类基本操作实现
│   │   ├── ParkingLot_Sort.cpp   # 排序算法实现
│   │   └── ParkingLot_Search.cpp # 查找算法实现
│   ├── CMakeLists.txt            # CMake 统一构建配置（唯一源文件清单）
│   └── Dockerfile                # Docker 多阶段构建
├── docker-compose.yml            # Docker Compose 配置
├── .gitignore                    # Git 忽略文件
└── README.md                     # 项目说明
```

---

## CI/CD

项目配置了 GitHub Actions 自动构建验证，每次 push 或 PR 会自动执行：
- Ubuntu + GCC + CMake 构建
- Windows + Visual Studio + CMake 构建
- Docker 镜像构建验证

---

## 技术栈

- **语言**：C++ 17
- **构建系统**：CMake（统一管理，自动扫描源文件）
- **编译器**：GCC / Clang / MSVC (Visual Studio 2017+)
- **容器化**：Docker 多阶段构建 + Docker Compose，静态链接无运行时依赖
- **跨平台**：支持 Windows / Linux / macOS，支持 ARM 和 X86 架构
