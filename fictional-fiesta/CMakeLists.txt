add_subdirectory(utils)
add_subdirectory(world)

set(SOURCE_CODE_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

if (${DOXYGEN_FOUND})
  add_subdirectory(docs)
endif ()

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${LIBXML2_INCLUDE_DIR})

set(FICTIONAL_FIESTA_ALL_SRC
  ${UTILS_SRC}
  ${WORLD_SRC}
)

set(FICTIONAL_FIESTA_ALL_ITF
  ${UTILS_ITF}
  ${WORLD_ITF}
)

set(FICTIONAL_FIESTA_ALL_CODE
  ${FICTIONAL_FIESTA_ALL_SRC}
  ${FICTIONAL_FIESTA_ALL_ITF}
)

add_library(fictional-fiesta ${FICTIONAL_FIESTA_ALL_SRC})

if (CPP_CHECK_EXE)
  set(CPP_CHECK_FLAGS "--template=gcc --enable=warning,information,style,performance")
  add_custom_target(check ${CPP_CHECK_EXE} --language=c++ ${CPP_CHECK_FLAGS} ${CMAKE_CURRENT_SOURCE_DIR})
else ()
  message(STATUS "Cppcheck not found target 'check' not available")
endif ()

if (VERA_EXE)
  set(VERA_FLAGS --profile "../../../..${CMAKE_CURRENT_SOURCE_DIR}/vera.profile")
  add_custom_target(style ${VERA_EXE} ${VERA_FLAGS} ${FICTIONAL_FIESTA_ALL_CODE} )
else ()
  message(STATUS "vera++ not found target 'style' not available")
endif ()
