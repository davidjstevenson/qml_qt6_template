cmake_minimum_required(VERSION 3.18)

#define the project name and version these end up in ${PROJECT_NAME}_version.h
project(qmlQt6 VERSION 1.0 LANGUAGES CXX)

# some cmake helper files/functions
add_subdirectory(cmake)

# add main application
add_subdirectory(src)
