# 指定最低版本
cmake_minimum_required(VERSION 3.0)
project(json-unit03)

# 开启大部分警告
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# 搜索源文件
# aux_source_directory(${PROJECT_SOURCE_DIR} SRC) 
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)
add_library(leptjson leptjson.cpp)
add_executable(test_unit03 test.cpp)
target_link_libraries(test_unit03 leptjson)