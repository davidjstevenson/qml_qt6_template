
# LIB_NAME should be consistent bewteen qt_add_library and qt_add_qml_module
set(LIB_NAME version)

# LIB_URI should be the path to the current folder with "/" replace with "."
# this is also the name given when import this module in qml files
set(LIB_URI libs.version)

# define this as a static library
qt6_add_library(${LIB_NAME} STATIC)

# define the qml module itself
qt6_add_qml_module(${LIB_NAME}
    URI ${LIB_URI}
    VERSION 1.0
    QML_FILES
        About.qml
    SOURCES
        version.h version.cpp
)

# this library needs the ${PROJECT_NAME}_version.h
target_include_directories(${LIB_NAME} PRIVATE "${CMAKE_BINARY_DIR}/include")
