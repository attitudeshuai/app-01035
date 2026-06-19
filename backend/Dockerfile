FROM gcc:13-bookworm AS builder

RUN apt-get update && apt-get install -y --no-install-recommends cmake && rm -rf /var/lib/apt/lists/*

WORKDIR /build

COPY CMakeLists.txt ./
COPY src/ ./src/

RUN cmake -B build -S . -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build -j$(nproc)

FROM debian:bookworm-slim

WORKDIR /app

RUN apt-get update && apt-get install -y --no-install-recommends libstdc++6 tzdata && rm -rf /var/lib/apt/lists/*

ENV TZ=Asia/Shanghai
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

ENV PARKING_CAPACITY=100
ENV PARKING_FEE_PER_HOUR=5.0

COPY --from=builder /build/build/parking_system .

ENTRYPOINT ["./parking_system"]
