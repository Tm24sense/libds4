cmake_minimum_required(VERSION 3.21)
project(libds4 VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF)

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
target_link_libraries(ds4pp PRIVATE ds4)

option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
    message("Building test examples")

    # 1. Fetch GLFW
    CPMAddPackage(
        NAME glfw
        GITHUB_REPOSITORY glfw/glfw
        GIT_TAG 3.3.10
        OPTIONS "GLFW_BUILD_TESTS OFF" "GLFW_BUILD_DOCS OFF" "GLFW_BUILD_EXAMPLES OFF"
    )

    # 2. Fetch ImGui
    CPMAddPackage(
        NAME imgui
        GITHUB_REPOSITORY ocornut/imgui
        GIT_TAG  v1.90
        GIT_SHALLOW TRUE
        DOWNLOAD_ONLY YES
    )

    # 3. Create ImGui Library (The missing step)
    if(imgui_ADDED)
        add_library(imgui_lib STATIC
            ${imgui_SOURCE_DIR}/imgui.cpp
            ${imgui_SOURCE_DIR}/imgui_draw.cpp
            ${imgui_SOURCE_DIR}/imgui_widgets.cpp
            ${imgui_SOURCE_DIR}/imgui_tables.cpp
            ${imgui_SOURCE_DIR}/imgui_demo.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
        )
        
        # Tell the library where to find its own headers
        target_include_directories(imgui_lib PUBLIC 
            ${imgui_SOURCE_DIR} 
            ${imgui_SOURCE_DIR}/backends
        )
        
        # ImGui backends need to know about GLFW and OpenGL
        target_link_libraries(imgui_lib PUBLIC glfw opengl32) # Use 'GL' instead of opengl32 on Linux
    endif()

    # 4. Add debug_menu executable
    add_executable(debug_menu tests/gui_debug_menu.cpp)
    target_include_directories(debug_menu PRIVATE include)
    
    # 5. Link everything
    # Now imgui_lib exists and carries its own include paths!
    target_link_libraries(debug_menu PRIVATE ds4 glfw imgui_lib)

endif()

