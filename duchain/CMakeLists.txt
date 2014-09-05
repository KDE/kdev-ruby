
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

add_library(kdevrubyduchain SHARED ${rubyduchain_SRCS})

target_link_libraries(kdevrubyduchain LINK_PRIVATE
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDEVPLATFORM_UTIL_LIBRARIES}
    kdevrubyparser
)

install(TARGETS kdevrubyduchain DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})

add_subdirectory(tests)

