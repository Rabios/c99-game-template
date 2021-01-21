cmake_minimum_required(VERSION 3.1)
project(glad LANGUAGES C)
set(CMAKE_C_STANDARD 99)

add_library(glad STATIC)
target_sources(glad
    PRIVATE
   "${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c"
   "${CMAKE_CURRENT_SOURCE_DIR}/include/glad/glad.h"
   "${CMAKE_CURRENT_SOURCE_DIR}/include/KHR/khrplatform.h"
)
target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
