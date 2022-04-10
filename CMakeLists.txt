# set minimum required version for cmake
cmake_minimum_required(VERSION 3.0)

# define the project name
project("cpp_studey")

add_compile_options(-std=c++14)

configure_file(config.h.in config.h)

## add debug message
add_definitions("-Wall -g")

find_package(PkgConfig)

pkg_check_modules(PC_ZeroMQ QUIET libzmq)

find_path(ZeroMQ_INCLUDE_DIR
        NAMES zmq.h
        PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
        )

find_library(ZeroMQ_LIBRARY
        NAMES zmq
        PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
        )

include_directories(${ZeroMQ_INCLUDE_DIR})

find_package(Protobuf REQUIRED)
if(PROTOBUF_FOUND)
    message(STATUS "protobuf library found")
else()
    message(FATAL_ERROR "protobuf library is needed but cant be found")
endif()


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
add_executable(concurrent src/concurrent/main.cpp)

target_link_libraries(mqtt_test ${MQTT_C} ${MQTT_CPP})
target_link_libraries(mqtt_test_sync ${MQTT_C} ${MQTT_CPP})

add_executable(zclient src/zmq/zclient.cpp)
target_link_libraries(zclient PUBLIC
        ${ZeroMQ_LIBRARY}
        ${PROTOBUF_LIBRARIES})


add_executable(zserver src/zmq/zserver.cpp)
target_link_libraries(zserver PUBLIC
        ${ZeroMQ_LIBRARY}
        ${PROTOBUF_LIBRARIES})

