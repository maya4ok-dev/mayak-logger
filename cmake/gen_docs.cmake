find_package(Doxygen)

if(Doxygen_FOUND)

    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in
        ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        @ONLY
    )

    doxygen_add_docs(
        docs
        USE_STAMP_FILE
        CONFIG_FILE ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        COMMENT "Generating documentation"
        ALL
    )

endif()
