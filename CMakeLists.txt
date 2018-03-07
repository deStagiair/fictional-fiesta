cmake_minimum_required(VERSION 3.8)

project(fictional-fiesta)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_path(PUGIXML_INCLUDE_DIR NAMES pugixml.hpp)
find_library(PUGIXML_LIBRARIES NAMES pugixml)

add_subdirectory(fictional-fiesta)
add_subdirectory(test)
