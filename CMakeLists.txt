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

add_executable(test1 src/test/test1.cpp)
add_executable(test2 src/test/test2.cpp)
add_executable(test3 src/test/test3.cpp)
add_executable(static_class src/oop/StaticClassAsNamespace.cpp)
add_executable(inherit_test src/oop/inherit_test.cpp)
