# 停车场管理系统

## How to Run

### 方式一：Visual Studio 2022 运行（推荐）

1. 双击 `backend/ParkingSystem.sln` 打开解决方案
2. 按 F5 运行（或 Ctrl+F5 无调试运行）

### 方式二：Docker 运行

```bash
# 构建并启动
docker-compose up --build -d

# 进入交互式终端运行程序
docker exec -it parking-system ./parking_system

# 停止容器
docker-compose down
```

### 方式三：命令行编译运行

```bash
# Windows (MinGW)
cd backend
g++ -std=c++17 -I./src -o parking_system.exe src/main.cpp src/ParkingLot.cpp src/ParkingLot_Sort.cpp src/ParkingLot_Search.cpp
parking_system.exe

# Linux / macOS
cd backend
g++ -std=c++17 -I./src -o parking_system src/main.cpp src/ParkingLot.cpp src/ParkingLot_Sort.cpp src/ParkingLot_Search.cpp
./parking_system
```

## Services

| 服务 | 说明 | 端口 |
|------|------|------|
| backend | C++ 停车场管理系统 | 控制台应用 |

## 测试账号

本系统为控制台应用，无需登录账号。

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

- 默认每小时 5 元
- 费用 = 停车时长（分钟）/ 60 × 每小时费率

---

## 项目结构

```
├── backend/
│   ├── src/
│   │   ├── main.cpp              # 主程序入口
│   │   ├── Vehicle.h             # 车辆结构体定义
│   │   ├── ParkingLot.h          # 停车场类声明
│   │   ├── ParkingLot.cpp        # 停车场类基本操作实现
│   │   ├── ParkingLot_Sort.cpp   # 排序算法实现
│   │   └── ParkingLot_Search.cpp # 查找算法实现
│   ├── ParkingSystem.sln         # VS2022 解决方案文件
│   ├── ParkingSystem.vcxproj     # VS2022 项目文件
│   ├── ParkingSystem.vcxproj.filters  # VS2022 筛选器文件
│   └── Dockerfile                # Docker 构建文件
├── docker-compose.yml            # Docker Compose 配置
├── .gitignore                    # Git 忽略文件
├── README.md                     # 项目说明
└── 轨迹/
    └── label-01035.md            # 开发轨迹记录
```

---

## 技术栈

- **语言**：C++ 17
- **编译器**：GCC 13 / MSVC (Visual Studio 2022)
- **容器化**：Docker + Docker Compose
- **跨平台**：支持 Windows / Linux / macOS，支持 ARM 和 X86 架构
