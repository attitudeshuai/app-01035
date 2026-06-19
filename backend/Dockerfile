# 停车场管理系统 - C++ 后端
# 使用 CMake 统一构建，跨平台支持 ARM 和 X86

FROM gcc:13-bookworm AS builder

WORKDIR /build

RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    make \
    && rm -rf /var/lib/apt/lists/*

COPY CMakeLists.txt ./
COPY src/ ./src/

RUN cmake -B build -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_CXX_FLAGS="-static-libgcc -static-libstdc++" \
    && cmake --build build -j$(nproc) \
    && cmake --install build --prefix /out

FROM debian:bookworm-slim

WORKDIR /app

ENV TZ=Asia/Shanghai
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

ENV PARKING_CAPACITY=100
ENV PARKING_FEE_PER_HOUR=5.0

COPY --from=builder /out/bin/parking_system ./

ENTRYPOINT ["./parking_system"]
