cmake_minimum_required(VERSION 3.16)
project(DungeonRPG)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Tell compiler to find headers
include_directories(src/entities)

# The executable
add_executable(dungeon src/main.cpp)