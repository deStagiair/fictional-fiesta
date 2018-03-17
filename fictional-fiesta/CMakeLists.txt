add_subdirectory(utils)

set(SOURCE_CODE_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

if (${DOXYGEN_FOUND})
  add_subdirectory(docs)
endif ()

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${LIBXML2_INCLUDE_DIR})

add_library(fictional-fiesta ${UTILS_SRC})

if (CPP_CHECK_EXE)
  set(CPP_CHECK_FLAGS "--template=gcc --enable=warning,information,style,performance")
  add_custom_target(check ${CPP_CHECK_EXE} cppcheck --language=c++ ${CPP_CHECK_FLAGS} ${CMAKE_CURRENT_SOURCE_DIR})
else ()
  message(STATUS "Cppcheck not found target 'check' not available")
endif ()
