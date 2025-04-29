# Build stage
FROM alpine:3.19 AS builder

RUN apk add --no-cache \
    build-base \
    cmake \
    make \
    linux-headers \
    perl \
    boost-build \
    python3 \
    py3-pip \
    && pip3 install --break-system-packages conan

WORKDIR /app

COPY CMakeLists.txt /app/
COPY conanfile.txt /app/
COPY config.json /app/
COPY static /app/static/
COPY src/ /app/src/

RUN conan profile detect --force
RUN conan install . --output-folder=build --build=missing -s build_type=Release

WORKDIR /app/build
RUN cmake .. -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
RUN make

# Runtime stage
FROM alpine:3.19

RUN apk add --no-cache libstdc++

WORKDIR /app

COPY --from=builder /app/build/app /app/app
COPY --from=builder /app/config.json /app/config.json
COPY --from=builder /app/static /app/static

CMD ["./app"]
