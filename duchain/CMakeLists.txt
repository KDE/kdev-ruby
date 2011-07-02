set(rubyduchain_SRCS
    editorintegrator.cpp
    declarationbuilder.cpp
    usebuilder.cpp
    contextbuilder.cpp
    typebuilder.cpp
    rubyducontext.cpp
    helpers.cpp
    types/objecttype.cpp
    navigation/declarationnavigationcontext.cpp
    navigation/navigationwidget.cpp
    navigation/includenavigationcontext.cpp
)

kde4_add_library(kdev4rubyduchain SHARED ${rubyduchain_SRCS})
target_link_libraries( kdev4rubyduchain
    ${KDE4_KDECORE_LIBS}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDE4_KTEXTEDITOR_LIBS}
    kdev4rubyparser
)

install(TARGETS kdev4rubyduchain DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})

add_subdirectory(navigation)