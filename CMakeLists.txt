# set minimum required version for cmake
cmake_minimum_required(VERSION 3.0)

# define the project name
project("cpp_studey")

add_compile_options(-std=c++11)

configure_file(config.h.in config.h)

## add debug message
add_definitions("-Wall -g")


LINK_LIBRARIES(pthread)
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    include)


add_executable(mytest
        src/demo.cpp
        src/utils/timer_task.cpp)