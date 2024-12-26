cmake_minimum_required(VERSION 3.20)

project(seagame)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories("./includes")

aux_source_directory("./src" SRC)

add_executable(seagame
  main.cpp
  ${SRC}
)