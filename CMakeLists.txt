cmake_minimum_required(VERSION 3.0.0)
project(numeral_system_converter VERSION 0.1.0)

file(GLOB SOURCES "*.c")
file(GLOB HEADERS "*.h")

add_executable(numeral_system_converter ${SOURCES} ${HEADERS})


