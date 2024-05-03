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
    message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
endif()

project(SElevator CXX C)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(DEBUG_MODE 1)
else()
    set(DEBUG_MODE 0)
endif()

if (NOT ELEVATOR_INSTANCE_COUNT)
    message(STATUS "Default elevator instance count = 4. Specify -DELEVATOR_INSTANCE_COUNT to change default")
    set(ELEVATOR_INSTANCE_COUNT 4)
else()
    message(STATUS "Elevator instance count = ${ELEVATOR_INSTANCE_COUNT}")
endif()

set(SELEVATOR_INC_DIR ${CMAKE_SOURCE_DIR}/src/inc)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB_PKG REQUIRED glib-2.0)
if (GLIB_PKG_FOUND)
    message(STATUS "Found glib-2.0")
    include_directories(${GLIB_PKG_INCLUDE_DIRS})
endif()

add_subdirectory(src)

configure_file(config.h.in ${SELEVATOR_INC_DIR}/config.h @ONLY)