set(BINARY ${CMAKE_PROJECT_NAME}_tst)

add_executable(${BINARY} 
    json_data_tests.cpp 
    json_printer_tests.cpp 
    json_parser_tests.cpp 
    json_util_tests.cpp
    main.cpp
)

target_include_directories(${BINARY}
    SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../lib/googletest/googletest/include/gtest/
)

target_link_libraries(${BINARY} 
    PUBLIC gtest
    PUBLIC JSON
)