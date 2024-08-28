cmake_minimum_required(VERSION 3.16)

project(TreasureHunt
        LANGUAGES CXX)

add_executable(TreasureHunt main.cpp src/Functions.cpp)
target_include_directories(TreasureHunt PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
