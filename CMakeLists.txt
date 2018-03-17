cmake_minimum_required(VERSION 3.8)

project(fictional-fiesta)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif ()

find_package(Doxygen REQUIRED dot OPTIONAL_COMPONENTS mscgen dia)
find_package(PugiXML REQUIRED)

find_program(CPP_CHECK_EXE cppcheck)
find_program(VERA_EXE vera++)

add_subdirectory(fictional-fiesta)
add_subdirectory(test)
