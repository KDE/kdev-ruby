set(rubyduchain_SRCS
    editorintegrator.cpp
    declarationbuilder.cpp
    contextbuilder.cpp
    typebuilder.cpp
)

kde4_add_library(kdevrubyduchain SHARED ${rubyduchain_SRCS})
target_link_libraries( kdevrubyduchain
    ${KDE4_KDECORE_LIBS}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDE4_KTEXTEDITOR_LIBS}
    kdevrubyparser
)

install(TARGETS kdevrubyduchain DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})
