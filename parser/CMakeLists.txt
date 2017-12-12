
bison_target(RUBY_PARSER parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser_gen.c)

set(rubyparser_SRCS
    node.c
    ${BISON_RUBY_PARSER_OUTPUTS}
    parser.cpp
    astvisitor.cpp
    ast.cpp
)
ecm_qt_declare_logging_category(rubyparser_SRCS
    HEADER parserdebug.h
    IDENTIFIER PARSER
    CATEGORY_NAME "kdevelop.languages.ruby.parser"
)

add_library(kdevrubyparser SHARED ${rubyparser_SRCS})

generate_export_header(kdevrubyparser EXPORT_MACRO_NAME KDEVRUBYPARSER_EXPORT
                                      EXPORT_FILE_NAME export.h)

target_link_libraries(kdevrubyparser LINK_PRIVATE
    KDev::Language
)

# Compile & install the tests if needed.
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DBUILD_TESTS)
    add_executable(ruby-parser main.c)
    set_target_properties(ruby-parser PROPERTIES WIN32_EXECUTABLE 0)
    install(DIRECTORY tools DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    target_link_libraries(ruby-parser kdevrubyparser)
endif()

install(TARGETS kdevrubyparser DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})

