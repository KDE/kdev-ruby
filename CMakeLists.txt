
find_package(KDE4 REQUIRED)
find_package(KDevPlatform REQUIRED)
find_package(KDevelop-PG QUIET)
find_package(Flex QUIET)

include_directories(
    ${KDEVPLATFORM_INCLUDE_DIR}
    ${KDEVPLATFORM_INCLUDE_DIR}/interfaces
    ${KDEVPLATFORM_INCLUDE_DIR}/language
    ${KDEVPLATFORM_INCLUDE_DIR}/language/backgroundparser
    ${KDEVPLATFORM_INCLUDE_DIR}/language/interfaces
    ${KDE4_INCLUDES}
    ${KDE4_INCLUDE_DIR}/threadweaver
    ${CMAKE_CURRENT_SOURCE_DIR}/parser
    ${CMAKE_CURRENT_BINARY_DIR}/parser
    ${CMAKE_CURRENT_BINARY_DIR}
)

set(kdevrubyparser_STAT_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/parser/decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/parser/decoder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/parser/ruby_io.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/parser/ruby_lexer.h
)

# autogenerate the lexer, the parser and the KDevelop codemodel
macro(GET_GENERATED_SRCS _srcsList PLUGIN_SOURCE_DIR PLUGIN_BINARY_DIR)
    if(KDEVPG_FOUND AND FLEX_FOUND)
        include_directories(${KDEVPG_INCLUDE_DIR})
        kdevpg_generate(_kdevpgList ruby DEBUG_VISITOR
  	      "${PLUGIN_SOURCE_DIR}/parser/ruby.g" 
  	      "${PLUGIN_SOURCE_DIR}/parser/ruby_lexer.h")
  
        # Copy ruby_lexer.ll to the builddir, so that flex doesn't write out
        # absolute paths in the generated file when we pass them as arguments.
        # In short, I don't want stuff like
        # '#line 2 "/home/kde/build/.../ruby_lexer.cpp" in SVN.
        add_custom_command(
            OUTPUT  "${PLUGIN_BINARY_DIR}/ruby_lexer.ll"
            MAIN_DEPENDENCY "${PLUGIN_SOURCE_DIR}/parser/ruby_lexer.ll"
            COMMAND ${CMAKE_COMMAND}  ARGS -E copy_if_different
                    "${PLUGIN_SOURCE_DIR}/parser/ruby_lexer.ll"
                    "${PLUGIN_BINARY_DIR}/ruby_lexer.ll"
        )
        # Add command to generate the lexer.
        add_custom_command(
            OUTPUT  "${PLUGIN_BINARY_DIR}/ruby_lexer.cpp"
            MAIN_DEPENDENCY "${PLUGIN_BINARY_DIR}/ruby_lexer.ll"
            DEPENDS "${PLUGIN_BINARY_DIR}/ruby_parser.h"
                    "${PLUGIN_SOURCE_DIR}/parser/ruby_lexer.h"
            COMMAND ${FLEX_EXECUTABLE}
            ARGS    -o"ruby_lexer.cpp"
                    "ruby_lexer.ll"
            WORKING_DIRECTORY ${PLUGIN_BINARY_DIR}
        )
        set(${_srcsList} ${_kdevpgList} "${PLUGIN_BINARY_DIR}/ruby_lexer.cpp")
    else(KDEVPG_FOUND AND FLEX_FOUND)
        include_directories(${PLUGIN_SOURCE_DIR}/parser/generated ${PLUGIN_SOURCE_DIR}/parser/generated/kdevelop-pg)
        message(STATUS "Assuming existence of generated parser files")
        message( STATUS "Assuming existence of generated lexer files")
	set(${_srcsList} 
            ${PLUGIN_SOURCE_DIR}/parser/generated/ruby_parser.cpp
            ${PLUGIN_SOURCE_DIR}/parser/generated/ruby_visitor.cpp
            ${PLUGIN_SOURCE_DIR}/parser/generated/ruby_default_visitor.cpp
            ${PLUGIN_SOURCE_DIR}/parser/generated/ruby_lexer.cpp )

    endif(KDEVPG_FOUND AND FLEX_FOUND)
endmacro(GET_GENERATED_SRCS)

add_subdirectory(tests)

get_generated_srcs(parser_GEN_SRCS ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
set(kdevrubylanguagesupport_PART_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/parser/parsesession.cpp
    simpleparsejob.cpp
    rubylanguagesupport.cpp
    ${kdevrubyparser_STAT_SRCS}
    ${parser_GEN_SRCS}
)

kde4_add_plugin(kdevrubylanguagesupport ${kdevrubylanguagesupport_PART_SRCS})
target_link_libraries(kdevrubylanguagesupport
    ${KDE4_KDEUI_LIBS}
    ${KDE4_KTEXTEDITOR_LIBS}
    ${KDE4_THREADWEAVER_LIBRARIES}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES} ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDEVPLATFORM_EDITOR_LIBRARIES} ${KDEVPLATFORM_PROJECT_LIBRARIES}
)

install(TARGETS kdevrubylanguagesupport DESTINATION ${PLUGIN_INSTALL_DIR})

# generate the command-line parser
add_executable(ruby-parser parser/main.cpp ${parser_GEN_SRCS} ${kdevrubyparser_STAT_SRCS})
target_link_libraries(ruby-parser)
install(TARGETS ruby-parser ${INSTALL_TARGETS_DEFAULT_ARGS})

########### install files ###############

install(FILES kdevrubysupport.desktop DESTINATION ${SERVICES_INSTALL_DIR})

add_custom_target( copy-generated

# 1. copy actions
    # kdev-pg generated files for the ruby parser
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_ast.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser/generated/ruby_ast.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_parser.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser/generated/ruby_parser.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_parser.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser/generated/ruby_parser.cpp"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_visitor.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser/generated/ruby_visitor.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_visitor.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser/generated/ruby_visitor.cpp"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_default_visitor.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser/generated/ruby_default_visitor.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_default_visitor.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser/generated/ruby_default_visitor.cpp"

    # flex parser/generated file
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_lexer.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/parser/generated/ruby_lexer.cpp"

# 2. depend on the files being copied
    # kdev-pg parser/generated files for the ruby parser
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/ruby_ast.h"
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_parser.h"
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_parser.cpp"
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_visitor.h"
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_visitor.cpp"
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_default_visitor.h"
            "${CMAKE_CURRENT_BINARY_DIR}/ruby_default_visitor.cpp"
    # flex parser/generated file
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/ruby_lexer.cpp"
)

