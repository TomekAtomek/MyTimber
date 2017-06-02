cmake_minimum_required (VERSION 2.6)
project (MyTimber)

# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)
set (SFML_DIR /home/tomek/SFML_project)
set (SOURCES_DIR /home/tomek/projects/MyTimber)
set (SOURCE_FILES ${SOURCES_DIR}/main.cpp)

add_compile_options(-std=c++11)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
  "${PROJECT_BINARY_DIR}/TutorialConfig.h"
  )

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")
include_directories ("${PROJECT_SOURCE_DIR}/SFML_source/SFML")

add_subdirectory (SFML_source/SFML)

# add the executable
add_executable(MyTimber ${SOURCE_FILES})
target_link_libraries (MyTimber sfml-graphics)
target_link_libraries (MyTimber sfml-window)
target_link_libraries (MyTimber sfml-system)
