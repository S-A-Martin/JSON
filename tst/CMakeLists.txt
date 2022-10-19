set(BINARY ${CMAKE_PROJECT_NAME}_tst)

add_executable(${BINARY} main.cpp json_data_tests.cpp json_printer_tests.cpp json_parser_tests.cpp json_util_tests.cpp)

target_include_directories(${BINARY} SYSTEM PUBLIC
    ${CMAKE_SOURCE_DIR}/lib/googletest/googletest/include/gtest/
    ${CMAKE_SOURCE_DIR}/lib/json/
)

target_link_libraries(${BINARY} SYSTEM gtest)
target_link_libraries(${BINARY} json)