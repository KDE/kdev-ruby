
add_subdirectory(tests)

set(rubycompletion_SRCS
    context.cpp
    model.cpp
    worker.cpp
    helpers.cpp

    items/normalitem.cpp
    items/keyworditem.cpp
)

kde4_add_library(kdev4rubycompletion SHARED ${rubycompletion_SRCS})
target_link_libraries( kdev4rubycompletion
    ${KDE4_KDECORE_LIBS}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDE4_KTEXTEDITOR_LIBS}
    kdev4rubyduchain
    kdev4rubyparser
)

install(TARGETS kdev4rubycompletion DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})
