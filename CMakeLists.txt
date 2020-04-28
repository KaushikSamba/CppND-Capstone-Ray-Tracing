cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(Raytracing)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external)
file(GLOB SOURCES "src/*.cpp")

# find_package(spdlog)

add_executable(raytracing ${SOURCES})
# add_executable(settings src/settings.cpp)
# target_link_libraries(raytracing PRIVATE spdlog::spdlog)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})
target_link_libraries(raytracing ${PNG_LIBRARY})