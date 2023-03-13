cmake_minimum_required(VERSION 3.25.0)

project(DataStructures)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

file(GLOB SRC_FILES src/*.c)
list(REMOVE_ITEM SRC_FILES ${CMAKE_CURRENT_LIST_DIR}/src/Driver.c)

add_library(DataStructures STATIC ${SRC_FILES})
target_include_directories(DataStructures BEFORE PUBLIC include/)

