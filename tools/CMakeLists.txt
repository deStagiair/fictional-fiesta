
find_package(Boost COMPONENTS program_options)

if (Boost_FOUND)

  include_directories(${CMAKE_SOURCE_DIR})
  include_directories(${Boost_INCLUDE_DIRS})

  add_executable(evolve src/evolve.cpp)

  target_link_libraries(evolve fictional-fiesta)
  target_link_libraries(evolve pugixml)
  target_link_libraries(evolve stdc++fs)
  target_link_libraries(evolve ${Boost_LIBRARIES})

endif ()
