cmake_minimum_required(VERSION 3.21)
project(libds4 VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_SHARED "Build libds4 as a shared library" OFF)
option(BUILD_TESTS  "Build test executables" OFF)

if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/cmake/CPM.cmake")
    file(DOWNLOAD
        "https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/get_cpm.cmake"
        "${CMAKE_CURRENT_LIST_DIR}/cmake/CPM.cmake" SHOW_PROGRESS)
endif()
include(cmake/CPM.cmake)

CPMAddPackage(
    NAME hidapi
    GITHUB_REPOSITORY libusb/hidapi
    GIT_TAG master
    OPTIONS "BUILD_SHARED_LIBS OFF"
)

set(DS4_SOURCES
    src/ds4/ds4_identify.c
    src/ds4/ds4_handle.c
    src/ds4/ds4_output.c
    src/ds4/ds4_input.c
    src/ds4/ds4_controls.c
)

if(BUILD_SHARED)
    add_library(ds4 SHARED ${DS4_SOURCES})
    target_compile_definitions(ds4 PRIVATE DS4_BUILD_SHARED)
else()
    add_library(ds4 STATIC ${DS4_SOURCES})
    target_compile_definitions(ds4 PUBLIC DS4_STATIC)
endif()

target_include_directories(ds4 PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
target_link_libraries(ds4 PRIVATE hidapi::hidapi)

add_library(ds4pp STATIC src/ds4pp/Device.cpp)
target_include_directories(ds4pp PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
target_link_libraries(ds4pp PUBLIC ds4)

add_library(libds4::ds4   ALIAS ds4)
add_library(libds4::ds4pp ALIAS ds4pp)

if(BUILD_TESTS)
    foreach(test IN ITEMS commands debug_menu)
        add_executable(${test} tests/${test}.c)
        target_link_libraries(${test} PRIVATE ds4)
    endforeach()

    foreach(test IN ITEMS cpp_test touchpad_test)
        add_executable(${test} tests/${test}.cpp)
        target_link_libraries(${test} PRIVATE ds4pp)
    endforeach()
endif()