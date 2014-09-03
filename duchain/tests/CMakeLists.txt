
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

include(ECMAddTests)

macro(ruby_unit_test testname)
    ecm_add_test(
        ${testname}.cpp duchaintestbase.cpp TEST_NAME ${testname}

        LINK_LIBRARIES

        ${QT_QTTEST_LIBRARY}
        ${KDEVPLATFORM_INTERFACES_LIBRARIES}
        ${KDEVPLATFORM_TESTS_LIBRARIES}
        ${KDEVPLATFORM_UTIL_LIBRARIES}
        ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
        kdevrubyduchain
        kdevrubyparser
    )
endmacro()

ruby_unit_test(benchmarks)
ruby_unit_test(duchain)
ruby_unit_test(uses)
