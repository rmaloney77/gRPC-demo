FROM alpine:edge

RUN apk add --update --no-cache \
    build-base \
    g++ \
    gcc \
    bash \
    cmake \
    protobuf-dev \
    openssl-dev \
    wget



#static zlib
#RUN wget https://zlib.net/zlib-1.2.11.tar.gz
#RUN ./configure --prefix=/home/ryan/dev/lib/zlib/1.2.11 --static
#ryan@DESKTOP-8ONCJ9D:~/Projects/wb-app/build$ cmake -Dc-ares_DIR=/home/ryan/dev/lib/c-ares/lib/cmake/c-ares -DCMAKE_PREF
#IX_PATH=/home/ryan/dev/lib/grpc/lib/cmake/grpc ../src/

#may need customprotobuf

#c-ares
#https://github.com/c-ares/c-ares.git
#RUN cmake ../c-ares

WORKDIR /deps
RUN wget https://github.com/c-ares/c-ares/releases/download/cares-1_15_0/c-ares-1.15.0.tar.gz
RUN tar -zxvf c-ares-1.15.0.tar.gz
WORKDIR /build-deps/c-ares
RUN cmake /deps/c-ares-1.15.0
RUN make
RUN make install

WORKDIR /deps
RUN wget https://github.com/grpc/grpc/archive/v1.17.2.tar.gz
RUN tar -xzvf v1.17.2.tar.gz
WORKDIR /build-deps/grpc
#RUN cmake ../grpc-1.17.2
#cmake -DgRPC_INSTALL=ON -DgRPC_ZLIB_PROVIDER=package ../grpc
RUN ls /deps
RUN cmake -DgRPC_INSTALL=ON -DgRPC_ZLIB_PROVIDER=package -DgRPC_PROTOBUF_PROVIDER=package -DgRPC_CARES_PROVIDER=package -DgRPC_SSL_PROVIDER=package  /deps/grpc-1.17.2
RUN make
RUN make install

COPY ./ /src
WORKDIR /build
RUN cmake ../src
RUN make

EXPOSE 8080
CMD ["/bin/bash"]
