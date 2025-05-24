cmake_minimum_required(VERSION 3.10)
project(json_parser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加库目标
add_library(json_lib
    src/parser.cpp
    src/value.cpp
)

target_include_directories(json_lib PUBLIC json)

# 添加 Google Test
find_package(GTest REQUIRED)
enable_testing()

# 添加测试可执行文件
add_executable(parser_test tests/parser_test.cpp)
target_link_libraries(parser_test
    PRIVATE
    json_lib
    GTest::GTest
    GTest::Main
)

# 添加到 CTest
add_test(NAME parser_test COMMAND parser_test)