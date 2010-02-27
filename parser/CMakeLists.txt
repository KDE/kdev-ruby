set(rubyparser_SRCS
    rubyast.cpp
    parser.cpp
    visitor.cpp
)

kde4_add_library(kdevrubyparser SHARED ${rubyparser_SRCS})
target_link_libraries( kdevrubyparser
    ${KDE4_KDECORE_LIBS}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDE4_KTEXTEDITOR_LIBS}
)

install(TARGETS kdevrubyparser DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})
