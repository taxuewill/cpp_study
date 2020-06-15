# set minimum required version for cmake
cmake_minimum_required(VERSION 2.8)

# define the project name
set(project_name "cpp_studey")

add_compile_options(-std=c++11)

configure_file(config.h.in config.h)

## add debug message
add_definitions("-Wall -g")


LINK_LIBRARIES(pthread)
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    include)
include_directories("/usr/include/eigen3")


find_package( Pangolin )
include_directories( ${Pangolin_INCLUDE_DIRS} )

find_package(Sophus REQUIRED)
include_directories(${Sophus_INCLUDE_DIRS})

add_executable(test1 src/test/test1.cpp)
add_executable(test2 src/test/test2.cpp)
add_executable(test3 src/test/test3.cpp)
#add_executable(signal_test src/test/signal_test.c)
add_executable(sigtest2 src/test/sigtest2.cpp)
add_executable(signal3 src/test/signal3.cpp)
add_executable(signal4 src/test/signal4.cpp)
add_executable(sigset src/test/sigset.cpp)
add_executable(test4 src/test/test4.cpp)
add_executable(test5 src/test/test5.cpp)
add_executable(test6 src/test/test6.cpp)
add_executable(test9 src/test/test9.cpp)

add_executable(fdtest1 src/linux/fdtest.cpp)
add_executable(epolltest src/linux/epoll.cpp)

####### algo programe ##### 
add_executable(algo5 src/algo/algo5.cpp)
target_link_libraries(algo5 ${Pangolin_LIBRARIES} )
add_executable(algo3 src/algo/slam_t3.cpp)
#add_subdirectory(src/slam_test)

###### linux #####
add_executable(domain_server src/linux/domain_socket_server.c)
add_executable(domain_client src/linux/domain_socket_client.c)