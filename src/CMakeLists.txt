add_library(JSON 
    json_data.cpp
    json_null.cpp
    json_parser.cpp
    json_printer.cpp
    json_util.cpp
)

target_include_directories(JSON
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)