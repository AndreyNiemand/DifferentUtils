cmake_minimum_required(VERSION 3.14.1)
project(numeral_system_converter VERSION 0.1.0)

option(NSC_CXX_INTERFACE_SUPPORT "Add C++ interface." ON)
option(NSC_TEST        "Build tests." OFF)
option(NSC_EXECUTABLE  "Build executable file." NOT<${NSC_TEST}>)

set(NSC_HEADERS "include/numeral_system_converter.h")

if (NOT NSC_EXECUTABLE)
    set(NSC_SOURCES "source/numeral_system_converter.c")

    add_library(numeral_system_converter ${NSC_SOURCES} ${NSC_HEADERS})

    if (BUILD_SHARED_LIBS)
        set(NSC_BUILD_TYPE NSC_SHARED_LIBRARY)
    else()
        set(NSC_BUILD_TYPE NSC_STATIC_LIBRARY)
    endif()
else()
    add_executable(${PROJECT_NAME} ${NSC_SOURCES} ${NSC_HEADERS})
    set(NSC_BUILD_TYPE NSC_EXECUTABLE)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE "-D${NSC_BUILD_TYPE}")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/source"
                                           PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} m)

set_target_properties(${PROJECT_NAME} PROPERTIES
                        OUTPUT_NAME nsc
                        C_STANDARD 11
                        C_STANDARD_REQUIRED ON)

if(NSC_CXX_INTERFACE_SUPPORT)
    add_library("${PROJECT_NAME}_cxx_interface" "source/numeral_system_converter.cpp")
    target_link_libraries(${PROJECT_NAME} "${PROJECT_NAME}_cxx_interface")

    set(NSC_CXX_TARGETS ${NSC_CXX_TARGETS}; ${PROJECT_NAME}_cxx_interface)
endif()

if(NSC_TEST)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    file(GLOB NSC_TESTS "test/*")

    find_package(Qt5Test REQUIRED)

    add_executable("test_${PROJECT_NAME}" "test/numeral_system_converter.cpp")
    target_link_libraries("test_${PROJECT_NAME}" ${PROJECT_NAME} Qt5::Test)

    set(NSC_CXX_TARGETS ${NSC_CXX_TARGETS}; test_${PROJECT_NAME})
endif()

foreach(target ${NSC_CXX_TARGETS})
    set_target_properties(${target} PROPERTIES
                            CXX_STANDARD 17
                            CXX_STANDARD_REQUIRED ON)

    target_include_directories(${target} PRIVATE "${PROJECT_SOURCE_DIR}/include")
    target_sources(            ${target} PRIVATE "${PROJECT_SOURCE_DIR}/include/numeral_system_converter.h")
endforeach()

unset(NSC_EXECUTABLE CACHE)
unset(NSC_TEST CACHE)
unset(NSC_CXX_INTERFACE_SUPPORT CACHE)
