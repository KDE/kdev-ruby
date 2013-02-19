project(ruby)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ruby_SOURCE_DIR}/cmake/)

find_package(KDE4 REQUIRED)
find_package(KDevPlatform 1.5.60 REQUIRED)
find_package(BISON REQUIRED)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 5)
set(VERSION_PATCH 60)

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

add_subdirectory(parser)
add_subdirectory(duchain)
add_subdirectory(navigation)
add_subdirectory(completion)
add_subdirectory(app_templates)

set(kdevrubylanguagesupport_PART_SRCS
    rubyparsejob.cpp
    rubyhighlighting.cpp
    rubylanguagesupport.cpp
)

kde4_add_plugin(kdevrubylanguagesupport ${kdevrubylanguagesupport_PART_SRCS})
target_link_libraries(kdevrubylanguagesupport
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
install(FILES kdevrubysupport.desktop DESTINATION ${SERVICES_INSTALL_DIR})
install(FILES kdevrubysupport.rc DESTINATION ${DATA_INSTALL_DIR}/kdevrubysupport)
install(DIRECTORY documentation DESTINATION ${DATA_INSTALL_DIR}/kdevrubysupport)
