# 停车场管理系统 - C++ 后端
# 跨平台支持 ARM 和 X86

# ===== 构建阶段：使用 CMake 统一构建 =====
FROM gcc:13-bookworm AS builder

RUN apt-get update \
    && apt-get install -y --no-install-recommends cmake \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# 仅复制构建所需文件，源文件清单由 CMakeLists.txt 统一维护
COPY CMakeLists.txt ./
COPY src/ ./src/

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release \
    && cmake --build build --parallel

# ===== 运行阶段：精简镜像，直接运行程序 =====
FROM debian:bookworm-slim

WORKDIR /app

# 设置时区为北京时间
ENV TZ=Asia/Shanghai
RUN apt-get update \
    && apt-get install -y --no-install-recommends tzdata \
    && ln -snf /usr/share/zoneinfo/$TZ /etc/localtime \
    && echo $TZ > /etc/timezone \
    && rm -rf /var/lib/apt/lists/*

# 业务参数：可通过 docker run -e / docker-compose 覆盖，无需改代码
ENV PARKING_CAPACITY=100 \
    PARKING_FEE_PER_HOUR=5.0

# 从构建阶段复制可执行文件
COPY --from=builder /app/build/parking_system /app/parking_system

# 容器启动后直接进入交互式程序，无需再 docker exec
ENTRYPOINT ["/app/parking_system"]
