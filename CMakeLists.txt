# set minimum required version for cmake
cmake_minimum_required(VERSION 3.0)

# define the project name
project("cpp_studey")

add_compile_options(-std=c++14)

configure_file(config.h.in config.h)

## add debug message
add_definitions("-Wall -g")

find_package (SQLite3 REQUIRED)

find_package(Boost REQUIRED COMPONENTS
        system
        filesystem )

find_library(MQTT_C paho-mqtt3c REQUIRED)
find_library(MQTT_CPP paho-mqttpp3 REQUIRED)

include_directories(${SQLite3_INCLUDE_DIRS})

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()


LINK_LIBRARIES(pthread)
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    include)



#target_link_libraries(exit_test
#        ${SQLite3_LIBRARIES})

## Test Target
add_executable(generic_test test/generic/test.cpp)
add_executable(mqtt_test src/mqtt/mqtt_main.cpp)
add_executable(mqtt_test_sync src/mqtt/mqtt_main_sync.cpp)
add_executable(serial_test
        src/serial/main.cpp
        src/serial/userCrc16.c)

target_link_libraries(mqtt_test ${MQTT_C} ${MQTT_CPP})
target_link_libraries(mqtt_test_sync ${MQTT_C} ${MQTT_CPP})
