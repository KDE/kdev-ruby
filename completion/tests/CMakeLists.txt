
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${KDEVPLATFORM_INCLUDE_DIR}
)

ecm_add_test(
    completion.cpp
    ../../duchain/tests/duchaintestbase.cpp

    TEST_NAME completion

    LINK_LIBRARIES

    ${QT_QTTEST_LIBRARY}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
    ${KDEVPLATFORM_TESTS_LIBRARIES}
    ${KDEVPLATFORM_UTIL_LIBRARIES}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    kdevrubyduchain
    kdevrubyparser
    kdevrubycompletion
)

