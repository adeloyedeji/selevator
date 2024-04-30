if (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
    cmake_minimum_required(VERSION 3.20)
else()
    cmake_minimum_required(VERSION 3.22)
endif()

# Do not allow building in source directory.
if (CMAKE_CURRENT_BINARY_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    message(FATAL_ERROR "In source builds not allowed. Create a build directory to build this project.")
endif()

message(STATUS "CMake Version: ${CMAKE_VERSION}")
message(STATUS "Source Dir: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "Host system: ${CMAKE_HOST_SYSTEM_NAME}")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

add_subdirectory(src)