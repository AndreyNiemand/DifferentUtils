cmake_minimum_required(VERSION 3.0.0)
project(AndreysUtils VERSION 0.1.0)

option(NSC_EXECUTABLE "Build executable file."  ON)
option(NSC_LIBRARY    "Build library file."     ON)

file(GLOB NSC_SOURCES "source/*.c")
file(GLOB NSC_HEADERS "include/*.h")

if (NSC_EXECUTABLE)
    add_executable(numeral_system_converter ${NSC_SOURCES} ${NSC_HEADERS})
    set_target_properties(numeral_system_converter PROPERTIES OUTPUT_NAME nsc)
    target_include_directories(numeral_system_converter PUBLIC "${PROJECT_SOURCE_DIR}/include")
    target_compile_definitions(numeral_system_converter PUBLIC -DNSC_EXECUTABLE)
endif()
unset(NSC_EXECUTABLE CACHE)

if (NSC_LIBRARY)
    add_library(numeral_system_converter_lib ${NSC_SOURCES} ${NSC_HEADERS})
    set_target_properties(numeral_system_converter_lib PROPERTIES OUTPUT_NAME nsc)
    target_include_directories(numeral_system_converter_lib PUBLIC "${PROJECT_SOURCE_DIR}/include")
    if (BUILD_SHARED_LIBS)
        target_compile_definitions(numeral_system_converter_lib PUBLIC -DNSC_SHARED_LIBRARY)
    else()
        target_compile_definitions(numeral_system_converter_lib PUBLIC -DNSC_STATIC_LIBRARY)
    endif()
endif()
unset(NSC_LIBRARY CACHE)

file(GLOB NSC_TEST_SOURCES "test/*.c")

add_executable(test_numeral_system_converter ${NSC_TEST_SOURCES} ${NSC_SOURCES} ${NSC_HEADERS})
target_compile_definitions(test_numeral_system_converter PUBLIC -DNSC_STATIC_LIBRARY)
target_include_directories(test_numeral_system_converter PUBLIC "${PROJECT_SOURCE_DIR}/include")

enable_testing()

#                     test_numeral_system_converter  in             {Int}   base    out      digits_count
add_test(nsc_test_i_1 test_numeral_system_converter "23234"         "Int"   "10"    "23234"     "10")
add_test(nsc_test_i_2 test_numeral_system_converter "-2323"         "Int"   "10"    "-2323"     "10")
add_test(nsc_test_i_3 test_numeral_system_converter "10110101100"   "Int"   "2"     "1452"      "2")
add_test(nsc_test_i_4 test_numeral_system_converter "-10110101100"  "Int"   "2"     "-1452"     "2")
add_test(nsc_test_i_5 test_numeral_system_converter "2654"          "Int"   "8"     "1452"      "8")
add_test(nsc_test_i_6 test_numeral_system_converter "-2654"         "Int"   "8"     "-1452"     "8")
add_test(nsc_test_i_7 test_numeral_system_converter "5AC"           "Int"   "16"    "1452"      "16")
add_test(nsc_test_i_8 test_numeral_system_converter "-5AC"          "Int"   "16"    "-1452"     "16")

#                     test_numeral_system_converter in          {Double}   base    out         digits_count
add_test(nsc_test_d_1 test_numeral_system_converter "23.45"     "Double"   "10"    "23.45"      "10")
add_test(nsc_test_d_2 test_numeral_system_converter "23.4542"   "Double"   "10"    "23.4542"    "10")
add_test(nsc_test_d_3 test_numeral_system_converter ".4542"     "Double"   "10"      ".4542"    "10")
add_test(nsc_test_d_4 test_numeral_system_converter "1.1110"    "Double"   "2"     "1.875"      "2")
add_test(nsc_test_d_5 test_numeral_system_converter "-1.111"    "Double"   "2"     "-1.875"     "2")

#                     test_numeral_system_converter in         {DComplex}      base_r  base_i  out_r   out_i  digits_count     
add_test(nsc_test_c_1 test_numeral_system_converter "23."      "DComplex"      "0"     "1"     "+3"    "2"    "10")
add_test(nsc_test_c_2 test_numeral_system_converter "230"      "DComplex"      "0"     "1"     "-2"    "3"    "10")
add_test(nsc_test_c_3 test_numeral_system_converter "-230"     "DComplex"      "0"     "1"      "2"   "-3"    "10")

set_tests_properties(nsc_test_i_1    nsc_test_d_1    nsc_test_c_1         
                     nsc_test_i_2    nsc_test_d_2    nsc_test_c_2
                     nsc_test_i_3    nsc_test_d_3    nsc_test_c_3
                     nsc_test_i_4    nsc_test_d_4                                       
                     nsc_test_i_5    nsc_test_d_5                                                                                    
                     nsc_test_i_6                                                                                                    
                     nsc_test_i_7                                                                                                    
                     nsc_test_i_8                                                                                                    
                                                                            
                     PROPERTIES PASS_REGULAR_EXPRESSION "1"
                                FAIL_REGULAR_EXPRESSION "0"
                                TIMEOUT 1)
