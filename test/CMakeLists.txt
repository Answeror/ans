project(test_${PROJECT_NAME})

file(GLOB srcs *.cpp)

set(target ${PROJECT_NAME})

add_executable(${target} ${srcs})

add_test(${target} ${CMAKE_BINARY_DIR}/${target})
