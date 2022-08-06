cmake_minimum_required (VERSION 3.8)

project ("libdrender" CXX)

file(GLOB_RECURSE libdrender_file_src *.cpp)
file(GLOB_RECURSE libdrender_file_include *.hpp)

include_directories(${d_module})

add_library(libdrender SHARED
	${libdrender_file_src}
	${libdrender_file_include}
)
target_link_libraries(libdrender libdcore glm opengl32 glad stb_lib)