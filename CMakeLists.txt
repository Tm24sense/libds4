cmake_minimum_required(VERSION 3.21)
project(libds4 VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_SHARED "Build libds4 as a shared library" OFF)
option(BUILD_TESTS "Build test executables" OFF)

# CPM Setup
if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/cmake/CPM.cmake")
    file(DOWNLOAD
        "https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/get_cpm.cmake"
        "${CMAKE_CURRENT_LIST_DIR}/cmake/CPM.cmake"
        SHOW_PROGRESS
    )
endif()
include(cmake/CPM.cmake)

set(HIDAPI_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

CPMAddPackage(
    NAME hidapi
    GITHUB_REPOSITORY libusb/hidapi
    GIT_TAG master
    OPTIONS
        "HIDAPI_BUILD_TESTS OFF"
        "HIDAPI_ENABLE_SHARED OFF"
        "HIDAPI_ENABLE_STATIC ON"
)

# ds4 library
if(BUILD_SHARED)
    add_library(ds4 SHARED
        src/ds4/ds4_identify.c
        src/ds4/ds4_handle.c
        src/ds4/ds4_output.c
        src/ds4/ds4_input.c
        src/ds4/ds4_controls.c
    )
    target_compile_definitions(ds4 PRIVATE DS4_BUILD_DLL)
else()
    add_library(ds4 STATIC
        src/ds4/ds4_identify.c
        src/ds4/ds4_handle.c
        src/ds4/ds4_output.c
        src/ds4/ds4_input.c
        src/ds4/ds4_controls.c
    )
    target_compile_definitions(ds4 PUBLIC DS4_STATIC)
endif()

target_include_directories(ds4 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(ds4 PRIVATE hidapi::hidapi)

# ds4pp library
if(BUILD_SHARED)
    add_library(ds4pp SHARED
        src/ds4pp/Device.cpp
    )
    target_compile_definitions(ds4pp PRIVATE DS4_BUILD_DLL)
else()
    add_library(ds4pp STATIC
        src/ds4pp/Device.cpp
    )
    target_compile_definitions(ds4pp PUBLIC DS4_STATIC)
endif()

target_include_directories(ds4pp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(ds4pp PUBLIC ds4)

if(BUILD_TESTS)
    add_executable(cpp_test tests/cpp_test.cpp)
    target_link_libraries(cpp_test PRIVATE ds4pp)
    
    add_executable(commands tests/commands.c)
    target_link_libraries(commands PRIVATE ds4)
    
    add_executable(debug_menu tests/debug_menu.c)
    target_link_libraries(debug_menu PRIVATE ds4)
    
    add_executable(touchpad_test tests/touchpad_test.cpp)
    target_link_libraries(touchpad_test PRIVATE ds4pp)
endif()