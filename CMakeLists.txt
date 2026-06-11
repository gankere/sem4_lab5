cmake_minimum_required(VERSION 3.16)
project(painter_lab VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Находим Qt6
find_package(Qt6 REQUIRED COMPONENTS Widgets Test)

# ==========================================
# 1. Основной исполняемый файл приложения
# ==========================================
add_executable(painter_lab 
    main.cpp
    domain.cpp domain.h
    presentation.cpp presentation.h
    logger.cpp logger.h
    qtcanvaswidget.cpp qtcanvaswidget.h
    mainwindow.cpp mainwindow.h
)
target_link_libraries(painter_lab PRIVATE Qt6::Widgets)

# ==========================================
# 2. Исполняемый файл для тестов
# ==========================================
add_executable(painter_lab_tests
    test.cpp
    domain.cpp
    logger.cpp
    qtcanvaswidget.cpp
    mainwindow.cpp
    presentation.cpp
)

# Явно включаем moc для test.cpp
set_source_files_properties(test.cpp PROPERTIES AUTOMOC ON)

target_include_directories(painter_lab_tests PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(painter_lab_tests PRIVATE 
    Qt6::Widgets
    Qt6::Test
)

enable_testing()
add_test(NAME PainterLabUnitTests COMMAND painter_lab_tests)