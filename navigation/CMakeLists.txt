include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(rubynavigation_SRCS
    railsswitchers.cpp
    railsdataprovider.cpp
)

add_library(kdev4rubynavigation SHARED ${rubynavigation_SRCS})
target_link_libraries( kdev4rubynavigation LINK_PRIVATE
    ${KDE4_KDECORE_LIBS}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDEVPLATFORM_UTIL_LIBRARIES}
    ${KDEVPLATFORM_PROJECT_LIBRARIES}
    kdev4rubyparser
)

install(TARGETS kdev4rubynavigation DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})
