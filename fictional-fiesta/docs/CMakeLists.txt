set(API_DOCS_BUILD_PATH ${CMAKE_CURRENT_BINARY_DIR})
configure_file(Doxyfile.in Doxyfile @ONLY)

add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
)
