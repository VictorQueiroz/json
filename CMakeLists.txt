project(json)
cmake_minimum_required(VERSION 2.4)

set(CMAKE_C_STANDARD 99)

set(JSON_SOURCES
    src/json_stringifier.c
    src/json_value.c
    src/json_object.c
    src/json_array.c
    src/json_string.c)

add_library(json SHARED ${JSON_SOURCES})
target_include_directories(json PUBLIC deps/cvector/include PUBLIC include)
target_compile_options(json PRIVATE -Wall -Wextra -pedantic)

add_executable(json_test test/test.c)
target_link_libraries(json_test PRIVATE json)
