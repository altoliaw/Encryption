cmake_minimum_required(VERSION 3.16)
project(ENCRYPTION LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 99)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_library(Mains
    Entry.c
)

target_include_directories(Mains PUBLIC ../../Headers)

add_subdirectory(Sources)
add_subdirectory(tests)

