# 指定最低版本
cmake_minimum_required(VERSION 3.0)
project(json)

# 搜索源文件
aux_source_directory(${PROJECT_SOURCE_DIR} SRC) 

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)
add_executable(test_unit01 ${SRC})