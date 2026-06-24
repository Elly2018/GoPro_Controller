#!/bin/bash

# Create a separate build directory for server
mkdir -p build_server_amd64
cd build_server_amd64

# Configure CMake with Toolchain
cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_SERVER=ON -DBUILD_MASTER=OFF

# Build
cmake --build . -j $nproc
