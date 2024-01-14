cmake_minimum_required(VERSION 3.10)
project(MyProject)

add_definitions(-DEXPORT_QUTILS_LIB)


# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含子目录
add_subdirectory(src)
