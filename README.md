# 停车场管理系统

## 快速开始

### 方式一：Docker Compose（推荐）

```bash
# 构建镜像并启动容器（程序自动运行，直接进入交互界面）
docker compose up --build

# 后台运行（构建完成后在后台启动）
docker compose up --build -d
# 附着到后台容器进行交互
docker attach parking-system

# 自定义配置（通过环境变量）
PARKING_CAPACITY=200 PARKING_FEE_PER_HOUR=8 docker compose up --build

# 停止并删除容器
docker compose down
```

容器启动后程序会直接运行，无需手动 `docker exec` 进入执行。

### 方式二：本地 CMake 编译

需要提前安装 CMake（>=3.16）和 C++17 编译器（GCC/Clang/MSVC）。

**Linux / macOS / Windows (MinGW):**
```bash
cd backend
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
./build/parking_system        # Linux/macOS
.\build\parking_system.exe    # Windows
```

**Windows (Visual Studio):**
```bash
cd backend
cmake -B build -S .
cmake --build build --config Release
.\build\Release\parking_system.exe
```

也可以直接双击 `backend/ParkingSystem.sln` 用 Visual Studio 2022 打开，按 F5 运行。

## 配置说明

业务参数通过环境变量配置，无需修改代码重新编译：

| 环境变量 | 说明 | 默认值 |
|---------|------|--------|
| `PARKING_CAPACITY` | 停车场最大车位数量 | 100 |
| `PARKING_FEE_PER_HOUR` | 每小时停车费率（元） | 5.0 |

也可以在项目根目录创建 `.env` 文件进行配置：
```
PARKING_CAPACITY=150
PARKING_FEE_PER_HOUR=6.0
```

## 功能使用

启动后输入 `0` 可添加 5 条测试数据：
- 京A12345、沪B67890、粤C11111、苏D22222、浙E33333

按菜单提示输入对应数字选择功能，输入 `q` 退出系统。

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

### 收费计算

- 费用 = 停车时长（分钟）/ 60 × 每小时费率
- 停车时长根据进场时间戳动态计算，实时更新

---

## 项目结构

```
├── .github/workflows/
│   └── ci.yml                    # GitHub Actions CI 配置
├── backend/
│   ├── src/
│   │   ├── main.cpp              # 主程序入口 & 配置加载
│   │   ├── Vehicle.h             # 车辆结构体定义
│   │   ├── ParkingLot.h          # 停车场类声明
│   │   ├── ParkingLot.cpp        # 停车场类基本操作实现
│   │   ├── ParkingLot_Sort.cpp   # 排序算法实现
│   │   └── ParkingLot_Search.cpp # 查找算法实现
│   ├── CMakeLists.txt            # CMake 构建配置（统一源文件管理）
│   ├── ParkingSystem.sln         # VS2022 解决方案文件
│   ├── ParkingSystem.vcxproj     # VS2022 项目文件
│   ├── ParkingSystem.vcxproj.filters  # VS2022 筛选器文件
│   └── Dockerfile                # Docker 多阶段构建
├── docker-compose.yml            # Docker Compose 配置
├── .gitignore                    # Git 忽略文件
└── README.md                     # 项目说明
```

---

## 技术栈

- **语言**：C++17
- **构建系统**：CMake（>=3.16），同时保留 Visual Studio 工程支持
- **编译器**：GCC 13 / Clang / MSVC (Visual Studio 2022)
- **容器化**：Docker + Docker Compose，多阶段构建静态链接
- **CI/CD**：GitHub Actions
- **跨平台**：支持 Windows / Linux / macOS，支持 ARM 和 X86 架构
