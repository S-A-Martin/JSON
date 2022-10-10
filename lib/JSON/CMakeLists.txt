add_library(json json_null.cpp json_data.cpp json_util.cpp json_printer.cpp json_parser.cpp)
target_include_directories(json PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})