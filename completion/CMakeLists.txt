
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(tests)

set(rubycompletion_SRCS
    context.cpp
    model.cpp
    worker.cpp
    helpers.cpp

    items/normalitem.cpp
    items/keyworditem.cpp
    items/requirefileitem.cpp
)

add_library(kdevrubycompletion SHARED ${rubycompletion_SRCS})

target_link_libraries(kdevrubycompletion LINK_PRIVATE
    KDev::Interfaces
    KDev::Language
    KDev::Util

    kdevrubyduchain
    kdevrubyparser
)

install(TARGETS kdevrubycompletion DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})
