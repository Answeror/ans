cmake_minimum_required(VERSION 2.8.5)

project(ans)

list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_SOURCE_DIR}/misc/cmake")
include(ans_3rd_config)

include_directories("${CMAKE_SOURCE_DIR}/include")

enable_testing()

add_subdirectory(libs)
