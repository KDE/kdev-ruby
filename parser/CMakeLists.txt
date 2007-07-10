

include_directories( ${QT_INCLUDES} ${KDE4_INCLUDE_DIR} ${KDEVPLATFORM_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} )

########### next target ###############

set(kdevrubyparser_STAT_SRCS
    decoder.cpp
    decoder.h
    ruby_io.cpp
    ruby_lexer.h
    parsesession.cpp
    parsesession.h
)

# autogenerate the lexer, the parser and the KDevelop codemodel

if(KDEVPG_FOUND)
    include_directories(${KDEVPG_INCLUDE_DIR})
    # Add commands to generate the parsers.
    add_custom_command(
        OUTPUT  "${CMAKE_CURRENT_BINARY_DIR}/ruby_ast.h"
                "${CMAKE_CURRENT_BINARY_DIR}/ruby_parser.h"
                "${CMAKE_CURRENT_BINARY_DIR}/ruby_parser.cpp"
                "${CMAKE_CURRENT_BINARY_DIR}/ruby_visitor.h"
                "${CMAKE_CURRENT_BINARY_DIR}/ruby_visitor.cpp"
                "${CMAKE_CURRENT_BINARY_DIR}/ruby_default_visitor.h"
                "${CMAKE_CURRENT_BINARY_DIR}/ruby_default_visitor.cpp"
        MAIN_DEPENDENCY "${CMAKE_CURRENT_SOURCE_DIR}/ruby.g"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/ruby_lexer.h"
        COMMAND ${KDEVPG_EXECUTABLE}
        ARGS     --output=ruby
                 --debug-visitor
                "${CMAKE_CURRENT_SOURCE_DIR}/ruby.g"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
else(KDEVPG_FOUND)
    # If kdev-pg is not available, copy the pre-generated parser files from SVN.
    add_custom_command(
        OUTPUT  "${CMAKE_CURRENT_BINARY_DIR}/ruby_ast.h"
                "${CMAKE_CURRENT_BINARY_DIR}/ruby_parser.h"
                "${CMAKE_CURRENT_BINARY_DIR}/ruby_parser.cpp"
                "${CMAKE_CURRENT_BINARY_DIR}/ruby_visitor.h"
                "${CMAKE_CURRENT_BINARY_DIR}/ruby_visitor.cpp"
                "${CMAKE_CURRENT_BINARY_DIR}/ruby_default_visitor.h"
                "${CMAKE_CURRENT_BINARY_DIR}/ruby_default_visitor.cpp"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/generated/ruby_ast.h"
                "${CMAKE_CURRENT_SOURCE_DIR}/generated/ruby_parser.h"
                "${CMAKE_CURRENT_SOURCE_DIR}/generated/ruby_parser.cpp"
                "${CMAKE_CURRENT_SOURCE_DIR}/generated/ruby_visitor.h"
                "${CMAKE_CURRENT_SOURCE_DIR}/generated/ruby_visitor.cpp"
                "${CMAKE_CURRENT_SOURCE_DIR}/generated/ruby_default_visitor.h"
                "${CMAKE_CURRENT_SOURCE_DIR}/generated/ruby_default_visitor.cpp"
        COMMAND ${CMAKE_COMMAND}  ARGS -E copy_if_different
                "${CMAKE_CURRENT_SOURCE_DIR}/generated/ruby_ast.h"
                "${CMAKE_CURRENT_BINARY_DIR}/ruby_ast.h"
        COMMAND ${CMAKE_COMMAND}  ARGS -E copy_if_different
                "${CMAKE_CURRENT_SOURCE_DIR}/generated/ruby_parser.h"
                "${CMAKE_CURRENT_BINARY_DIR}/ruby_parser.h"
        COMMAND ${CMAKE_COMMAND}  ARGS -E copy_if_different
                "${CMAKE_CURRENT_SOURCE_DIR}/generated/ruby_parser.cpp"
                "${CMAKE_CURRENT_BINARY_DIR}/ruby_parser.cpp"
        COMMAND ${CMAKE_COMMAND}  ARGS -E copy_if_different
                "${CMAKE_CURRENT_SOURCE_DIR}/generated/ruby_visitor.h"
                "${CMAKE_CURRENT_BINARY_DIR}/ruby_visitor.h"
        COMMAND ${CMAKE_COMMAND}  ARGS -E copy_if_different
                "${CMAKE_CURRENT_SOURCE_DIR}/generated/ruby_visitor.cpp"
                "${CMAKE_CURRENT_BINARY_DIR}/ruby_visitor.cpp"
        COMMAND ${CMAKE_COMMAND}  ARGS -E copy_if_different
                "${CMAKE_CURRENT_SOURCE_DIR}/generated/ruby_default_visitor.h"
                "${CMAKE_CURRENT_BINARY_DIR}/ruby_default_visitor.h"
        COMMAND ${CMAKE_COMMAND}  ARGS -E copy_if_different
                "${CMAKE_CURRENT_SOURCE_DIR}/generated/ruby_default_visitor.cpp"
                "${CMAKE_CURRENT_BINARY_DIR}/ruby_default_visitor.cpp"
        COMMENT "kdev-pg is not installed, using the pre-generated parser files from SVN."
    )
endif(KDEVPG_FOUND)

set(kdevrubyparser_STAT_SRCS
    ${kdevrubyparser_STAT_SRCS}
    "${CMAKE_CURRENT_BINARY_DIR}/ruby_ast.h"
    "${CMAKE_CURRENT_BINARY_DIR}/ruby_parser.h"
    "${CMAKE_CURRENT_BINARY_DIR}/ruby_parser.cpp"
    "${CMAKE_CURRENT_BINARY_DIR}/ruby_visitor.h"
    "${CMAKE_CURRENT_BINARY_DIR}/ruby_visitor.cpp"
    "${CMAKE_CURRENT_BINARY_DIR}/ruby_default_visitor.h"
    "${CMAKE_CURRENT_BINARY_DIR}/ruby_default_visitor.cpp"
)
set_source_files_properties(
    "${CMAKE_CURRENT_BINARY_DIR}/ruby_ast.h"
    "${CMAKE_CURRENT_BINARY_DIR}/ruby_parser.h"
    "${CMAKE_CURRENT_BINARY_DIR}/ruby_parser.cpp"
    "${CMAKE_CURRENT_BINARY_DIR}/ruby_visitor.h"
    "${CMAKE_CURRENT_BINARY_DIR}/ruby_visitor.cpp"
    "${CMAKE_CURRENT_BINARY_DIR}/ruby_default_visitor.h"
    "${CMAKE_CURRENT_BINARY_DIR}/ruby_default_visitor.cpp"
    GENERATED
)


if(FLEX_EXECUTABLE)
    # Copy ruby_lexer.ll to the builddir, so that flex doesn't write out
    # absolute paths in the generated file when we pass them as arguments.
    # In short, I don't want stuff like
    # '#line 2 "/home/kde/build/.../ruby_lexer.cpp" in SVN.
    add_custom_command(
        OUTPUT  "${CMAKE_CURRENT_BINARY_DIR}/ruby_lexer.ll"
        MAIN_DEPENDENCY "${CMAKE_CURRENT_SOURCE_DIR}/ruby_lexer.ll"
        COMMAND ${CMAKE_COMMAND}  ARGS -E copy_if_different
                "${CMAKE_CURRENT_SOURCE_DIR}/ruby_lexer.ll"
                "${CMAKE_CURRENT_BINARY_DIR}/ruby_lexer.ll"
    )
    set_source_files_properties(
        "${CMAKE_CURRENT_BINARY_DIR}/ruby_lexer.ll"
        GENERATED
    )
    # Add command to generate the lexer.
    add_custom_command(
        OUTPUT  "${CMAKE_CURRENT_BINARY_DIR}/ruby_lexer.cpp"
        MAIN_DEPENDENCY "${CMAKE_CURRENT_BINARY_DIR}/ruby_lexer.ll"
        DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/ruby_parser.h"
        COMMAND ${FLEX_EXECUTABLE}
        ARGS    -o"ruby_lexer.cpp"
                "ruby_lexer.ll"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
else(FLEX_EXECUTABLE)
    # If flex is not available, copy the pre-generated lexer from SVN.
    add_custom_command(
        OUTPUT  "${CMAKE_CURRENT_BINARY_DIR}/ruby_lexer.cpp"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/generated/ruby_lexer.cpp"
        COMMAND ${CMAKE_COMMAND}  ARGS -E copy_if_different
                "${CMAKE_CURRENT_SOURCE_DIR}/generated/ruby_lexer.cpp"
                "${CMAKE_CURRENT_BINARY_DIR}/ruby_lexer.cpp"
        COMMENT "flex is not installed, using the pre-generated lexer from SVN."
    )
endif(FLEX_EXECUTABLE)

set(kdevrubyparser_STAT_SRCS
    ${kdevrubyparser_STAT_SRCS}
    "${CMAKE_CURRENT_BINARY_DIR}/ruby_lexer.cpp"
)
set_source_files_properties(
    "${CMAKE_CURRENT_BINARY_DIR}/ruby_lexer.cpp"
    GENERATED
)

set(kdevrubyparser_STAT_SRCS
    ${kdevrubyparser_STAT_SRCS}
)


kde4_add_library(kdevrubyparser SHARED ${kdevrubyparser_STAT_SRCS})
target_link_libraries(kdevrubyparser ${QT_QTCORE_LIBRARY})
install(TARGETS kdevrubyparser DESTINATION ${LIB_INSTALL_DIR})

# generate the command-line parser
add_executable(ruby-parser main.cpp)
target_link_libraries(ruby-parser kdevrubyparser)
install(TARGETS ruby-parser DESTINATION ${BIN_INSTALL_DIR})


add_custom_target( copy-generated

# 1. copy actions
    # kdev-pg generated files for the ruby parser
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_ast.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/generated/ruby_ast.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_parser.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/generated/ruby_parser.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_parser.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/generated/ruby_parser.cpp"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_visitor.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/generated/ruby_visitor.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_visitor.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/generated/ruby_visitor.cpp"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_default_visitor.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/generated/ruby_default_visitor.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_default_visitor.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/generated/ruby_default_visitor.cpp"

    # flex generated file
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_lexer.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/generated/ruby_lexer.cpp"

# 2. depend on the files being copied
    # kdev-pg generated files for the ruby parser
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/ruby_ast.h"
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_parser.h"
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_parser.cpp"
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_visitor.h"
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_visitor.cpp"
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_default_visitor.h"
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_default_visitor.cpp"
    # flex generated file
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/ruby_lexer.cpp"
)
