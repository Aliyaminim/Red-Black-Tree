cmake_minimum_required(VERSION 3.13)

project(red-black-tree)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(FATAL_ERROR "In-source build is forbidden")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -O0 -D DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O2 -DNDEBUG")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(GTest REQUIRED)
enable_testing()
add_subdirectory(test)

add_executable(main_rbt ./src/main_rbt.cpp)
target_include_directories(main_rbt PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(main_set ./src/main_set.cpp)
target_include_directories(main_set PUBLIC ${CMAKE_SOURCE_DIR}/include)
#cmake -DCMAKE_BUILD_TYPE=Debug