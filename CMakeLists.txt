cmake_minimum_required(VERSION 3.10)
project(oj_023_deque LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Favor fast, safe build flags
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-O2 -pipe -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wconversion -Wsign-conversion)
endif()

add_executable(code src/main.cpp)

# For larger inputs
if (UNIX)
  target_compile_definitions(code PRIVATE _DEFAULT_SOURCE)
endif()
