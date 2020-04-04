include(FetchContent)

# Fetch GoogleTest
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.16.0
        OVERRIDE_FIND_PACKAGE
        EXCLUDE_FROM_ALL
)

enable_testing()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

file(GLOB test-sources "*_test.cpp")

add_executable(tests "${test-sources}")
target_link_libraries(tests gtest_main pthread StrongTypes)

add_test(
        NAME unit-test
        COMMAND tests
)
