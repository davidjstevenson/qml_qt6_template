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
