cmake_minimum_required(VERSION 3.15)
project(StrongTypes)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -D_GLIBCXX_DEBUG")

include(GNUInstallDirs)

install(
        DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        FILES_MATCHING PATTERN "*.h"
)

add_library(StrongTypes INTERFACE)

# Set the include directories for both build and install
target_include_directories(StrongTypes INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

add_subdirectory(test)

install(TARGETS StrongTypes EXPORT StrongTypesTargets)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/StrongTypesTargetsConfigVersion.cmake
        VERSION 1.0.0
        COMPATIBILITY AnyNewerVersion
)

install(EXPORT StrongTypesTargets
        FILE StrongTypesTargets.cmake
        DESTINATION ${CMAKE_INSTALL_DATADIR}
)

configure_file(StrongTypesTargetsConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/StrongTypesTargetsConfig.cmake @ONLY)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/StrongTypesTargetsConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/StrongTypesTargetsConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_DATADIR}
)
