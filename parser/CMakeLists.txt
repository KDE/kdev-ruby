find_package(KDE4 REQUIRED)
find_package(KDevPlatform REQUIRED)
find_package(KDevelop-PG-Qt QUIET)
find_package(Flex QUIET)

find_program(FLEX_EXECUTABLE
    NAMES flex
    PATHS /usr/bin
    DOC "Flex executable")

set(parser_STAT_SRCS
    parsesession.cpp
)

if(KDEVPGQT_FOUND)
     kdevpgqt_generate(_kdevpgList ruby NAMESPACE ruby DEBUG_VISITOR TOKEN_TEXT
        "${ruby_SOURCE_DIR}/parser/ruby.g"
        "${ruby_SOURCE_DIR}/parser/rubylexer.h"
    )
    set( parser_SRCS
       ${_kdevpgList}
   )
else(KDEVPGQT_FOUND)
   message(STATUS "Assuming existence of generated parser files")
   set(parser_SRCS
       generated/rubyparser.cpp
       generated/rubyvisitor.cpp
       generated/rubydefaultvisitor.cpp )

endif(KDEVPGQT_FOUND)

if(FLEX_EXECUTABLE)
    # Add command to generate the lexer.
    add_custom_command(
        OUTPUT  "${CMAKE_CURRENT_SOURCE_DIR}/generated/rubylexer.cpp"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/ruby.ll"
                "${CMAKE_CURRENT_SOURCE_DIR}/FlexLexer.h"
                "${CMAKE_CURRENT_SOURCE_DIR}/generated/rubyparser.h"
        COMMAND ${FLEX_EXECUTABLE}
        ARGS    --outfile=generated/rubylexer.cpp
                -+
                ruby.ll
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

    set(parser_srcs ${CMAKE_CURRENT_SOURCE_DIR}/generated/rubylexer.cpp ${parser_srcs})

    set_source_files_properties(
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/rubylexer.cpp
        GENERATED
    )
else(FLEX_EXECUTABLE)
    message("--- Assuming existence of the generated lexer file generated/rubylexer.cpp")
    set(parser_srcs ${CMAKE_CURRENT_SOURCE_DIR}/generated/rubylexer.cpp ${parser_srcs})
endif(FLEX_EXECUTABLE)

kde4_add_library( kdev4rubyparser SHARED ${parser_SRCS} ${parser_STAT_SRCS} )
target_link_libraries( kdev4rubyparser
    ${KDE4_KDECORE_LIBS}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDE4_KTEXTEDITOR_LIBS}
)

kde4_add_executable( ruby-parser main.cpp )
target_link_libraries(ruby-parser ${QT_QTCORE_LIBRARY} kdev4rubyparser)

install(TARGETS kdev4rubyparser DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})


add_custom_target( copy-generated
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${ruby_BINARY_DIR}/parser/rubyparser.cpp" "${ruby_SOURCE_DIR}/parser/generated/rubyparser.cpp"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${ruby_BINARY_DIR}/parser/rubyparser.h" "${ruby_SOURCE_DIR}/parser/generated/rubyparser.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${ruby_BINARY_DIR}/parser/rubyast.h" "${ruby_SOURCE_DIR}/parser/generated/rubyast.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${ruby_BINARY_DIR}/parser/rubyvisitor.h" "${ruby_SOURCE_DIR}/parser/generated/rubyvisitor.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${ruby_BINARY_DIR}/parser/rubyvisitor.cpp" "${ruby_SOURCE_DIR}/parser/generated/rubyvisitor.cpp"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${ruby_BINARY_DIR}/parser/rubydefaultvisitor.h" "${ruby_SOURCE_DIR}/parser/generated/rubydefaultvisitor.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${ruby_BINARY_DIR}/parser/rubydefaultvisitor.cpp" "${ruby_SOURCE_DIR}/parser/generated/rubydefaultvisitor.cpp"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${ruby_BINARY_DIR}/parser/rubydebugvisitor.h" "${ruby_SOURCE_DIR}/parser/generated/rubydebugvisitor.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${ruby_BINARY_DIR}/parser/rubytokentext.h" "${ruby_SOURCE_DIR}/parser/generated/rubytokentext.h"
    DEPENDS "${ruby_BINARY_DIR}/parser/rubyparser.cpp"
    DEPENDS "${ruby_BINARY_DIR}/parser/rubyparser.h"
    DEPENDS "${ruby_BINARY_DIR}/parser/rubyvisitor.cpp"
    DEPENDS "${ruby_BINARY_DIR}/parser/rubyvisitor.h"
    DEPENDS "${ruby_BINARY_DIR}/parser/rubydefaultvisitor.cpp"
    DEPENDS "${ruby_BINARY_DIR}/parser/rubydefaultvisitor.h"
    DEPENDS "${ruby_BINARY_DIR}/parser/rubyast.h"
    DEPENDS "${ruby_BINARY_DIR}/parser/rubydebugvisitor.h"
    DEPENDS "${ruby_BINARY_DIR}/parser/rubytokentext.h"
    )
