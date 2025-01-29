cmake_minimum_required(VERSION 3.20)

project("string-searching" CXX)
set(CMAKE_CXX_STANDARD 20)

# Enable CPM
include("cmake/CPM.cmake")

add_subdirectory("src")
include_directories("src")
CPMAddPackage(
  NAME Boost
  VERSION 1.86.0
  URL https://github.com/boostorg/boost/releases/download/boost-1.86.0/boost-1.86.0-cmake.tar.xz
  URL_HASH SHA256=2c5ec5edcdff47ff55e27ed9560b0a0b94b07bd07ed9928b476150e16b0efc57
  OPTIONS "BOOST_ENABLE_CMAKE ON" "BOOST_INCLUDE_LIBRARIES program_options" # Note the escapes!
)

find_package(Boost REQUIRED COMPONENTS program_options)
if(Boost_FOUND)
  target_link_libraries(${PROJECT_NAME} Boost::program_options)
else()
  message(FATAL_ERROR "Boost program_options not found!")
endif()

# Option to enable or disable unit tests
option(ENABLE_UNIT_TESTS "Enable unit tests" ON)
if(ENABLE_UNIT_TESTS)
  add_subdirectory("tests/unit")
endif()

# Option to enable or disable style checks
option(ENABLE_STYLE_CHECKS "Enable style checks" ON)
if(ENABLE_STYLE_CHECKS)
  add_subdirectory("tests/style")
endif()
