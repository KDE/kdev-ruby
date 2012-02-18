
bison_target(RUBY_PARSER parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.c)

set(rubyparser_SRCS
    node.c
    ${BISON_RUBY_PARSER_OUTPUTS}
    rubyparser.cpp
    rubyastvisitor.cpp
)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

kde4_add_library(kdev4rubyparser SHARED ${rubyparser_SRCS})
target_link_libraries( kdev4rubyparser
    ${KDE4_KDECORE_LIBS}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDE4_KTEXTEDITOR_LIBS}
)

# Installing the parser executable and its test suite
kde4_add_executable( ruby-parser main.c )
install(DIRECTORY tools DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Building the kdev4rubyparser library
target_link_libraries(ruby-parser kdev4rubyparser)
install(TARGETS kdev4rubyparser DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})
