# Sets Minimum Allowed CMake Version 
cmake_minimum_required(VERSION 3.5)

# Project Name 
project(homework)
set(SOURCE_NAME "OSHomeworkSource")

# Sets Language to C++, Uses C++11
enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)

# Release Build : Compiles Optimized Code
set(CMAKE_BUILD_TYPE Release)

# Adds Compile Warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wredundant-decls -Wcast-align -Wshadow")

# Will Include Files in Current Directory
set(hw_INCDIR ${CMAKE_CURRENT_SOURCE_DIR})
set(src_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_NAME})

include_directories(${src_DIR})
include_directories(${hw_DIR})

enable_testing()

# Add SRC Directory with Professor's Starter Code
add_subdirectory(${SOURCE_NAME})

# Create Library
# TODO : Include your new file here!
add_library(cond_var STATIC
    ${src_SOURCES}
    condition_var.cpp
    )

add_library(semaphore STATIC
    ${src_SOURCES}
    semaphore.cpp
    )

add_library(circular STATIC
    ${src_SOURCES}
    circular.cpp
    )

add_library(hold_and_wait STATIC
    ${src_SOURCES}
    hold_and_wait.cpp
    )


target_link_libraries(cond_var pthread)
target_link_libraries(semaphore pthread)
target_link_libraries(hold_and_wait pthread)
target_link_libraries(circular pthread)

# Add Directory with Professor's Unit Tests
add_subdirectory(${SOURCE_NAME}/tests)

# Subdirectory with Example Programs
add_subdirectory(examples)
