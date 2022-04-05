cmake_minimum_required(VERSION 3.14)
project(test_calc)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES *.cpp)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${SHARED_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SHARED_LIB_LIBRARIES} GTest::gtest_main)