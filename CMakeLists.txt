cmake_minimum_required(VERSION 2.8)

project(lab1)
add_executable(${PROJECT_NAME} "main.c")

target_link_libraries(lab1 m)
