cmake_minimum_required(VERSION 3.15)
project(shopping-list)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(test)

install(
        DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION "include"
        FILES_MATCHING PATTERN "*.h"
)
