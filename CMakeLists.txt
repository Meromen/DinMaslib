cmake_minimum_required(VERSION 3.7)
project(DinamicLib)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES linear_sequence.c linear_sequence.h)
add_library(DinamicLib ${SOURCE_FILES})