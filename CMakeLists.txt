cmake_minimum_required(VERSION 3.20)

project("string-searching" CXX)
set(CMAKE_CXX_STANDARD 20)

# download CPM.cmake
file(
    DOWNLOAD
    https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.40.5/CPM.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
    EXPECTED_HASH SHA256=c46b876ae3b9f994b4f05a4c15553e0485636862064f1fcc9d8b4f832086bc5d
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

add_subdirectory("src/core")

# Option to enable or disable tests
option(ENABLE_TESTS "Enable tests" ON)

if (ENABLE_TESTS)
    add_subdirectory("src/tests")
endif()
