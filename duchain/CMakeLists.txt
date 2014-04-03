set(rubyduchain_SRCS
    expressionvisitor.cpp
    editorintegrator.cpp
    rubyducontext.cpp
    helpers.cpp
    loader.cpp

    builders/declarationbuilder.cpp
    builders/usebuilder.cpp
    builders/contextbuilder.cpp
    builders/typebuilder.cpp
    types/classtype.cpp

    navigation/declarationnavigationcontext.cpp
    navigation/navigationwidget.cpp
    navigation/includenavigationcontext.cpp
    declarations/methoddeclaration.cpp
    declarations/variabledeclaration.cpp
    declarations/moduledeclaration.cpp
)

kde4_add_library(kdev4rubyduchain SHARED ${rubyduchain_SRCS})
target_link_libraries( kdev4rubyduchain LINK_PRIVATE
    ${KDE4_KDECORE_LIBS}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDE4_KTEXTEDITOR_LIBS}
    kdev4rubyparser
)

install(TARGETS kdev4rubyduchain DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})

add_subdirectory(tests)
