cmake_minimum_required(VERSION 3.0.0)
project(iz2)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0")

add_subdirectory(input_processing)

message("PROCESSING_LIB_INCLUDE_DIRS = ${INPUT_PROCESSING_INCLUDE_DIRS}")
message("PROCESSING_LIB_LIBRARIES = ${INPUT_PROCESSING_LIBRARIES}")

add_executable(${PROJECT_NAME} main.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${INPUT_PROCESSING_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${INPUT_PROCESSING_LIBRARIES})