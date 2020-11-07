cmake_minimum_required(VERSION 3.10)

add_subdirectory(Loki)

project(compiler)

add_executable(
    compiler
    main.cpp
)

target_link_libraries(compiler PRIVATE loki)
