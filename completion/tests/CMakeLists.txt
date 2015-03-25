
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
)

ecm_add_test(
    completion.cpp
    ../../duchain/tests/duchaintestbase.cpp

    TEST_NAME completion

    LINK_LIBRARIES

    Qt5::Test

    KDev::Interfaces
    KDev::Tests

    kdevrubyduchain
    kdevrubyparser
    kdevrubycompletion
)

