include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(rubynavigation_SRCS
    railsswitchers.cpp
    railsdataprovider.cpp
)

kde4_add_library(kdevrubynavigation SHARED ${rubynavigation_SRCS})
target_link_libraries( kdevrubynavigation
    ${KDE4_KDECORE_LIBS}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDE4_KTEXTEDITOR_LIBS}
    kdevrubyparser
)

install(TARGETS kdevrubynavigation DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})
