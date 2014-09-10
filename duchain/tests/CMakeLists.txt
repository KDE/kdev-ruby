
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

include(ECMAddTests)

macro(ruby_unit_test testname)
    ecm_add_test(
        ${testname}.cpp duchaintestbase.cpp TEST_NAME ${testname}

        LINK_LIBRARIES

        Qt5::Test

        KDev::Interfaces
        KDev::Tests

        kdevrubyduchain
        kdevrubyparser
    )
endmacro()

ruby_unit_test(benchmarks)
ruby_unit_test(duchain)
ruby_unit_test(uses)
