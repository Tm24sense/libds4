#include <chrono>
#include <thread>
#include <iostream>
#include <ds4pp/Device.hpp>
int main() 
{
    DS4::DualShock4 device;
    device.Connect();
    const int targetHz = 250;
    const std::chrono::milliseconds frameDuration(1000 / targetHz);

    while (true) 
    {
        auto start = std::chrono::steady_clock::now();

        device.Update();
        
        // Output data
        auto [x, y, z] = device.GetAccelData();
        std::cout << "\rX: " << x << " Y: " << y << " Z: " << z << std::flush;

        device.SendCommandBuffer();
    }
}