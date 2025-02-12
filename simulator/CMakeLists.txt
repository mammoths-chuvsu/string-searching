cmake_minimum_required(VERSION 3.20)

project(
  "simulator"
  VERSION 1.0.0
  LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 20)

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
include("../cmake/CPM.cmake")

CPMAddPackage(NAME "string-searching" SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

CPMAddPackage(
  NAME Boost
  VERSION 1.86.0
  URL https://github.com/boostorg/boost/releases/download/boost-1.86.0/boost-1.86.0-cmake.tar.xz
  URL_HASH SHA256=2c5ec5edcdff47ff55e27ed9560b0a0b94b07bd07ed9928b476150e16b0efc57
  OPTIONS "BOOST_ENABLE_CMAKE ON" "BOOST_INCLUDE_LIBRARIES program_options" # Note the escapes!
)

# ---- Add source files ----

file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
list(FILTER sources EXCLUDE REGEX ".*main\\.cpp$")

# create library
add_library(${PROJECT_NAME} ${headers} ${sources})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20 POSITION_INDEPENDENT_CODE ON)

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")

# Set includes
target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                         $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)
target_link_libraries(${PROJECT_NAME} "string-searching::string-searching" Boost::program_options)

# create executable
add_executable(run-simulator src/main.cpp)
target_link_libraries(run-simulator PRIVATE simulator)
set_target_properties(
  run-simulator PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin"
)
