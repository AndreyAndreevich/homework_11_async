cmake_minimum_required(VERSION 3.2)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

include_directories(
        ${CMAKE_SOURCE_DIR}/src
        ${Boost_INCLUDE_DIR}
        )

file(GLOB TESTS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(${TEST_NAME} ${TESTS})

set_target_properties(${TEST_NAME} PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK 
        CXX_STANDARD_REQUIRED ON   
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
        )

target_link_libraries(${TEST_NAME}
        ${Boost_LIBRARIES}
        ${MY_BEST_LIB}
        )

add_test(${TEST_NAME} ${TEST_NAME})