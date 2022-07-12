# author:	chenghua.wang
# time:		2022-06-10
# cmake script for d_core module.

# Note: This lib will be compiled to static lib by default.

# This module will use the pre-compiled head. The
# pre-compiled head is include and made in the top
# level CMakeLists.txt
cmake_minimum_required (VERSION 3.8)

project ("libdcore" CXX)

file(GLOB_RECURSE libcore_file_src src/*.cpp)
file(GLOB_RECURSE libcore_file_include include/*.hpp)

include_directories(${d_module}/d_core/include)

add_library(libdcore 
	${libcore_file_src}
	${libcore_file_include}
)
target_link_libraries(libdcore spdlog glad glfw)
target_precompile_headers(libdcore PRIVATE pch.hpp)
