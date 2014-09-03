
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(rubynavigation_SRCS
    railsswitchers.cpp
    railsdataprovider.cpp
)

add_library(kdevrubynavigation SHARED ${rubynavigation_SRCS})

target_link_libraries(kdevrubynavigation LINK_PRIVATE
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDEVPLATFORM_PROJECT_LIBRARIES}
    kdevrubyparser
)

install(TARGETS kdevrubynavigation DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})

