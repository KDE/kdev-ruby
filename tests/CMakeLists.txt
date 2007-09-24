set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

get_generated_srcs(parser_GEN_SRCS)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
set(RUBY_TEST_LIBRARIES ${QT_QTTEST_LIBRARY} ${KDE4_KDECORE_LIBS})

#### Automated tests ####

# Test some files on disk
set( ruby_fulltestsuite_SRCS ruby_fulltestsuite.cpp ${kdevrubyparser_STAT_SRCS} ${parser_GEN_SRCS} )

kde4_add_unit_test(ruby_fulltestsuite ${ruby_fulltestsuite_SRCS})

target_link_libraries(ruby_fulltestsuite ${RUBY_TEST_LIBRARIES})

