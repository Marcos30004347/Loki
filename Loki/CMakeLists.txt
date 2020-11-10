cmake_minimum_required(VERSION 3.10)

add_subdirectory(HLSL)
add_subdirectory(GLSL)

project(loki)

include_directories(.)

link_libraries(glsl)
link_libraries(hlsl)

add_executable(
	loki
	main.cpp
)

