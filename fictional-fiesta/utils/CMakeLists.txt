set(UTILS_ITF
  ${CMAKE_CURRENT_SOURCE_DIR}/itf/Exception.h
  ${CMAKE_CURRENT_SOURCE_DIR}/itf/XmlDocument.h
  ${CMAKE_CURRENT_SOURCE_DIR}/itf/Pimpl.h
  CACHE INTERNAL "")

set(UTILS_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Exception.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/XmlDocument.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/XmlDocumentImpl.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/XmlDocumentImpl.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/XmlNode.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/XmlNodeImpl.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/XmlNodeImpl.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/PimplImp.h
  CACHE INTERNAL "")
