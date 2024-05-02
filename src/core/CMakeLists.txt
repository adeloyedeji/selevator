include_directories(${SELEVATOR_INC_DIR})

set(SOURCES
    dispatch.c
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB_PKG REQUIRED glib-2.0)
if (GLIB_PKG_FOUND)
    message(STATUS "Found glib-2.0")
    include_directories(${GLIB_PKG_INCLUDE_DIRS})
endif()


add_library(core STATIC ${SOURCES})

target_link_libraries(core PUBLIC inc)

target_link_libraries(core INTERFACE glib-2.0)