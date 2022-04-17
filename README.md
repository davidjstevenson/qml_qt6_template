# Title...

# Build
This is currently only configured for Windows, though mac and linux should work but will likely need some adjustments to the cmake files

If Qt is not installed in the usual place you may need to specify CMAKE_PREFIX_PATH - either in the CMAKE gui when configuring the project
or on the command line "-DCMAKE_PREFX_PATH=D:/Qt/6.3.0/msvc2019_64".

If you want to install without admin priviledges, make sure CMAKE_INSTALL_PREFIX points to somewhere sensible, e.g.
"-DCMAKE_PREFIX_PATH=<source>/install" - where <source> is this directory
