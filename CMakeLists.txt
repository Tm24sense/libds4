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
target_include_directories(ds4 PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(ds4 PUBLIC hidapi::hidapi)


add_library(ds4pp STATIC src/ds4pp/Device.cpp)
target_include_directories(ds4pp PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(ds4pp PUBLIC ds4)

#when im testing
if(PROJECT_IS_TOP_LEVEL)
    message(STATUS "libds4: Developer mode enabled. Building tests...")
    
    add_executable(ds4_test tests/cpp_test.cpp)
    target_link_libraries(ds4_test PRIVATE ds4pp)
endif()


include(GNUInstallDirs)

install(TARGETS ds4 ds4pp
    EXPORT libds4-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/libds4-config.cmake"
"include(CMakeFindDependencyMacro)
find_dependency(hidapi)
include(\"\${CMAKE_CURRENT_LIST_DIR}/libds4-targets.cmake\")
")

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/libds4-config.cmake"
    DESTINATION share/libds4
)

install(EXPORT libds4-targets
    FILE libds4-targets.cmake
    NAMESPACE libds4::
    DESTINATION share/libds4
)