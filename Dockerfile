FROM ubuntu:24.04

RUN apt-get update && \
    apt-get install -y \
        build-essential \
        cmake && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN rm -rf build && \
    cmake -S . -B build && \
    cmake --build build --config Release

EXPOSE 8080

CMD ["./build/backend/menu_calculator", "--server"]