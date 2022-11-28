cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PROJECT_NAME lab2)


file(GLOB_RECURSE SRC_FILES
        "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/*.h"
        )

project(${PROJECT_NAME})
add_executable(${PROJECT_NAME} ${SRC_FILES})
