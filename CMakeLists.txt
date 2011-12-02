cmake_minimum_required(VERSION 2.8.5)

project(ans)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/misc/cmake)
include(config)

include_directories(include)

INCLUDE_DIRECTORIES($ENV{CML_ROOT})

FILE(TO_CMAKE_PATH $ENV{CODE}/tdm/include TDM_INCLUDE_DIRS)
INCLUDE_DIRECTORIES(${TDM_INCLUDE_DIRS})

FILE(TO_CMAKE_PATH $ENV{CODE}/others/pstade PSTADE_INCLUDE_DIRS)
INCLUDE_DIRECTORIES(${PSTADE_INCLUDE_DIRS})

find_package(DynamicAny REQUIRED)
include_directories(${DYNAMIC_ANY_INCLUDE_DIRS})

file(GLOB_RECURSE hdrs include/*.hpp)
file(GLOB_RECURSE srcs src/*.cpp)

set(files ${hdrs} ${srcs})
source_group_by_dir(files)

add_library(ans ${files})
boost_support(ans)

enable_testing()

add_subdirectory(test)
