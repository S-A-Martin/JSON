cmake_minimum_required(VERSION 3.2)
project(JSON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tst)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/googletest/)
