add_subdirectory(utils)
add_subdirectory(world)

set(TEST_FICTIONAL_FIESTA
  ${UTILS_TESTS}
  ${WORLD_TESTS}
  CACHE INTERNAL "")
