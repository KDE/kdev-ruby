project(kdev-ruby)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 90)
set(VERSION_PATCH 90)
# KDevplatform dependency version
set( KDEVPLATFORM_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}" )

cmake_minimum_required(VERSION 2.8.12)
find_package (ECM 0.0.9 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)

find_package(Qt5 REQUIRED Core Widgets Test)
find_package(KF5 REQUIRED COMPONENTS KDELibs4Support ThreadWeaver TextEditor I18n)
find_package(KDevPlatform ${KDEVPLATFORM_VERSION} REQUIRED)
find_package(BISON REQUIRED)

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/version.h.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/version.h"
  @ONLY
)

include_directories(
    ${KDEVPLATFORM_INCLUDE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/libs
)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

add_subdirectory(parser)
add_subdirectory(duchain)
add_subdirectory(rails)
add_subdirectory(completion)
add_subdirectory(app_templates)

add_library(kdevrubylanguagesupport MODULE
    parsejob.cpp
    highlighting.cpp
    languagesupport.cpp
    codegen/refactoring.cpp
)

target_link_libraries(kdevrubylanguagesupport
    KF5::I18n
    KF5::TextEditor
    KF5::KDELibs4Support

    KDev::Language
    KDev::Util

    kdevrubyparser
    kdevrubyduchain
    kdevrubycompletion
    kdevrubyrails
)

install(TARGETS kdevrubylanguagesupport DESTINATION ${PLUGIN_INSTALL_DIR})
configure_file(kdevrubysupport.desktop.cmake ${CMAKE_CURRENT_BINARY_DIR}/kdevrubysupport.desktop)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/kdevrubysupport.desktop DESTINATION ${SERVICES_INSTALL_DIR})
install(FILES kdevrubysupport.rc DESTINATION ${KXMLGUI_INSTALL_DIR}/kdevrubysupport)
install(FILES documentation/builtins.rb DESTINATION ${DATA_INSTALL_DIR}/kdevrubysupport/documentation/)

