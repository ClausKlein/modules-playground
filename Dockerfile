FROM ubuntu:25.10

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    g++-15 \
    gcc-15 \
    ninja-build \
    wget \
    && rm -rf /var/lib/apt/lists/*

RUN wget https://github.com/Kitware/CMake/releases/download/v4.2.3/cmake-4.2.3-linux-x86_64.tar.gz -q && \
    tar -xf cmake-4.2.3-linux-x86_64.tar.gz && \
    mv cmake-4.2.3-linux-x86_64 /opt

# Prefer gcc-15/g++-15 as default (optional; remove if you want system default)
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-15 100 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-15 100

WORKDIR /workspace
