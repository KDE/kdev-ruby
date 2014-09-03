
bison_target(RUBY_PARSER parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.c)

set(rubyparser_SRCS
    node.c
    ${BISON_RUBY_PARSER_OUTPUTS}
    rubyparser.cpp
    rubyastvisitor.cpp
)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(kdev4rubyparser SHARED ${rubyparser_SRCS})

target_link_libraries( kdev4rubyparser LINK_PRIVATE
    ${QT_QTCORE_LIBRARY}
    KF5::I18n
)
target_link_libraries( kdev4rubyparser LINK_PUBLIC
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDEVPLATFORM_UTIL_LIBRARIES}
    ${KDEVPLATFORM_PROJECT_LIBRARIES}
)

# Compile & install the tests if needed.
if((${KDE4_BUILD_TESTS} STREQUAL "ON") OR (${CMAKE_BUILD_TYPE} STREQUAL "Debug"))
    add_definitions(-DBUILD_TESTS)
    add_executable( ruby-parser main.c )
    install(DIRECTORY tools DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    target_link_libraries(ruby-parser kdev4rubyparser)
endif((${KDE4_BUILD_TESTS} STREQUAL "ON") OR (${CMAKE_BUILD_TYPE} STREQUAL "Debug"))

install(TARGETS kdev4rubyparser DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})
