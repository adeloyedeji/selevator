# include_directories(${SELEVATOR_INC_DIR})
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/core)
include_directories("${PROJECT_SOURCE_DIR}/src/core")

set(SOURCES
    main.cpp)

set(APP_NAME "elevator-test")

add_executable(${APP_NAME} ${SOURCES})
target_link_libraries(${APP_NAME} PUBLIC core)
install (DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
        DESTINATION
        ${PROJECT_SOURCE_DIR}/bin
)