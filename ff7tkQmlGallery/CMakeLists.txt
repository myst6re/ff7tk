project(ff7tkQmlGallery VERSION 0.1.1 LANGUAGES CXX DESCRIPTION "Demo App for ff7tk using QML")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Quick QuickControls2 QmlImportScanner)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED NO_MODULE COMPONENTS
        Quick
        QuickControls2
)

if(APPLE)
    set(PLATFORM_EX_SRC ${CMAKE_CURRENT_SOURCE_DIR}/ff7tkQmlGallery.icns)
    set_source_files_properties(${PLATFORM_EX_SRC} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
elseif(WIN32)
    set(PLATFORM_EX_SRC ff7tkQmlGallery.rc)
endif()

add_executable(ff7tkQmlGallery WIN32 MACOSX_BUNDLE
        main.cpp
        qml.qrc
        ${PLATFORM_EX_SRC}
)

add_dependencies(ff7tkQmlGallery ff7tk)

target_include_directories(ff7tkQmlGallery
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/src/data>
)

target_link_libraries ( ff7tkQmlGallery PUBLIC
        Qt::Quick
        Qt::QuickControls2
        ff7tk::ff7tk
)

if(APPLE)
    set_target_properties(ff7tkQmlGallery PROPERTIES
        INSTALL_RPATH "@executable_path/../Frameworks @executable_path @loader_path @loader_path/../Frameworks"
        BUILD_WITH_INSTALL_RPATH TRUE
        MACOSX_BUNDLE_GUI_IDENTIFIER "org.ff7tk.QmlGallery"
        MACOSX_BUNDLE_DISPLAY_NAME "ff7tkQmlGallery"
        MACOSX_BUNDLE_BUNDLE_NAME "ff7tkQmlGallery"
        MACOSX_BUNDLE_DISPLAY_NAME "ff7tkQmlGallery"
        MACOSX_BUNDLE_INFO_STRING "ff7tk - QmlGallery"
        MACOSX_BUNDLE_COPYRIGHT "2012-2020 ff7tk Authors"
        MAXOSX_BUNDLE_ICON_FILE ff7tkQmlGallery.icns
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    )

    add_custom_command(TARGET ff7tkQmlGallery POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ff7tk> $<TARGET_BUNDLE_CONTENT_DIR:ff7tkQmlGallery>/MacOS/
        COMMAND macdeployqt ${CMAKE_CURRENT_BINARY_DIR}/\${CONFIGURATION}/ff7tkQmlGallery.app
#        COMMAND install_name_tool -change @rpath/libff7tk.0.dylib @executable_path/libff7tk.0.dylib $<TARGET_FILE:ff7tkQmlGallery>
    )

elseif(UNIX AND NOT APPLE)
    set_target_properties(ff7tkQmlGallery PROPERTIES
        INSTALL_RPATH "\$ORIGIN/../lib"
    )
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ff7tkQmlGallery.desktop" DESTINATION share/applications/ COMPONENT ff7tkQmlGallery_RUNTIME)
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ff7tkQmlGallery.png" DESTINATION share/pixmaps COMPONENT ff7tkQmlGallery_RUNTIME)
endif()

install(TARGETS ff7tkQmlGallery
    BUNDLE DESTINATION ${CMAKE_INSTALL_BINDIR}
     COMPONENT ff7tkQmlGallery_RUNTIME
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
     COMPONENT ff7tkQmlGallery_RUNTIME
)

#if(APPLE)
#    get_target_property(QtCore_location Qt5::Core LOCATION)
#    install(
#      CODE [[
#        include(BundleUtilities)
#        set(DIRS ${QtCore_location} ${CMAKE_BINARY_DIR}/src/data )
#        fixup_bundle("${CMAKE_INSTALL_PREFIX}/bin/ff7tkQmlGallery.app" "" "${QT_LIBRARY_DIRS} ${CMAKE_BINARY_DIR}/src/data")
#      ]]
#      COMPONENT ff7tkQmlGallery_RUNTIME
#    )
#endif()
