# libds4

C/C++ library for reading dualshock4 4 controllers on Windows and Linux supports button input, rumble, led colors, gyro/accel data, and battery monitoring.

## Features

- Polling input from a dualshock4 controller 
- Works on windows and linux
- CMake and xmake support

## Installation & Setup

### CMake with CPM

Add to `CMakeLists.txt`:

```cmake
include(cmake/CPM.cmake)

CPMAddPackage(
    NAME libds4
    GITHUB_REPOSITORY Tm24sense/libds4
    GIT_TAG main
)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE libds4::ds4pp)
```

### xmake(i will add a xmake repo package for libds4 in the future)

Create `xmake.lua`:

```lua
set_project("my_app")
set_languages("c++17")

include("external/libds4")

target("my_app")
    set_kind("binary")
    add_files("src/*.cpp")
    add_packages("libds4")
```

Then run `xmake`.

## Quick Start - C++ API

```cpp
#include <ds4pp/Device.hpp>
#include <iostream>
#include <thread>

int main() {
    DS4::DualShock4 controller;
    controller.Connect();
    
    while (true) {
        controller.Update();
        
        if (controller.IsButtonPressed(ControllerButton::PS)) {
            break;
        }
        
        auto [gx, gy, gz] = controller.GetGyroData();
        std::cout << "Gyro: " << gx << ", " << gy << ", " << gz << "\n";
        
        controller.Rumble(std::byte{200}, std::byte{100}, 
                         std::chrono::milliseconds(50));
        controller.SetLed(255, 0, 0);
        
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    
    return 0;
}
```

## Quick Start - C API

```c
#include <ds4/ds4.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

int main() {
    ds4_handle* controller = ds4_open_device();
    if (!controller) {
        printf("Failed to open device\n");
        return 1;
    }
    
    while (true) {
        ds4_state state = ds4_update(controller);
        
        if (state.PS_Button) {
            break;
        }
        
        ds4_motion_t gyro = ds4_gyro_query(&state);
        printf("Gyro: %d, %d, %d\n", gyro.x, gyro.y, gyro.z);
        
        ds4_message msg = ds4_begin_message();
        ds4_set_vibration(&msg, 200, 100);
        ds4_set_led(&msg, 255, 0, 0);
        ds4_send_commands(controller, &msg);
        
        usleep(16000);
    }
    
    ds4_destroy_handle(controller);
    return 0;
}
```

## Common Tasks

### C++ Button Input

```cpp
controller.Update();

if (controller.IsButtonPressed(ControllerButton::Circle)) {
    std::cout << "Circle pressed\n";
}
```

### C Button Input

```c
ds4_state state = ds4_update(controller);

if (ds4_button_pressed(&state, DS_BTN_Circle)) {
    printf("Circle pressed\n");
}
```

### C++ Rumble

```cpp
controller.Rumble(std::byte{255}, std::byte{128}, 
                 std::chrono::milliseconds(100));
controller.EndRumble();
```

### C Rumble

```c
ds4_message msg = ds4_begin_message();
ds4_set_vibration(&msg, 255, 128);
ds4_send_commands(controller, &msg);
```

### C++ LED

```cpp
controller.SetLed(255, 0, 0);  // red
controller.EnableFlash(true);
controller.SetFlash(50, 200);
```

### C LED

```c
ds4_message msg = ds4_begin_message();
ds4_set_led(&msg, 255, 0, 0);
ds4_enable_flash(&msg, 50, 200, true);
ds4_send_commands(controller, &msg);
```

### C++ Sensors

```cpp
auto [gx, gy, gz] = controller.GetGyroData();
auto [ax, ay, az] = controller.GetAccelData();
uint8_t battery = controller.GetBatteryLevel();
```

### C Sensors

```c
ds4_state state = ds4_update(controller);

ds4_motion_t gyro = ds4_gyro_query(&state);
ds4_motion_t accel = ds4_accel_query(&state);
uint8_t battery = state.battery_level;
```

## Building

Clone and build with CMake:

```bash
git clone https://github.com/Tm24sense/libds4.git
cd libds4
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

Or with xmake:

```bash
xmake build -a
```

Build with tests:

```bash
cmake -DBUILD_TESTS=ON ..
cmake --build .
./cpp_test
```

Or with xmake:

```bash
xmake f --build_tests=y
xmake build -a
xmake run cpp_test
```

## Linux: Non-root Access

On Linux, HID devices require root access by default. Setup udev rules to use without sudo:

```bash
sudo nano /etc/udev/rules.d/50-ds4.rules
```

Add these lines:

```text
SUBSYSTEM=="hidraw", ATTRS{idVendor}=="054c", ATTRS{idProduct}=="05c4", MODE="0666"
SUBSYSTEM=="hidraw", ATTRS{idVendor}=="054c", ATTRS{idProduct}=="09cc", MODE="0666"
```

Then reload:

```bash
sudo udevadm control --reload
sudo udevadm trigger
```
