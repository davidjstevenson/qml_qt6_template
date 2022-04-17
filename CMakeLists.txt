cmake_minimum_required(VERSION 3.18)

#define the project name and version these end up in ${PROJECT_NAME}_version.h
project(qmlQt6 VERSION 1.0 LANGUAGES CXX)

# some cmake helper files/functions
add_subdirectory(cmake)
add_subdirectory(version)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.3 COMPONENTS Quick Gui REQUIRED)

# makes the build structure a little nicer as this puts all the qml
# modules in one place - however this does require the following line
# in main.cpp: engine.addImportPath(QMLPLUGIN_OUTPUT_LOCATION);
set(QMLPLUGIN_OUTPUT_LOCATION qml)
add_definitions(-DQMLPLUGIN_OUTPUT_LOCATION="${QMLPLUGIN_OUTPUT_LOCATION}/")
set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${QMLPLUGIN_OUTPUT_LOCATION})

# this helps Qt Creator find the qml modules, though does not seam to be
# required for the actual build
# set(QML_IMPORT_PATH ${CMAKE_BINARY_DIR}/qml)

qt_add_executable(${PROJECT_NAME} WIN32 main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Gui Qt6::Quick)

# define the main entry point qml module, the URI here is only referenced
# by main.cpp when pointing to the "main.qml"
qt_add_qml_module(${PROJECT_NAME}
    URI gui
    VERSION 1.0
    QML_FILES main.qml fallback.qml
    RESOURCES resources/image_cat_CC0.jpg
)

make_version_header(${PROJECT_NAME})

target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

# add the version library
add_subdirectory(libs/version)

# link the library to the main app - this name is value given to qt_add_library with "plugin" added as a suffix
target_link_libraries(${PROJECT_NAME} PRIVATE versionplugin)

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
          --qmldir \"${CMAKE_BINARY_DIR}\"
          --qmlimport \"${QT_QML_OUTPUT_DIRECTORY}\"
          --compiler-runtime
          \"$<TARGET_FILE:qmlQt6>\"
      )"
      COMPONENT ${PROJECT_NAME}
    )
endif()
