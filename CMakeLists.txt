cmake_minimum_required(VERSION 3.15)

project(fourier)

# Build options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

# Put default build target
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "RELEASE as default build target")
    set(CMAKE_BUILD_TYPE "RELEASE")
endif()

add_subdirectory(submodules)

include_directories(
    src
    src/utils
)

# Default compilation flags
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra -Wno-deprecated-declarations -Wno-unused-parameter -Wno-sign-compare -Wno-missing-field-initializers")

# Debug compilation flags
set(CMAKE_CXX_FLAGS_DEBUG "-fsanitize=address -g3 -O0 -DDEBUG")

# Release compilation flags
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -DRELEASE")

# Exec
add_executable(fourier)
target_sources(fourier PRIVATE "src/main.cpp")
target_link_libraries(fourier PRIVATE STATIC_LIBRARIES)
