add_subdirectory(parser)

include_directories(
    ${KDEVPLATFORM_INCLUDES}
    ${KDE4_INCLUDES}
    ${KDE4_INCLUDE_DIR}/threadweaver
    ${CMAKE_CURRENT_SOURCE_DIR}/parser
    ${CMAKE_CURRENT_BINARY_DIR}/parser
)

link_directories( ${KDE4_LIB_DIR} )
########### next target ###############

set(kdevrubylanguagesupport_PART_SRCS
    rubylanguagesupport.cpp
#    parsejob.cpp
)

kde4_automoc(${kdevrubylanguagesupport_PART_SRCS})
kde4_add_plugin(kdevrubylanguagesupport ${kdevrubylanguagesupport_PART_SRCS})
target_link_libraries(kdevrubylanguagesupport
    ${KDE4_KDEUI_LIBS}
    ${KDEVPLATFORM_INTERFACES_LIBRARY}
    kdevrubyparser
)

install(TARGETS kdevrubylanguagesupport DESTINATION ${PLUGIN_INSTALL_DIR})


########### install files ###############

install(FILES kdevrubysupport.desktop DESTINATION ${SERVICES_INSTALL_DIR})
