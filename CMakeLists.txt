project(ruby)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 6)
set(VERSION_PATCH 60)
# KDevplatform dependency version
set( KDEVPLATFORM_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}" )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ruby_SOURCE_DIR}/cmake/)

cmake_minimum_required(VERSION 2.8.9)

find_package(KDE4 REQUIRED)
find_package(KDevPlatform ${KDEVPLATFORM_VERSION} REQUIRED)
find_package(BISON REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/version.h.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/version.h"
  @ONLY
)

enable_testing()

include_directories(
    ${KDEVPLATFORM_INCLUDE_DIR}
    ${KDE4_INCLUDES}
    ${KDE4_INCLUDE_DIR}/threadweaver
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

add_subdirectory(parser)
add_subdirectory(duchain)
add_subdirectory(navigation)
add_subdirectory(completion)
add_subdirectory(app_templates)

set(kdevrubylanguagesupport_PART_SRCS
    rubyparsejob.cpp
    rubyhighlighting.cpp
    rubylanguagesupport.cpp

    codegen/refactoring.cpp
)

kde4_add_plugin(kdevrubylanguagesupport ${kdevrubylanguagesupport_PART_SRCS})
target_link_libraries(kdevrubylanguagesupport LINK_PRIVATE
    ${KDE4_KDEUI_LIBS}
    ${KDE4_KTEXTEDITOR_LIBS}
    ${KDE4_THREADWEAVER_LIBRARIES}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDEVPLATFORM_PROJECT_LIBRARIES}
    kdev4rubyparser
    kdev4rubyduchain
    kdev4rubynavigation
    kdev4rubycompletion
)

install(TARGETS kdevrubylanguagesupport DESTINATION ${PLUGIN_INSTALL_DIR})

configure_file(kdevrubysupport.desktop.cmake ${CMAKE_CURRENT_BINARY_DIR}/kdevrubysupport.desktop)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/kdevrubysupport.desktop DESTINATION ${SERVICES_INSTALL_DIR})
install(FILES kdevrubysupport.rc DESTINATION ${DATA_INSTALL_DIR}/kdevrubysupport)
install(FILES documentation/builtins.rb DESTINATION ${DATA_INSTALL_DIR}/kdevrubysupport/documentation/)
