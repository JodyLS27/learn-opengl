# Project level CMake

cmake_minimum_required(VERSION 3.20)
Project(fluid_solver VERSION 0.0.1)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(editor)
add_subdirectory(engine)
