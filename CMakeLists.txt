cmake_minimum_required(VERSION 3.15)
project(libds4 LANGUAGES C)

find_package(hidapi CONFIG REQUIRED)



add_library(ds4 SHARED
    src/ds4_identify.c
    src/ds4_handle.c
    src/ds4_output.c
    src/ds4_input.c
    src/ds4_controls.c  
)


target_include_directories(ds4
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include   
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src       
)

target_link_libraries(ds4 PRIVATE hidapi::hidapi hidapi::libusb)


add_executable(ds4_test
    tests/test.c
)

target_link_libraries(ds4_test PRIVATE ds4)

target_include_directories(ds4_test PRIVATE ${HIDAPI_INCLUDE_DIRS})
