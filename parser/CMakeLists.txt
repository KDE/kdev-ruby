
bison_target(RUBY_PARSER parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser_gen.c)

set(rubyparser_SRCS
    node.c
    ${BISON_RUBY_PARSER_OUTPUTS}
    parser.cpp
    astvisitor.cpp
    ast.cpp
)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(kdevrubyparser SHARED ${rubyparser_SRCS})

target_link_libraries(kdevrubyparser LINK_PRIVATE
    KDev::Language
)

# Compile & install the tests if needed.
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_definitions(-DBUILD_TESTS)
    add_executable(ruby-parser main.c)
    install(DIRECTORY tools DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    target_link_libraries(ruby-parser kdevrubyparser)
endif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")

install(TARGETS kdevrubyparser DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})

