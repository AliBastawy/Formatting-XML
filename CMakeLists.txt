cmake_minimum_required(VERSION 3.5)

project(DSAProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

#set_target_properties(DSAProject PROPERTIES WIN32_EXECUTABLE TRUE)
#add_executable(DSAProject WIN32 main.cpp)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        options.h
        options.cpp
        options.ui
        Resources.qrc
        consistency.h
        consistency.cpp
        consistency.ui
        formatting.h
        formatting.cpp
        formatting.ui
        tojson.h
        tojson.cpp
        tojson.ui
#        compress.h
#        compress.cpp
#        compress.ui
        Nodes_Tree.cpp
        Nodes_Tree.h
        tree.cpp
        tree.h
        XML_Formater.cpp
        XML_Formater.h
        tags.cpp
        tags.h
#        XML_FileConsistency.cpp
        testdialog.h
        testdialog.cpp
        testdialog.ui
#        DataProject.cpp
        DataProject.h
        XML_JSON.cpp
        XML_JSON.h
        graph.h
        graph.cpp
        graph.ui
        graphs1.h
        Graphs1.cpp
        consistfunction.h
        consistfunction.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DSAProject
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET DSAProject APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(DSAProject SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(DSAProject
            ${PROJECT_SOURCES}
        )
#        add_executable(DSAProject WIN32 main.cpp)

    endif()
endif()

target_link_libraries(DSAProject PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(DSAProject PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DSAProject)
endif()
