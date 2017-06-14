add_subdirectory(utils)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${LIBXML2_INCLUDE_DIR})

add_library(fictional-fiesta ${UTILS_SRC})
