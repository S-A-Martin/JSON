set(BINARY ${CMAKE_PROJECT_NAME}_exec)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXE_LINKER_FLAGS_INIT "-fsanitize=address -fno-omit-frame-pointer")
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

add_executable(${BINARY} main.cpp)

target_include_directories(
    ${BINARY} PUBLIC ${CMAKE_SOURCE_DIR}/lib
    ${BINARY} PUBLIC ${CMAKE_SOURCE_DIR}/lib/json/
)

target_link_libraries(${BINARY} json)