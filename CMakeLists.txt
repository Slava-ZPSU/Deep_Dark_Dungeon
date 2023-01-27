cmake_minimum_required(VERSION 3.16)

project(Deep_Dark_Dungeon C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(SRC_LIST
    ${CMAKE_CURRENT_SOURCE_DIR}/Game_Menu.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Structs.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GamePlayFunctions.cpp
)

add_executable(
  ${PROJECT_NAME}
  ${SRC_LIST}
)