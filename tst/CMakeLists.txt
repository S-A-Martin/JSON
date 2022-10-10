set(BINARY ${CMAKE_PROJECT_NAME}_tst)

add_executable(${BINARY} main.cpp json_null_tests.cpp)

target_include_directories(${BINARY} SYSTEM PUBLIC
    ${CMAKE_SOURCE_DIR}/lib/googletest/googletest/include/gtest/
    ${CMAKE_SOURCE_DIR}/lib/json/
)

target_link_libraries(${BINARY} SYSTEM gtest)
target_link_libraries(${BINARY} json)