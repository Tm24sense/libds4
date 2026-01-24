# libds4

A lightweight C++ library for reading DualShock 4 controllers on Linux and Windows. Supports Reading and parsing input, rumble, LED colors, gyro/accel data, and battery monitoring.



## Requirements

- CMake 3.21 or higher
- GCC/Clang/Msvc with C++17 support
- hidapi for HID device communication

## Installation with CPM

Add to your CMakeLists.txt:

```cmake
include(cmake/CPM.cmake)

CPMAddPackage(
    NAME libds4
    GITHUB_REPOSITORY Tm24sense/libds4
    GIT_TAG cpm-integration
)

add_executable(your_app main.cpp)
target_link_libraries(your_app PRIVATE ds4pp)
```

## Usage

```cpp
#include <ds4pp/Device.hpp>
#include <iostream>

int main() {
    DS4::DualShock4 controller;
    controller.Connect();
    
    while (true) {
        controller.Update();
        
        // Check input
        if (controller.IsButtonPressed(ControllerButton::PS)) {
            break;
        }
        
        // Rumble
        controller.Rumble(255, 128, std::chrono::milliseconds(100));
        
        // LED
        controller.SetLed(255, 0, 0);
        
        // Sensors
        auto [gx, gy, gz] = controller.GetGyroData();
        
        // Battery
        std::cout << "Battery: " << (double)(controller.GetBatteryLevel()/11)*100 << "%" << std::endl;
    }
    
    return 0;
}
```
## To be able to use this library without root
**First**
```bash
sudo nano /etc/udev/rules.d/50-ds4.rules
```
**then Append these two rules to the file**
```text
# DS4 v1 & v2
SUBSYSTEM=="hidraw", ATTRS{idVendor}=="054c", ATTRS{idProduct}=="05c4", MODE="0666"
SUBSYSTEM=="hidraw", ATTRS{idVendor}=="054c", ATTRS{idProduct}=="09cc", MODE="0666"
```




## Building Tests
```bash
mkdir build && cd build
cmake -DBUILD_TESTS=ON ..
cmake --build .
./ds4_test or sudo ./ds4_test if you havent added the sudo rule
```
