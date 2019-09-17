# set minimum required version for cmake
cmake_minimum_required(VERSION 2.8)

# define the project name
set(project_name "cpp_studey")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(test1 src/test/test1.cpp)