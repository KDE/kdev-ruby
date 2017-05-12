
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
ecm_qt_declare_logging_category(rubyduchain_SRCS
    HEADER duchaindebug.h
    IDENTIFIER DUCHAIN
    CATEGORY_NAME "kdevelop.languages.ruby.duchain"
)

add_library(kdevrubyduchain SHARED ${rubyduchain_SRCS})

generate_export_header(kdevrubyduchain EXPORT_MACRO_NAME KDEVRUBYDUCHAIN_EXPORT
                                       EXPORT_FILE_NAME duchainexport.h)

target_link_libraries(kdevrubyduchain LINK_PRIVATE
    KDev::Language
    KDev::Util

    kdevrubyparser
)

install(TARGETS kdevrubyduchain DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})

add_subdirectory(tests)

