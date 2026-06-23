#!/bin/bash

# Create build directory
mkdir -p build_master_amd64
cd build_master_amd64

cp ../*.otf .

# Configure CMake
cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_SERVER=OFF -DBUILD_MASTER=ON

cp compile_commands.json ..

# Build
cmake --build . -j $nproc

