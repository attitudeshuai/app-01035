# 停车场管理系统

基于顺序表实现的车辆信息管理控制台程序。构建系统统一使用 **CMake**，源文件清单只需在 `CMakeLists.txt` 一处维护（实际通过 `file(GLOB ...)` 自动收集 `src/` 下的源文件，新增文件无需任何同步）。

## How to Run

### 方式一：Docker（推荐，开箱即用）

```bash
# 构建并启动；容器启动后程序直接运行，无需再 docker exec
docker-compose run --rm backend

# 或者使用 docker 直接运行
docker build -t parking-system ./backend
docker run --rm -it parking-system
```

业务参数（车位容量、每小时费率）通过环境变量配置，无需改代码：

```bash
docker run --rm -it \
  -e PARKING_CAPACITY=200 \
  -e PARKING_FEE_PER_HOUR=8.0 \
  parking-system
```

也可在 [docker-compose.yml](docker-compose.yml) 的 `environment` 段中集中配置。

### 方式二：本地 CMake 构建

```bash
cd backend
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel

# 运行（Linux / macOS）
./build/parking_system

# 运行（Windows，多配置生成器）
./build/Release/parking_system.exe
```

通过环境变量自定义业务参数：

```bash
# Linux / macOS
PARKING_CAPACITY=200 PARKING_FEE_PER_HOUR=8.0 ./build/parking_system

# Windows PowerShell
$env:PARKING_CAPACITY=200; $env:PARKING_FEE_PER_HOUR=8.0; ./build/Release/parking_system.exe
```

### 方式三：Visual Studio 2022（使用 CMake 工程）

VS 2022 原生支持 CMake：菜单选择 **文件 → 打开 → CMake...**，选中 `backend/CMakeLists.txt` 即可。已提供 [CMakePresets.json](backend/CMakePresets.json) 内置 `default` / `debug` / `msvc-x64` 三种预设。

> 旧的 `.sln` / `.vcxproj` 已移除。源文件清单只在 `CMakeLists.txt` 一处维护，新增/删除 `src/*.cpp` 后重新配置即可，无需手动同步多个工程文件。

## 配置项

| 环境变量 | 默认值 | 说明 |
|---|---|---|
| `PARKING_CAPACITY` | `100` | 停车场最大容量（车位数） |
| `PARKING_FEE_PER_HOUR` | `5.0` | 每小时收费标准（元） |
| `TZ` | `Asia/Shanghai` | 时区（仅容器） |

## CI

GitHub Actions 工作流见 [.github/workflows/ci.yml](.github/workflows/ci.yml)，包含：

- **build**：在 Ubuntu 与 Windows 上用 CMake 构建并做冒烟测试，上传可执行文件作为 artifact。
- **docker**：构建 Docker 镜像并验证 `ENTRYPOINT` 启动后程序可直接运行。

## 测试账号

本系统为控制台应用，无需登录账号。

启动后输入 `0` 可添加 5 条测试数据：
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

- 默认每小时 5 元（可通过 `PARKING_FEE_PER_HOUR` 调整）
- 默认容量 100 个车位（可通过 `PARKING_CAPACITY` 调整）
- 费用 = 停车时长（分钟）/ 60 × 每小时费率

---

## 项目结构

```
├── backend/
│   ├── src/
│   │   ├── main.cpp              # 主程序入口（读取环境变量配置）
│   │   ├── Vehicle.h             # 车辆结构体定义
│   │   ├── ParkingLot.h          # 停车场类声明
│   │   ├── ParkingLot.cpp        # 停车场类基本操作实现
│   │   ├── ParkingLot_Sort.cpp   # 排序算法实现
│   │   └── ParkingLot_Search.cpp # 查找算法实现
│   ├── CMakeLists.txt            # 统一构建入口（源文件清单的唯一权威来源）
│   ├── CMakePresets.json         # CMake 预设（VS / 命令行通用）
│   └── Dockerfile                # 多阶段构建：CMake 构建 + 直接运行
├── docker-compose.yml            # Docker Compose 配置（含业务参数）
├── .github/workflows/ci.yml      # GitHub Actions CI
├── .gitignore                    # Git 忽略文件
└── README.md                     # 项目说明
```

---

## 技术栈

- **语言**：C++ 17
- **构建系统**：CMake 3.16+
- **编译器**：GCC 13 / Clang / MSVC (Visual Studio 2022)
- **容器化**：Docker + Docker Compose
- **CI**：GitHub Actions（Linux + Windows + Docker）
- **跨平台**：支持 Windows / Linux / macOS，支持 ARM 和 X86 架构
