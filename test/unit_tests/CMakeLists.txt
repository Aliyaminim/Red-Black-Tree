aux_source_directory(./src SRC_LIST)

add_executable(unit_tests ${SRC_LIST})

target_link_libraries(unit_tests
                      PRIVATE ${GTEST_LIBRARIES}
                      PRIVATE ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(unit_tests
                           PRIVATE ${CMAKE_SOURCE_DIR}/include)

gtest_discover_tests(unit_tests)