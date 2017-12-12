cmake_minimum_required(VERSION 3.0)

project(kdev-ruby)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 90)
set(VERSION_PATCH 90)

find_package (ECM "5.14.0" REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

include(GenerateExportHeader)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMQtDeclareLoggingCategory)

set(QT_MIN_VERSION "5.5.0")
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED Core Widgets Test)
set(KF5_DEP_VERSION "5.15.0")
find_package(KF5 ${KF5_DEP_VERSION} REQUIRED COMPONENTS ThreadWeaver TextEditor I18n ItemModels)
set(KDEVPLATFORM_DEP_VERSION "5.2.40")
find_package(KDevPlatform ${KDEVPLATFORM_DEP_VERSION} CONFIG)
set_package_properties(KDevPlatform PROPERTIES
    TYPE REQUIRED
)

find_package(BISON REQUIRED)

# needed for parser/ module prefix with includes for some minimal namespacing
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_definitions(-DQT_NO_URL_CAST_FROM_STRING)

add_subdirectory(parser)
add_subdirectory(duchain)
add_subdirectory(rails)
add_subdirectory(completion)
add_subdirectory(app_templates)

set(ruby_PLUGIN_SRCS
    highlighting.cpp
    languagesupport.cpp
    launcher.cpp
    parsejob.cpp
    codegen/refactoring.cpp
)
ecm_qt_declare_logging_category(ruby_PLUGIN_SRCS
    HEADER debug.h
    IDENTIFIER KDEV_RUBY
    CATEGORY_NAME "kdevelop.languages.ruby"
)
kdevplatform_add_plugin(kdevrubylanguagesupport JSON kdevrubylanguagesupport.json SOURCES ${ruby_PLUGIN_SRCS})

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

install(FILES kdevrubysupport.rc DESTINATION ${KDE_INSTALL_KXMLGUI5DIR}/kdevrubysupport)
install(FILES documentation/builtins.rb DESTINATION ${KDE_INSTALL_DATADIR}/kdevrubysupport/documentation/)

# kdebugsettings file
install(FILES kdevrubysupport.categories DESTINATION ${KDE_INSTALL_CONFDIR})

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

