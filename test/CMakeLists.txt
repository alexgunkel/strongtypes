include(ExternalProject)
set(EXTERNAL_INSTALL_LOCATION ${PROJECT_SOURCE_DIR}/external)

ExternalProject_Add(googletest_ep
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG 78fdd6c00b8fa5dd67066fbb796affc87ba0e075
        GIT_PROGRESS true
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION} -DCMAKE_INSTALL_LIBDIR=lib64 -DCMAKE_CXX_FLAGS="-w"
        )

link_directories(${EXTERNAL_INSTALL_LOCATION}/lib64)

file(GLOB test-sources "*_test.cpp")

add_executable(tests "")
target_sources(tests PRIVATE test_main.cpp ${test-sources})
target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR}/include ${EXTERNAL_INSTALL_LOCATION}/include)
target_link_libraries(tests PRIVATE gtest pthread)
add_dependencies(tests googletest_ep)
