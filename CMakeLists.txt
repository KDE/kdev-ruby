
#To properly find kdevelop-pg add -DKDEVPG_DATA_DIR=<kdevpg-install-path>/share to the 
#cmake run if you installed it in a different directory than this plugin
#TODO: a cmake run is needed after changing one of the CMakeLists.txt, make will
#complain about the FindKDevelop-PG.cmake file not findable.
if( KDEVPG_DATA_DIR )
    set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${KDEVPG_DATA_DIR}/cmake/modules )
else( KDEVPG_DATA_DIR )
    set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_INSTALL_PREFIX}/share/cmake/modules )
endif( KDEVPG_DATA_DIR )

find_package(KDE4 REQUIRED)
find_package(KDevPlatform REQUIRED)
find_package(KDevelop-PG)

add_subdirectory(parser)
add_subdirectory(tests)

include_directories(
    ${KDEVPLATFORM_INCLUDE_DIR}/interfaces
    ${KDEVPLATFORM_INCLUDE_DIR}/language
    ${KDEVPLATFORM_INCLUDE_DIR}/language/backgroundparser
    ${KDEVPLATFORM_INCLUDE_DIR}/language/interfaces
    ${KDE4_INCLUDES}
    ${KDE4_INCLUDE_DIR}/threadweaver
    ${CMAKE_CURRENT_SOURCE_DIR}/parser
    ${CMAKE_CURRENT_BINARY_DIR}/parser
    ${CMAKE_CURRENT_BINARY_DIR}
)

if(KDEVPG_FOUND)
    include_directories(${KDEVPG_INCLUDE_DIR})
else(KDEVPG_FOUND)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/parser/generated)
endif(KDEVPG_FOUND)


link_directories( ${KDE4_LIB_DIR} )
########### next target ###############

set(kdevrubylanguagesupport_PART_SRCS
    rubylanguagesupport.cpp
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
