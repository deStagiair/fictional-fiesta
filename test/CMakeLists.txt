add_subdirectory(fictional-fiesta)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(tests tests.cpp ${UTILS_TESTS})

target_link_libraries(tests fictional-fiesta)
target_link_libraries(tests pugixml)
target_link_libraries(tests stdc++fs)
