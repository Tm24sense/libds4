cmake_minimum_required(VERSION 3.15)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "" FORCE)
endif()

project(libds4 VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries")

find_package(hidapi CONFIG REQUIRED)

# --- Library: ds4 ---
add_library(ds4 STATIC
    src/ds4/ds4_identify.c
    src/ds4/ds4_handle.c
    src/ds4/ds4_output.c
    src/ds4/ds4_input.c
    src/ds4/ds4_controls.c
)

# Standard vcpkg includes
target_include_directories(ds4 PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(ds4 PUBLIC hidapi::hidapi)

# --- Library: ds4pp ---
add_library(ds4pp STATIC src/ds4pp/Device.cpp)
target_include_directories(ds4pp PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(ds4pp PUBLIC ds4)

# --- Local Testing ---
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_executable(ds4_test tests/cpp_test.cpp)
    target_link_libraries(ds4_test PRIVATE ds4pp)
endif()

# --- Installation ---
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS ds4 ds4pp
    EXPORT libds4-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/libds4-config-version.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/libds4-config.cmake"
"include(CMakeFindDependencyMacro)
find_dependency(hidapi CONFIG)
include(\"\${CMAKE_CURRENT_LIST_DIR}/libds4-targets.cmake\")
")

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/libds4-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/libds4-config-version.cmake"
    DESTINATION share/libds4
)

install(EXPORT libds4-targets
    FILE libds4-targets.cmake
    NAMESPACE libds4::
    DESTINATION share/libds4
)