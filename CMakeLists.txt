cmake_minimum_required(VERSION 3.21)
message("Using CMake version ${CMAKE_VERSION}")



project(
  sglib
  LANGUAGES CXX
  VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(src)
add_subdirectory(test)


