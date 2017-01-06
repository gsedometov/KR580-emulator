cmake_minimum_required(VERSION 3.6)
project(Emulator)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c CPU.c CPU.h)
add_executable(Emulator ${SOURCE_FILES})