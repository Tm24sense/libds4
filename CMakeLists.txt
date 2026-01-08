cmake_minimum_required(VERSION 3.15)
project(libds4 LANGUAGES C)
# ------------------------------
# 1️⃣ Find HIDAPI (required for DS4)
# ------------------------------
find_package(hidapi CONFIG REQUIRED)


# ------------------------------
# 2️⃣ Build the library
# ------------------------------
add_library(ds4 SHARED
    src/ds4_identify.c
    src/ds4_handle.c
    src/ds4_output.c
    src/ds4_input.c
    src/ds4_controls.c  # optional if you have it
)

# Include directories
target_include_directories(ds4
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include   # public headers for users
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src       # if library source needs access
)

# Link HIDAPI
target_link_libraries(ds4 PRIVATE hidapi::hidapi hidapi::libusb)

# ------------------------------
# 3️⃣ Build the test executable
# ------------------------------
add_executable(ds4_test
    tests/commands.c
)

# Link library to test executable
target_link_libraries(ds4_test PRIVATE ds4)

# Include HIDAPI for the executable
target_include_directories(ds4_test PRIVATE ${HIDAPI_INCLUDE_DIRS})
