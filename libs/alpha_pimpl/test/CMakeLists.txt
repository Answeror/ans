file(GLOB_RECURSE HDRS "${CMAKE_SOURCE_DIR}/include/ans/alpha/*.hpp")
acmake_group_source(${HDRS} RELATIVE "${CMAKE_SOURCE_DIR}/include")

file(GLOB_RECURSE FILES *.hpp *.cpp)
acmake_group_source(${FILES})

list(APPEND FILES ${HDRS})

set(OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin/test")
add_executable(test_alpha_pimpl ${FILES})
set_target_properties(test_alpha_pimpl
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}")
acmake_boost_support(test_alpha_pimpl COMPONENTS unit_test_framework)

add_test(test_alpha_pimpl "${OUTPUT_DIRECTORY}/test_alpha_pimpl")
