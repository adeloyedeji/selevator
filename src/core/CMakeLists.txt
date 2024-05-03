include_directories(${SELEVATOR_INC_DIR})

set(SOURCES
    dispatch.c
    elevator.c
)

add_library(core STATIC ${SOURCES})

target_link_libraries(core PUBLIC inc)

target_link_libraries(core INTERFACE glib-2.0)