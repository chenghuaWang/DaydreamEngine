cmake_minimum_required (VERSION 3.8)

project ("libdui" CXX)

file(GLOB_RECURSE libdui_file_src *.cpp)
file(GLOB_RECURSE libdui_file_include *.hpp)

message(${libdui_file_src})

include_directories(${d_module})

add_library(libdui SHARED
	${libdui_file_src}
	${libdui_file_include}
)
target_link_libraries(libdui libdcore libdscene libdrender glfw imgui opengl32)