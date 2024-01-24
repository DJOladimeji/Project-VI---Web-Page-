cmake_minimum_required(VERSION 3.7)

project(ProjectVI)

set(CMAKE_CXX_STANDARD 20)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(Threads)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(ProjectVI main.cpp DB.cpp Tasks.cpp User.cpp)
target_link_libraries(ProjectVI sqlite3 ${Boost_LIBRARIES} Threads::Threads)
