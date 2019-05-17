cmake_minimum_required(VERSION 2.8)
project(Sample LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-std=c++11 -O3")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_PATH    "${PROJECT_BINARY_DIR}/lib")

include_directories(BigInteger)
add_subdirectory(BigInteger)

add_executable(sample SampleDriver.cpp)
target_link_libraries(sample BigInteger)
