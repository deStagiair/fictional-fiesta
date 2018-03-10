file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/result")

set(TEST_UTILS_ITF
  ${CMAKE_CURRENT_SOURCE_DIR}/itf/BenchmarkFiles.h
  ${CMAKE_CURRENT_SOURCE_DIR}/itf/CommandLineUtils.h
  ${CMAKE_CURRENT_SOURCE_DIR}/itf/CompareFiles.h
  CACHE INTERNAL "")

set(TEST_UTILS_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/BenchmarkFiles.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/CommandLineUtils.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/CompareFiles.cpp
  CACHE INTERNAL "")

set(TEST_UTILS_TESTS
  ${CMAKE_CURRENT_SOURCE_DIR}/src/CompareFilesTest.cpp
  CACHE INTERNAL "")
