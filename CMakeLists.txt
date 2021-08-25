cmake_minimum_required(VERSION 3.16)
project(GameKenoBet)

set(CMAKE_CXX_STANDARD 11)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall")

add_executable(GameKenoBet main.cpp src/KenoBet.cpp include/KenoBet.h src/Functions.cpp include/Functions.h)