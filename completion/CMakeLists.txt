
set(rubycompletion_SRCS
    context.cpp
    model.cpp
    worker.cpp
    keyworditem.cpp
    helpers.cpp
)

kde4_add_library(kdev4rubycompletion SHARED ${rubycompletion_SRCS})
target_link_libraries( kdev4rubycompletion
    ${KDE4_KDECORE_LIBS}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDE4_KTEXTEDITOR_LIBS}
)

install(TARGETS kdev4rubycompletion DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})
