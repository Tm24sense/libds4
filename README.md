# libds4

C/C++ library for reading dualshock4  controllers on windows and linux supports button input, rumble, led colors, gyro/accel data, and reading battery level



## To use in your project

### cmake

add to your 'CMakeLists.txt':

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

create `xmake.lua`:

```lua
set_project("my_app")
set_languages("c++17")

include("external/libds4")-- or wherever you installed the repo to

target("my_app")
    set_kind("binary")
    add_files("src/*.cpp")
    add_packages("libds4") --Or add_packages("ds4pp") for c++ wrapper
```


## C++ api (ds4pp)

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
        
        controller.Rumble(200, 100, 
                         std::chrono::milliseconds(50));
        controller.SetLed(255, 0, 0);
        
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    
    return 0;
}
```

## C api (libds4)

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
        
    
    }
    
    ds4_destroy_handle(controller); // always destory the handle cuz it can prevent the controller from being recognized 
    return 0;
}
```

## Examples

### C++ button input

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

### C++ Rumble/vibrating

```cpp
controller.Rumble(255 /*max*/, 255, 
                 std::chrono::milliseconds(100));
controller.EndRumble();
```

### C Rumble/vibrating

```c
ds4_message msg = ds4_begin_message();
ds4_set_vibration(&msg, 255, 128);
ds4_send_commands(controller, &msg);
```

### C++ LED

```cpp
controller.SetLed(255, 0, 0);  // red
controller.EnableFlash(true); // You always need to enable flash before setting flash or else it wont work
controller.SetFlash(50, 200);
```

### C LED

```c
ds4_message msg = ds4_begin_message();
ds4_set_led(&msg, 255, 0, 0);
ds4_enable_flash(&msg, 50, 200, true);//same here
ds4_send_commands(controller, &msg);
```

### C++ motion sensors

```cpp
auto [gx, gy, gz] = controller.GetGyroData();
auto [ax, ay, az] = controller.GetAccelData();
uint8_t battery = controller.GetBatteryLevel();
```

### C motion sensors

```c
ds4_state state = ds4_update(controller);

ds4_motion_t gyro = ds4_gyro_query(&state);
ds4_motion_t accel = ds4_accel_query(&state);
uint8_t battery = state.battery_level;
```

## Building

Clone and build with CMake also be sure to set BUILD_SHARED

```bash
git clone https://github.com/Tm24sense/libds4.git
cd libds4
mkdir build && cd build
cmake .. -DBUILD_SHARED=ON
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

on Linux, hid devices require root access by default setup udev rules to use without sudo:

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
