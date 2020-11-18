cmake_minimum_required(VERSION 3.0.0)
project(AndreysUtils VERSION 0.1.0)

file(GLOB SOURCES "source/*.c")
file(GLOB HEADERS "include/*.h")

include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(numeral_system_converter ${SOURCES} ${HEADERS})

file(GLOB TEST_SOURCES "test/*.c")

add_executable(test_numeral_system_converter ${TEST_SOURCES} ${HEADERS})

target_link_libraries(test_numeral_system_converter numeral_system_converter)

enable_testing()

add_test(test1 test_numeral_system_converter 23 Int 10 23 10)
set_tests_properties(test1 PROPERTIES PASS_REGULAR_EXPRESSION "1" FAIL_REGULAR_EXPRESSION "0")

add_test(test2 test_numeral_system_converter 23.45 Double 10 23.45 10)
set_tests_properties(test2 PROPERTIES PASS_REGULAR_EXPRESSION "1" FAIL_REGULAR_EXPRESSION "0")

add_test(test3 test_numeral_system_converter 23. DComplex 0 1 3 2 10)
set_tests_properties(test3 PROPERTIES PASS_REGULAR_EXPRESSION "1" FAIL_REGULAR_EXPRESSION "0")

#set_tests_properties(test1 PROPERTIES TIMEOUT 1)




