cmake_minimum_required(VERSION 3.20)

project("simulator-tests" LANGUAGES CXX)

# ---- CMake configuration ----

# Include guards
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

# Make Clangd works
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---- Dependencies ----

# Enable CPM
include("../../cmake/CPM.cmake")

# downlaod googletest
CPMAddPackage(
  NAME googletest
  GITHUB_REPOSITORY google/googletest
  GIT_TAG v1.15.2
  VERSION 1.15.2
  OPTIONS "INSTALL_GTEST OFF" "gtest_force_shared_crt"
)

CPMAddPackage(NAME "simulator" SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
CPMAddPackage(NAME "string-searching" SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../..)

# ---- Create binary ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} PRIVATE simulator gtest gtest_main gmock)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)

# getting GTest
enable_testing()
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
