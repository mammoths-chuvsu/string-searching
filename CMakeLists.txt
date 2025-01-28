cmake_minimum_required(VERSION 3.20)

project("string-searching" CXX)
set(CMAKE_CXX_STANDARD 20)

# Enable CPM
include("cmake/CPM.cmake")

add_subdirectory("src")

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
