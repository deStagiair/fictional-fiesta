find_path(PUGIXML_INCLUDE_DIR NAMES pugixml.hpp)
find_library(PUGIXML_LIBRARIES NAMES pugixml)

message (STATUS "Found pugixml includes: ${PUGIXML_INCLUDE_DIR}")
message (STATUS "Found pugixml libraries: ${PUGIXML_LIBRARIES}")
