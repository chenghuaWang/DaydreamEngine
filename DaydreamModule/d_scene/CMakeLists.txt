cmake_minimum_required (VERSION 3.8)

project ("libdscene" CXX)

file(GLOB_RECURSE libdscene_file_src *.cpp)
file(GLOB_RECURSE libdscene_file_include *.hpp)

include_directories(${d_module})

add_library(libdscene # SHARED
	${libdscene_file_src}
	${libdscene_file_include}
)
target_link_libraries(libdscene libdcore libdrender opengl32)