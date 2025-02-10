set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE lib_sources "*.hpp" "*.cpp")

add_library(${BINARY} STATIC ${lib_sources})
set_property(TARGET ${BINARY} PROPERTY POSITION_INDEPENDENT_CODE ON)
