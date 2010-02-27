set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${KDEVPLATFORM_INCLUDE_DIR}
)

set(duchain_SRCS duchain.cpp)
kde4_add_unit_test(duchain ${duchain_SRCS})
target_link_libraries(duchain kdevrubyduchain ${QT_QTTEST_LIBRARY})
