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

WORKDIR /deps
RUN wget https://github.com/c-ares/c-ares/releases/download/cares-1_15_0/c-ares-1.15.0.tar.gz
RUN tar -xzvf c-ares-1.15.0.tar.gz
WORKDIR /build-deps/c-ares
RUN cmake /deps/c-ares-1.15.0
RUN make
RUN make install

WORKDIR /deps
RUN wget https://github.com/google/googletest/archive/release-1.8.1.tar.gz
RUN tar -xzvf release-1.8.1.tar.gz
WORKDIR /build-deps/gtest
RUN cmake /deps/googletest-release-1.8.1/
RUN make
RUN make install

WORKDIR /deps
RUN wget https://github.com/grpc/grpc/archive/v1.17.2.tar.gz
RUN tar -xzvf v1.17.2.tar.gz
WORKDIR /build-deps/grpc
RUN ls /deps
RUN cmake -DgRPC_INSTALL=ON -DgRPC_ZLIB_PROVIDER=package -DgRPC_PROTOBUF_PROVIDER=package -DgRPC_CARES_PROVIDER=package -DgRPC_SSL_PROVIDER=package  /deps/grpc-1.17.2
RUN make
RUN make install

ADD ./src /base/src
ADD ./proto /base/proto
ADD ./test /base/test
COPY ./CMakeLists.txt /base/

WORKDIR /build
RUN cmake ../base
RUN make
RUN make test

COPY ./test.sh /

CMD ["/bin/bash", "/test.sh"]
