# OpenCV CMake file written by Petr Stepanov (pstepanov@hamamatsu.com)

# Instructions:
# 1. Put this CMakeLists.txt in the program directory containing project files: source files, header files and LinkDef.h
# 2. C++ file containing main() function must be named main.c (or .cc, .cpp etc...)
# 3. Specify the name of your executable below (stored it CMake PROJECT_NAME variable):

# Assert CMake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# This is your project statement. You should always list languages
project(hc-delimiter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

# For setting project in IDE via CMake generators
include_directories(${ROOT_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/src/)

# Build list of header files
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS 
                          ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hxx 
                          ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp 
                          ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hh 
                          ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
message(STATUS "Found list of headers:")
message(STATUS "${HEADERS}")

# Build list of source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS 
                          ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx 
                          ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp 
                          ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc 
                          ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
message(STATUS "Found list of sources:")
message(STATUS "${SOURCES}")

if(MSVC)
  set_target_properties(${PROJECT_NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
endif()

# Find location of the enrty point file (main.c*)
file(GLOB_RECURSE MAIN ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx 
                       ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp 
                       ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc 
                       ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
list(FILTER MAIN INCLUDE REGEX "main\\.c")
message(STATUS "Found entry point file: ${MAIN}")

# Create the main program using the library.
add_executable(${PROJECT_NAME} ${MAIN})
