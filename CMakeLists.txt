# set minimum required version for cmake
cmake_minimum_required(VERSION 2.8)

# define the project name
set(project_name "cpp_studey")

add_compile_options(-std=c++11)

configure_file(config.h.in config.h)

## add debug message
add_definitions("-Wall -g")

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    include)

add_executable(test1 src/test/test1.cpp)
add_executable(test2 src/test/test2.cpp)