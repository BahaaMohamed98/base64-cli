cmake_minimum_required(VERSION 3.25)
project(base64-cli)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

add_executable(base64
    ./src/main.cpp
    ./src/base64.hpp
)
