include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

#add_subdirectory(tests)

set(rubycompletion_SRCS
    context.cpp
    model.cpp
    worker.cpp
    helpers.cpp

    items/normalitem.cpp
    items/keyworditem.cpp
    items/requirefileitem.cpp
)

add_library(kdev4rubycompletion SHARED ${rubycompletion_SRCS})
target_link_libraries( kdev4rubycompletion LINK_PRIVATE
    ${KDE4_KDECORE_LIBS}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDEVPLATFORM_PROJECT_LIBRARIES}
    kdev4rubyduchain
    kdev4rubyparser
)

install(TARGETS kdev4rubycompletion DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})
