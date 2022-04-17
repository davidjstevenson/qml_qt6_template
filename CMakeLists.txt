cmake_minimum_required(VERSION 3.18)

project(qmlQt6 VERSION 1.1.2 LANGUAGES CXX)

add_subdirectory(cmake)
add_subdirectory(version)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 20)
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

make_version_header(${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} DESTINATION .)
install(FILES "${PROJECT_SOURCE_DIR}/LICENSE" DESTINATION .)

if (WIN32)
    message("${PROJECT_BINARY_DIR}")
    install(FILES $<TARGET_PDB_FILE:${PROJECT_NAME}> DESTINATION . OPTIONAL)
    install(
      CODE "execute_process(
        COMMAND \"${WINDEPLOYQT_EXECUTABLE}\"
          --dir \"\${CMAKE_INSTALL_PREFIX}\"
          --no-translations
          --qmldir \"${PROJECT_BINARY_DIR}\"
          --compiler-runtime
          \"$<TARGET_FILE:qmlQt6>\"
      )"
      COMPONENT ${PROJECT_NAME}
    )
endif()
