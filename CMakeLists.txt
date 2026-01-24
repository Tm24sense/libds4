cmake_minimum_required(VERSION 3.21)
project(libds4 VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
option(USE_VCPKG "Use vcpkg instead of CPM for dependencies" OFF)


if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/cmake/CPM.cmake")
    file(DOWNLOAD
        "https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/get_cpm.cmake"
        "${CMAKE_CURRENT_LIST_DIR}/cmake/CPM.cmake"
        SHOW_PROGRESS
    )
endif()
include(cmake/CPM.cmake)


CPMAddPackage(
    NAME hidapi
    GITHUB_REPOSITORY libusb/hidapi
    GIT_TAG master
    OPTIONS "HIDAPI_BUILD_TESTS OFF" "HIDAPI_SHARED OFF"
)

add_library(ds4 STATIC
    src/ds4/ds4_identify.c
    src/ds4/ds4_handle.c
    src/ds4/ds4_output.c
    src/ds4/ds4_input.c
    src/ds4/ds4_controls.c
)
target_include_directories(ds4 PUBLIC include)
target_link_libraries(ds4 PUBLIC hidapi::hidapi)


add_library(ds4pp STATIC src/ds4pp/Device.cpp)
target_include_directories(ds4pp PUBLIC include)
target_link_libraries(ds4pp PUBLIC ds4)


add_executable(ds4_test tests/cpp_test.cpp)
target_link_libraries(ds4_test PRIVATE ds4pp)
