# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project ("DaydreamEngine")

set(d_module "${PROJECT_SOURCE_DIR}/DaydreamModule/")

# 包含子项目。
add_subdirectory ("DaydreamEngine")
add_subdirectory("DaydreamModule")