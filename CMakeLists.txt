cmake_minimum_required(VERSION 3.16)

project(VEDA_miniProject2_Blog VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)
set(PROJECT_HEADERS

    include/mainwidget.h
        include/writewidget.h
        include/accountdialog.h
        include/postlistwidget.h
        include/postwidget.h
        include/post.h
        include/commentwidget.h
        include/commentdisplaywidget.h
        include/network.h
)

set(PROJECT_SOURCES

    source/mainwidget.cpp
        source/writewidget.cpp
        source/accountdialog.cpp
        source/postlistwidget.cpp
        source/postwidget.cpp
        source/commentwidget.cpp
        source/commentdisplaywidget.cpp
        source/network.cpp
)

set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui")
set(PROJECT_UI

    ui/mainwidget.ui
        ui/writewidget.ui
        ui/accountdialog.ui
        ui/postlistwidget.ui
        ui/postwidget.ui
        ui/commentwidget.ui
        ui/commentdisplaywidget.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(VEDA_miniProject2_Blog
        MANUAL_FINALIZATION
        main.cpp
        ${PROJECT_HEADERS}
        ${PROJECT_SOURCES}
        ${PROJECT_UI}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET VEDA_miniProject2_Blog APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(VEDA_miniProject2_Blog SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(VEDA_miniProject2_Blog
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(VEDA_miniProject2_Blog PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.VEDA_miniProject2_Blog)
endif()
set_target_properties(VEDA_miniProject2_Blog PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS VEDA_miniProject2_Blog
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(VEDA_miniProject2_Blog)
endif()
