cmake_minimum_required(VERSION 3.4...3.18)
project(pydaydream LANGUAGES CXX)

include_directories(${d_module})

add_subdirectory(pybind11)
pybind11_add_module(pydaydream src/pydaydream.cpp)
target_link_libraries(pydaydream PRIVATE libdui)
# add_library(pydaydream MODULE src/pydaydream.cpp)
# target_link_libraries(pydaydream PUBLIC libdui pybind11::module)
