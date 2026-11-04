enable_testing()
add_executable(tests)
target_sources(tests
    PUBLIC
        core_test/texture_tests.cc
)

target_link_libraries(tests
    PRIVATE
        core
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
)
