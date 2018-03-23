set(WORLD_ITF
  ${CMAKE_CURRENT_SOURCE_DIR}/itf/ConstantSource.h
  ${CMAKE_CURRENT_SOURCE_DIR}/itf/FSM.h
  ${CMAKE_CURRENT_SOURCE_DIR}/itf/Individual.h
  ${CMAKE_CURRENT_SOURCE_DIR}/itf/Location.h
  ${CMAKE_CURRENT_SOURCE_DIR}/itf/Source.h
  ${CMAKE_CURRENT_SOURCE_DIR}/itf/SourceFactory.h
  CACHE INTERNAL "")

set(WORLD_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/ConstantSource.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/FSM.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Individual.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Location.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Source.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/SourceFactory.cpp
  CACHE INTERNAL "")
