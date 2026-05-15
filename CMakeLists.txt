cmake_minimum_required(VERSION 3.20)

project(loom)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(SOURCES
    main.c
)

add_executable(loom ${SOURCES})
