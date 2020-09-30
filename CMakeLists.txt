cmake_minimum_required(VERSION 3.17)
project(dslib)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_C_STANDARD 99)

include_directories(include)

file(GLOB SOURCES src/*.c)

add_library(dslib SHARED ${SOURCES})

add_executable(test_dslib main.c)
target_link_directories(test_dslib PRIVATE include)
target_link_libraries(test_dslib PRIVATE dslib)
