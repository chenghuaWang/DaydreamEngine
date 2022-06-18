cmake_minimum_required (VERSION 3.8)

project ("libdevent" CXX)

file(GLOB_RECURSE libdevent_file_src *.cpp)
file(GLOB_RECURSE libdevent_file_include *.hpp)

include_directories(${d_module})

add_library(libdevent SHARED
	${libdevent_file_src}
	${libdevent_file_include}
)

target_link_libraries(libdevent libdcore)