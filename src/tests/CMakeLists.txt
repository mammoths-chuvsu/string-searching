set(BINARY ${CMAKE_PROJECT_NAME}_test)

# downlaod googletest
CPMAddPackage(
    NAME googletest
    GITHUB_REPOSITORY google/googletest
    GIT_TAG v1.15.2
    VERSION 1.15.2
    OPTIONS "INSTALL_GTEST OFF" "gtest_force_shared_crt"
)

# getting GTest
enable_testing()

# building tests
file(GLOB_RECURSE test_sources "*.hpp" "*.cpp")
add_executable(${BINARY} ${test_sources})
add_test(NAME ${BINARY} COMMAND ${BINARY})

# linking with gtest and implemented classes
target_link_libraries(${BINARY} PRIVATE ${CMAKE_PROJECT_NAME} gtest gmock)
