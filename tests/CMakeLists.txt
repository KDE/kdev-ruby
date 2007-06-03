if(KDE4_BUILD_TESTS)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

include_directories( ${CMAKE_CURRENT_BINARY_DIR}/../parser/ ${CMAKE_CURRENT_SOURCE_DIR}/../parser/ )
link_directories( ${CMAKE_CURRENT_BINARY_DIR}/../parser/ )

set(RUBY_TEST_LIBRARIES ${QT_QTTEST_LIBRARY} ${KDE4_KDECORE_LIBS} kdevrubyparser)

add_definitions(-DRUBY_TESTDIR="\\"${CMAKE_CURRENT_SOURCE_DIR}/\\"")

#### Automated tests ####

# Test some files on disk
set( ruby_fulltestsuite_SRCS ruby_fulltestsuite.cpp )

kde4_automoc(${ruby_fulltestsuite_SRCS} )

kde4_add_executable(ruby_fulltestsuite NOGUI RUN_UNINSTALLED ${ruby_fulltestsuite_SRCS})

target_link_libraries(ruby_fulltestsuite ${RUBY_TEST_LIBRARIES})

add_test(ruby_fulltestsuite ${EXECUTABLE_OUTPUT_PATH}/ruby_fulltestsuite)

endif(KDE4_BUILD_TESTS)
