cmake_minimum_required (VERSION 3.8)

project ("libdui" CXX)

file(GLOB_RECURSE libdui_file_src *.cpp)
file(GLOB_RECURSE libdui_file_include *.hpp)

include_directories(${d_module})
include_directories(${d_3rdparty}/assimp/include/)

add_library(libdui SHARED
	${libdui_file_src}
	${libdui_file_include}
)
target_link_libraries(libdui libdcore libdrender glfw imgui opengl32 stb_lib glm)