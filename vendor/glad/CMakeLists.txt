cmake_minimum_required(VERSION 3.28.0)
project(glad)

add_library(glad ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
