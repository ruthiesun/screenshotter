set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h

        collectionviewer.h collectionviewer.cpp
        screenshoteditor.h screenshoteditor.cpp
        collectionmodel.h collectionmodel.cpp
        treeviewdelegate.h treeviewdelegate.cpp
        canvas.h canvas.cpp
        canvasviewer.h canvasviewer.cpp
        camera.h camera.cpp
        paletteretriever.h paletteretriever.cpp
        colourselector.h colourselector.cpp
        saver.h saver.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(screenshotter
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET screenshotter APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(screenshotter SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(screenshotter
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(screenshotter PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(screenshotter PRIVATE Qt6::Network)

set_target_properties(screenshotter PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(screenshotter)
endif()
