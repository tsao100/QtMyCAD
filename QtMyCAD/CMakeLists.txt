cmake_minimum_required(VERSION 3.5)

project(QtMyCAD)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets OpenGL)
find_package(Qt5 REQUIRED COMPONENTS Widgets OpenGL)

include_directories(${Qt5Widgets_INCLUDE_DIRS} ${Qt5OpenGL_INCLUDE_DIRS})

set(SOURCES
    main.cpp
    MainWindow.cpp
    OpenGLWidget.cpp
)

set(HEADERS
    MainWindow.h
    OpenGLWidget.h
)

add_executable(QtMyCAD ${SOURCES} ${HEADERS})
target_link_libraries(QtMyCAD Qt5::Widgets Qt5::OpenGL)
