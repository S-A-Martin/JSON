set(BINARY ${CMAKE_PROJECT_NAME}_exec)

add_executable(${BINARY} main.cpp)

target_include_directories(
    ${BINARY} PUBLIC ${CMAKE_SOURCE_DIR}/lib
    ${BINARY} PUBLIC ${CMAKE_SOURCE_DIR}/lib/json/
)

target_link_libraries(${BINARY} json)