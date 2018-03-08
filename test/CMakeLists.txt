add_subdirectory(fictional-fiesta)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(tests tests.cpp ${UTILS_TESTS})
target_compile_definitions(tests PRIVATE TEST_SOURCE_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(tests fictional-fiesta)
target_link_libraries(tests pugixml)
target_link_libraries(tests stdc++fs)
