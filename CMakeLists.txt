cmake_minimum_required(VERSION 3.15)

project(Bst
    VERSION 1.0.0
    DESCRIPTION "Binary Search Tree"
    LANGUAGES CXX
)

set (CMAKE_CXX_STANDARD 17)

include(cmake/CPM.cmake)


add_library(bst src/Bst.cpp)

target_include_directories(bst PUBLIC src)

add_executable(bst_run main.cpp)

target_link_libraries(bst_run PRIVATE bst)


add_subdirectory(tests)
