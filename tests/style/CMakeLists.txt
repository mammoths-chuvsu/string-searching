cmake_minimum_required(VERSION 3.20)

project("string-searching-style-check" LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/CPM.cmake)

CPMAddPackage(
  NAME Format.cmake
  VERSION 1.7.3
  GITHUB_REPOSITORY TheLartians/Format.cmake
)
