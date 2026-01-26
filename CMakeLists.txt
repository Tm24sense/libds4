cmake_minimum_required(VERSION 3.21)
project(libds4 VERSION 1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

find_package(hidapi CONFIG REQUIRED)
add_library(ds4
    src/ds4/ds4_identify.c
    src/ds4/ds4_handle.c
    src/ds4/ds4_output.c
    src/ds4/ds4_input.c
    src/ds4/ds4_controls.c
)

target_include_directories(ds4
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(ds4 PUBLIC hidapi::hidapi)
add_library(ds4pp
    src/ds4pp/Device.cpp
)

target_include_directories(ds4pp
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(ds4pp PUBLIC ds4)
include(CMakePackageConfigHelpers)

install(TARGETS ds4 ds4pp
    EXPORT libds4_targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/ DESTINATION include)

install(EXPORT libds4_targets
    FILE libds4Targets.cmake
    NAMESPACE libds4::
    DESTINATION share/libds4
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/libds4ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/libds4Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/libds4Config.cmake"
    INSTALL_DESTINATION share/libds4
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/libds4Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/libds4ConfigVersion.cmake"
    DESTINATION share/libds4
)

option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    add_executable(cpp_test tests/cpp_test.cpp)
    target_link_libraries(
        cpp_test ds4pp
    )
endif()
