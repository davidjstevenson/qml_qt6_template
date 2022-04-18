# Simple Example Qt6 QML Application
*This is a work in progress and may not yet work...*

This is indented to be an exmple of a simple but fully worked example of how to build and run
and application using Qt6 and QML.

# Platform support
Currently this is only supported on Windows, as I have not had the time to build, test and refine
this under any other platform.



# Build
If Qt is not installed in the usual place you may need to specify CMAKE_PREFIX_PATH - either in the CMAKE gui when configuring the project
or on the command line "-DCMAKE_PREFX_PATH=D:/Qt/6.3.0/msvc2019_64".

If you want to install without admin priviledges, make sure CMAKE_INSTALL_PREFIX points to somewhere sensible, e.g.
"-DCMAKE_INSTALL_PREFIX=<source>/install" - where <source> is this directory


# QMLPLUGIN_OUTPUT_LOCATION
All the QML modules can be put in the one location with the user of QMLPLUGIN_OUTPUT_LOCATION

add to the top level CMakeLists.txt
```
set(QMLPLUGIN_OUTPUT_LOCATION qml)
add_definitions(-DQMLPLUGIN_OUTPUT_LOCATION="${QMLPLUGIN_OUTPUT_LOCATION}/")
set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${QMLPLUGIN_OUTPUT_LOCATION})
```

and to the invocation of `windeployqt`
```
--qmlimport \"${QT_QML_OUTPUT_DIRECTORY}\"
```

then in main.cpp
```
engine.addImportPath(QMLPLUGIN_OUTPUT_LOCATION);
```
