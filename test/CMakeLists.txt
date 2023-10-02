cmake_minimum_required(VERSION 3.14...3.22)

project(Geeks4GeeksTests LANGUAGES CXX)

# -- -- Options -- --

option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)
option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)

# -- - Import tools -- --
find_package(Git)
if(Git_FOUND)
  message("Git found: ${GIT_EXECUTABLE}")
endif()
set(VERSION_UPDATE_FROM_GIT "TRUE")
include(../cmake/GetVersionFromGitTag.cmake)
include(../cmake/tools.cmake)

# -- -- Dependencies -- --

include(../cmake/CPM.cmake)

CPMAddPackage(
  NAME fmt
  GIT_TAG 8.1.1
  GITHUB_REPOSITORY fmtlib/fmt
  OPTIONS "FMT_INSTALL YES" # create an installable target
)

FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/doctest/doctest.git
  GIT_TAG b7c21ec5ceeadb4951b00396fc1e4642dd347e5f # 2.4.9
)

FetchContent_MakeAvailable(doctest)
CPMAddPackage("gh:TheLartians/Format.cmake@1.7.3")

if(TEST_INSTALLED_VERSION)
  find_package(Geeks4Geeks REQUIRED)
else()
  CPMAddPackage(NAME Geeks4Geeks SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
endif()

# -- -- Create binary -- --
file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
add_executable(${PROJECT_NAME} ${sources})
# target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
target_link_libraries(${PROJECT_NAME} PRIVATE doctest::doctest Geeks4Geeks::Geeks4Geeks fmt::fmt)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

# ---- Add preprocessor definitions ----
# Add a preprocessor definition for DEBUG_PRINTS_ON when the build configuration is Debug
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions(-DDEBUG_PRINTS_ON)
endif()

# enable compiler warnings
if(NOT TEST_INSTALLED_VERSION)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(Geeks4Geeks PUBLIC -Wall -Wpedantic -Wextra -Werror)
  elseif(MSVC)
    target_compile_options(Geeks4Geeks PUBLIC /W4 /WX)
    target_compile_definitions(${PROJECT_NAME} PUBLIC DOCTEST_CONFIG_USE_STD_HEADERS)
  endif()
endif()

# ---- Add Geeks4GeeksTests ----

enable_testing()

# Note: doctest and similar testing frameworks can automatically configure CMake tests. For other
# testing frameworks add the tests target instead: add_test(NAME ${PROJECT_NAME} COMMAND
# ${PROJECT_NAME})

include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(${PROJECT_NAME})

# ---- code coverage ----

if(ENABLE_TEST_COVERAGE)
  target_compile_options(Geeks4Geeks PUBLIC -O0 -g -fprofile-arcs -ftest-coverage)
  target_link_options(Geeks4Geeks PUBLIC -fprofile-arcs -ftest-coverage)
endif()
