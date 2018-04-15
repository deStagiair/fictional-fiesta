
find_package(Boost)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(evolve src/evolve.cpp)

target_link_libraries(evolve fictional-fiesta)
target_link_libraries(evolve pugixml)
target_link_libraries(evolve stdc++fs)
