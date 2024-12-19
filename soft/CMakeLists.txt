cmake_minimum_required(VERSION 3.30)
project(soft)

set(CMAKE_CXX_STANDARD 20)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(soft main.cpp
        pages/main/mainpg.h
        pages/main/mainpg.cpp)
target_link_libraries(soft ${CURSES_LIBRARIES})
