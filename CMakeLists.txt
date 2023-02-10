cmake_minimum_required(VERSION 3.24)
project(NeuralNet)

set(CMAKE_CXX_STANDARD 23)

# Automatische Header Files
file(GLOB_RECURSE HEADER_FILES
        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        include/*.h
        src/*.h)

# Weitere Header-Dateien
set(HEADER_FILES ${HEADER_FILES})

# Automatische Source Files
file(GLOB_RECURSE SOURCE_FILES
        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        src/*.cpp)

# Weitere Source-Dateien
set(SOURCE_FILES ${SOURCE_FILES})

# Header-Dateien in Include-Ordner
include_directories(include)

# Source-Dateien in Source-Ordner
include_directories(src)

# add source to this project's executable.

add_executable(NeuralNet src/main.cpp ${HEADER_FILES} ${SOURCE_FILES})