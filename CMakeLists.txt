cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(Raytracing)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/single_include)
file(GLOB SOURCES "src/*.cpp")

add_executable(raytracing ${SOURCES})
# add_executable(settings src/settings.cpp)