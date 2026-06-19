FROM gcc:13-bookworm AS builder

WORKDIR /build

RUN apt-get update && apt-get install -y cmake && rm -rf /var/lib/apt/lists/*

COPY CMakeLists.txt ./
COPY src/ ./src/

RUN cmake -B build -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build -j$(nproc)

FROM debian:bookworm

WORKDIR /app

ENV TZ=Asia/Shanghai
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

ENV PARKING_CAPACITY=100
ENV PARKING_FEE_PER_HOUR=5.0

COPY --from=builder /build/build/parking_system .

CMD ["./parking_system"]
