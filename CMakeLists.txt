cmake_minimum_required(VERSION 3.15)
project(libds4 LANGUAGES C CXX)



find_package(hidapi CONFIG REQUIRED)


add_library(ds4 STATIC
    src/ds4/ds4_identify.c
    src/ds4/ds4_handle.c
    src/ds4/ds4_output.c
    src/ds4/ds4_input.c
    src/ds4/ds4_controls.c
)


target_include_directories(ds4 PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(ds4 PUBLIC hidapi::hidapi)

#cpp wrapper
add_library(ds4pp STATIC
    src/ds4pp/Device.cpp
)

target_include_directories(ds4pp PUBLIC ${PROJECT_SOURCE_DIR}/include)


target_link_libraries(ds4pp PUBLIC ds4)


add_executable(ds4_test tests/debug_menu.c)
target_link_libraries(ds4_test PRIVATE ds4)