set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})


include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${KDEVPLATFORM_INCLUDE_DIR}
)

set(completiontest_SRCS
    completion.cpp
    ../../duchain/tests/duchaintestbase.cpp
)

kde4_add_unit_test(completiontest ${completiontest_SRCS})
target_link_libraries(completiontest
    kdev4rubycompletion
    kdev4rubyduchain
    kdev4rubyparser
    ${QT_QTTEST_LIBRARY}
    ${KDEVPLATFORM_TESTS_LIBRARIES}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
)
