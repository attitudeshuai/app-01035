# 停车场管理系统 - C++ 后端
# 跨平台支持 ARM 和 X86

# 使用相同的基础镜像进行构建和运行，避免 GLIBC 版本不兼容
FROM gcc:13-bookworm AS builder

WORKDIR /app

# 复制源代码
COPY src/ ./src/

# 静态链接编译，避免运行时依赖问题（多文件编译）
RUN g++ -std=c++17 -O2 -static-libgcc -static-libstdc++ -I./src \
    -o parking_system \
    src/main.cpp \
    src/ParkingLot.cpp \
    src/ParkingLot_Sort.cpp \
    src/ParkingLot_Search.cpp

# 运行阶段 - 使用相同的基础镜像
FROM debian:bookworm

WORKDIR /app

# 设置时区为北京时间
ENV TZ=Asia/Shanghai
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# 从构建阶段复制可执行文件
COPY --from=builder /app/parking_system .

# 设置入口点 - 使用 tail 保持容器运行
CMD ["tail", "-f", "/dev/null"]
