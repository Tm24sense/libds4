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

include(GNUInstallDirs)

# Install the library binaries
install(TARGETS ds4 ds4pp
    EXPORT libds4-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Install headers
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Generate and install the Config file so find_package() works
install(EXPORT libds4-targets
    NAMESPACE libds4::
    DESTINATION share/libds4
)

#add_executable(ds4_test tests/cpp_test.cpp)
#target_link_libraries(ds4_test PRIVATE ds4pp)