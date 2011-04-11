set(rubyparser_SRCS
    node.c
    parser.c
)

kde4_add_library(kdevrubyparser SHARED ${rubyparser_SRCS})
target_link_libraries( kdevrubyparser
    ${KDE4_KDECORE_LIBS}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDE4_KTEXTEDITOR_LIBS}
)

kde4_add_executable( ruby-parser main.c )
target_link_libraries(ruby-parser kdevrubyparser)
install(TARGETS kdevrubyparser DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})
