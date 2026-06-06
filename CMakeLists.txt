cmake_minimum_required(VERSION 3.16)
project(painter_lab VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(painter_lab 
    main.cpp
    domain.cpp domain.h
    presentation.cpp presentation.h
    logger.cpp logger.h
    qtcanvaswidget.cpp qtcanvaswidget.h
    mainwindow.cpp mainwindow.h
)

target_link_libraries(painter_lab PRIVATE Qt6::Widgets)