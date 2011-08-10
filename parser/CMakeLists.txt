set(rubyparser_SRCS
    node.c
    parser.c
    rubyparser.cpp
    rubyastvisitor.cpp
)

kde4_add_library(kdev4rubyparser SHARED ${rubyparser_SRCS})
target_link_libraries( kdev4rubyparser
    ${KDE4_KDECORE_LIBS}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDE4_KTEXTEDITOR_LIBS}
)

# Installing the parser executable and its test suite
kde4_add_executable( ruby-parser main.c )
install(DIRECTORY tests tools DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Building the kdev4rubyparser library
target_link_libraries(ruby-parser kdev4rubyparser)
install(TARGETS kdev4rubyparser DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})
