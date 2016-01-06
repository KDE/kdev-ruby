project(kdev-ruby)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 90)
set(VERSION_PATCH 90)
# KDevplatform dependency version
set( KDEVPLATFORM_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}" )

cmake_minimum_required(VERSION 2.8.12)
find_package (ECM 0.0.9 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

include(GenerateExportHeader)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)

find_package(Qt5 REQUIRED Core Widgets Test)
find_package(KF5 REQUIRED COMPONENTS ThreadWeaver TextEditor I18n ItemModels)
find_package(KDevPlatform ${KDEVPLATFORM_VERSION} REQUIRED)
find_package(BISON REQUIRED)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/libs
)

add_definitions(-DQT_NO_URL_CAST_FROM_STRING)

add_subdirectory(parser)
add_subdirectory(duchain)
add_subdirectory(rails)
add_subdirectory(completion)
add_subdirectory(app_templates)

kdevplatform_add_plugin(kdevrubylanguagesupport JSON kdevrubylanguagesupport.json SOURCES
    highlighting.cpp
    languagesupport.cpp
    launcher.cpp
    parsejob.cpp
    codegen/refactoring.cpp
)

target_link_libraries(kdevrubylanguagesupport
    KF5::I18n
    KF5::TextEditor

    KDev::Language
    KDev::Util

    kdevrubyparser
    kdevrubyduchain
    kdevrubycompletion
    kdevrubyrails
)

install(TARGETS kdevrubylanguagesupport DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES kdevrubysupport.rc DESTINATION ${KXMLGUI_INSTALL_DIR}/kdevrubysupport)
install(FILES documentation/builtins.rb DESTINATION ${DATA_INSTALL_DIR}/kdevrubysupport/documentation/)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

