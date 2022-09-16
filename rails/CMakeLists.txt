
set(rubyrails_SRCS
    support.cpp
    switchers.cpp
    dataprovider.cpp
    helpers.cpp
    quickopendata.cpp
)

add_library(kdevrubyrails SHARED ${rubyrails_SRCS})

generate_export_header(kdevrubyrails EXPORT_MACRO_NAME KDEVRUBYRAILS_EXPORT
                                     EXPORT_FILE_NAME export.h)

target_link_libraries(kdevrubyrails LINK_PRIVATE
    KDev::Language
    KDev::Project

    kdevrubyparser
)

install(TARGETS kdevrubyrails DESTINATION ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
