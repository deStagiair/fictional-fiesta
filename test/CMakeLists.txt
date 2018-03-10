add_subdirectory(test_utils)
add_subdirectory(fictional-fiesta)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(tests ${TEST_UTILS_SRC} ${TEST_FICTIONAL_FIESTA} ${TEST_UTILS_TESTS} tests.cpp)
target_compile_definitions(tests PRIVATE TEST_SOURCE_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_definitions(tests PRIVATE TEST_BINARY_DIRECTORY="${CMAKE_CURRENT_BINARY_DIR}")

target_link_libraries(tests fictional-fiesta)
target_link_libraries(tests pugixml)
target_link_libraries(tests stdc++fs)
