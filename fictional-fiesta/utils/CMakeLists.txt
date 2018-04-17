set(UTILS_ITF
  ${CMAKE_CURRENT_SOURCE_DIR}/itf/Descriptable.h
  ${CMAKE_CURRENT_SOURCE_DIR}/itf/Exception.h
  ${CMAKE_CURRENT_SOURCE_DIR}/itf/Xmlable.h
  ${CMAKE_CURRENT_SOURCE_DIR}/itf/XmlDocument.h
  ${CMAKE_CURRENT_SOURCE_DIR}/itf/XmlNode.h
  ${CMAKE_CURRENT_SOURCE_DIR}/itf/Pimpl.h
  CACHE INTERNAL "")

set(UTILS_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Descriptable.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Exception.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/PimplImpl.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Xmlable.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/XmlDocument.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/XmlNode.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/XmlNodeImpl.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/XmlNodeImpl.h
  CACHE INTERNAL "")
