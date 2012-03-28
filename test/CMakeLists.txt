project(test_${PROJECT_NAME})

file(GLOB_RECURSE HDRS *.hpp)
file(GLOB_RECURSE SRCS *.cpp)
set(FILES ${SRCS} ${HDRS})

source_group_by_dir(FILES)

set(target ${PROJECT_NAME})

add_executable(${target} ${FILES})
boost_support(${target})

add_test(${target} ${CMAKE_BINARY_DIR}/${target})
