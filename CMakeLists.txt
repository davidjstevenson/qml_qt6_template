cmake_minimum_required(VERSION 3.18)

project(qmlQt6 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.3 COMPONENTS Quick Gui REQUIRED)

qt_add_executable(qmlQt6 WIN32 main.cpp)

target_link_libraries(qmlQt6 PRIVATE Qt6::Gui Qt6::Quick)

qt_add_qml_module(qmlQt6
    URI gui
    VERSION 1.0
    QML_FILES main.qml
)

target_compile_definitions(qmlQt6 PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
