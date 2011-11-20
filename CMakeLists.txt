cmake_minimum_required(VERSION 2.8)

project(ans)

# output dir

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(include)

INCLUDE_DIRECTORIES($ENV{CML_ROOT})

FILE(TO_CMAKE_PATH $ENV{CODE}/tdm/include TDM_INCLUDE_DIRS)
INCLUDE_DIRECTORIES(${TDM_INCLUDE_DIRS})

FILE(TO_CMAKE_PATH $ENV{CODE}/others/pstade PSTADE_INCLUDE_DIRS)
INCLUDE_DIRECTORIES(${PSTADE_INCLUDE_DIRS})

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

file(TO_CMAKE_PATH $ENV{CODE} ENV_CODE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ENV_CODE}/cmake)

find_package(DynamicAny REQUIRED)
include_directories(${DYNAMIC_ANY_INCLUDE_DIRS})

file(GLOB_RECURSE hdrs include/*.hpp)
file(GLOB_RECURSE srcs src/*.cpp)

set(files ${hdrs} ${srcs})

add_library(ans ${files})

enable_testing()

add_subdirectory(test)
