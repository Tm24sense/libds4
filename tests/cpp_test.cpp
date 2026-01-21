#include <chrono>
#include <thread>
#include <iostream>
#include <ds4pp/Device.hpp>
int main() 
{
    DS4::DualShock4 device;
    device.Connect();

    // Target 250Hz (4ms per update)
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

        // Calculate how long to sleep to maintain the rate
        auto end = std::chrono::steady_clock::now();
        auto elapsed = end - start;
        if (elapsed < frameDuration) {
            std::this_thread::sleep_for(frameDuration - elapsed);
        }
    }
}