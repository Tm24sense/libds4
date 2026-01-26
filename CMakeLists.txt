cmake_minimum_required(VERSION 3.21)
project(libds4 VERSION 1.0 LANGUAGES C CXX)
set(VCPKG_LIBRARY_LINKAGE static)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

# ------------------------------
# Find dependencies
# ------------------------------
find_package(hidapi CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

# ------------------------------
# Build libds4 (C Library)
# ------------------------------
add_library(ds4 STATIC
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

# ------------------------------
# Build ds4pp (C++ Wrapper)
# ------------------------------
add_library(ds4pp STATIC
    src/ds4pp/Device.cpp
)

target_include_directories(ds4pp
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
target_link_libraries(ds4pp PUBLIC ds4)

# ------------------------------
# Install & Export
# ------------------------------
include(CMakePackageConfigHelpers)

install(TARGETS ds4 ds4pp
    EXPORT libds4_targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/ DESTINATION include)

# Export the targets file
install(EXPORT libds4_targets
    FILE libds4Targets.cmake
    NAMESPACE libds4::
    DESTINATION share/libds4
)

# Version file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/libds4ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# Configure the Config file from the .in template
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/libds4Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/libds4Config.cmake"
    INSTALL_DESTINATION share/libds4
)

# Install config files
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/libds4Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/libds4ConfigVersion.cmake"
    DESTINATION share/libds4
)

# ------------------------------
# Optional tests
# ------------------------------
option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    add_executable(debug_menu tests/gui_debug_menu.cpp)
    # Note: Use the modern targets found by find_package
    target_link_libraries(debug_menu PRIVATE
        ds4pp
        glfw            
        imgui::imgui
        OpenGL::GL
    )
endif()