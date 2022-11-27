# this script adds all subprojects to a single build to allow IDEs understand the full project
# structure.

cmake_minimum_required(VERSION 3.14...3.22)

project(BuildAll LANGUAGES CXX)

# --- Import tools ----
find_package(Git)
if(Git_FOUND)
  message("Git found: ${GIT_EXECUTABLE}")
endif()
set (VERSION_UPDATE_FROM_GIT "TRUE")
include(../cmake/GetVersionFromGitTag.cmake)
include(../cmake/tools.cmake)

# needed to generate test target
enable_testing()

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../standalone ${CMAKE_BINARY_DIR}/standalone)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../test ${CMAKE_BINARY_DIR}/test)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../documentation ${CMAKE_BINARY_DIR}/documentation)
