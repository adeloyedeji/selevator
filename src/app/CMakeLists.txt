include_directories(${SELEVATOR_INC_DIR})
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/core)
include_directories("${PROJECT_SOURCE_DIR}/src/core")

set(SOURCES
    main.cpp)

set(APP_NAME "elevator-test")

add_executable(${APP_NAME} ${SOURCES})
target_link_libraries(${APP_NAME} PUBLIC core)
target_link_libraries(core INTERFACE glib-2.0)
install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${APP_NAME}
        DESTINATION
        ${PROJECT_SOURCE_DIR}/bin
        PERMISSIONS OWNER_EXECUTE
)