cmake_minimum_required(VERSION 3.7)

project(hello_CSCN)

set(CMAKE_CXX_STANDARD 20)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(Threads)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(hello_CSCN main.cpp)
target_link_libraries(hello_CSCN ${Boost_LIBRARIES} Threads::Threads)
