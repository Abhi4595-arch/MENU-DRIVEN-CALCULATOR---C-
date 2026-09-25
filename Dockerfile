FROM ubuntu:24.04

RUN apt-get update && \
    apt-get install -y \
        build-essential \
        cmake \
        nginx && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN rm -rf build && \
    cmake -S . -B build && \
    cmake --build build --config Release

RUN rm -rf /usr/share/nginx/html/* && \
    cp -r frontend/* /usr/share/nginx/html/ && \
    rm -f /etc/nginx/sites-enabled/default && \
    cp nginx.render.conf /etc/nginx/conf.d/default.conf

EXPOSE 10000

CMD ["sh", "-c", "PORT=8080 ./build/backend/menu_calculator --server & nginx -g 'daemon off;'"]
