
set(CMAKE_AUTOMOC ON)

option(DEPLOY_QT_LIBS "Set whether windeployqt will be run" OFF)
option(QML_FROM_SRC_DIR "Sets whether to load QML from the filesystem or QRC" OFF)
option(OUTPUT_TO_CONSOLE "Creates a console window for std::cout and std::err" OFF)
option(REDIRECT_CONSOLE_TO_DEBUG "Redirects std::cout and std::err to the visual studio output window" ON)

if (OUTPUT_TO_CONSOLE)
    add_definitions(-DOUTPUT_TO_CONSOLE)
elseif (REDIRECT_CONSOLE_TO_DEBUG)
    add_definitions(-DREDIRECT_CONSOLE_TO_DEBUG)
endif()

find_package(Qt6 6.3 COMPONENTS Quick Gui QuickControls2 REQUIRED)

set(SOURCES
    main.cpp
    application.h application.cpp
)

qt_add_executable(${PROJECT_NAME} WIN32 ${SOURCES})
target_link_libraries(${PROJECT_NAME}
    PRIVATE 

    Qt6::Gui 
    Qt6::Quick 
    Qt6::QuickControls2
)

if (${QML_FROM_SRC_DIR})
    add_definitions(-DQML_SRC_DIR="${CMAKE_SOURCE_DIR}/src")
endif()

# define the main entry point qml module, the URI here is only referenced
# by main.cpp when pointing to the "main.qml"
qt_add_qml_module(${PROJECT_NAME}
    URI gui
    VERSION 1.0
    QML_FILES main.qml fallback.qml app.qml
    RESOURCES resources/image_cat_CC0.jpg
)

add_subdirectory(version)
make_version_header(${PROJECT_NAME})

target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

# add the version library
add_subdirectory(libs/version)

# link the library to the main app - this name is value given to qt_add_library with "plugin" added as a suffix
target_link_libraries(${PROJECT_NAME} PRIVATE versionplugin)

install(TARGETS ${PROJECT_NAME} DESTINATION .)
install(FILES "${PROJECT_SOURCE_DIR}/LICENSE" DESTINATION .)

if (WIN32)
    install(FILES $<TARGET_PDB_FILE:${PROJECT_NAME}> DESTINATION . OPTIONAL)
    if (DEPLOY_QT_LIBS)
        install(
          CODE "execute_process(
            COMMAND \"${WINDEPLOYQT_EXECUTABLE}\"
              --dir \"\${CMAKE_INSTALL_PREFIX}\"
              --no-translations
              --qmldir \"${CMAKE_BINARY_DIR}\"
              --compiler-runtime
              \"$<TARGET_FILE:qmlQt6>\"
          )"
          COMPONENT ${PROJECT_NAME}
        )
    endif()
endif()
