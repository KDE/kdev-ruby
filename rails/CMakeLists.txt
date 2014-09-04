
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(rubynavigation_SRCS
    railsswitchers.cpp
    railsdataprovider.cpp
)

add_library(kdevrubyrails SHARED ${rubynavigation_SRCS})

target_link_libraries(kdevrubyrails LINK_PRIVATE
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDEVPLATFORM_PROJECT_LIBRARIES}
    ${KDEVPLATFORM_UTIL_LIBRARIES}
    kdevrubyparser
)

install(TARGETS kdevrubyrails DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})

add_subdirectory(tests)

