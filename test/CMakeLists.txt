project(Testing)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/include)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_subdirectory(e2e)

add_executable(test1 test1.cpp)
target_link_libraries(test1 gtest gtest_main Threads::Threads)