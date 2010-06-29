project(ruby)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ruby_SOURCE_DIR}/cmake/)
enable_testing()

find_package(KDE4 REQUIRED)
find_package(KDevPlatform REQUIRED)

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
add_subdirectory(app_templates)
add_subdirectory(tests)

set(kdevrubylanguagesupport_PART_SRCS
    parsejob.cpp
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
    kdevrubyparser
    kdevrubyduchain
    kdevrubynavigation
)

install(TARGETS kdevrubylanguagesupport DESTINATION ${PLUGIN_INSTALL_DIR})


########### install files ###############

install(FILES kdevrubysupport.desktop DESTINATION ${SERVICES_INSTALL_DIR})
install(FILES kdevrubysupport.rc DESTINATION ${DATA_INSTALL_DIR}/kdevrubysupport)
