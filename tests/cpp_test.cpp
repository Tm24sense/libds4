#include <chrono>
#include <vector>
#include <thread>
#include <iostream>
#include <ds4pp/Device.hpp>
using namespace std::chrono;
using namespace DS4;
int main() 
{
    DualShock4 device;
    device.Connect();
    
    
    while (true) 
    {
        
        device.Update();
        
        std::vector<ControllerButton> combo = {
            ControllerButton::Circle, ControllerButton::Cross,
            ControllerButton::DPadNorth
        };

        if(device.AreButtonsPressed(combo))
        {
            std::cout << "pressed\n" << (int)device.GetDeviceModel();
        }
        
        device.SendCommandBuffer();
        std::this_thread::sleep_for(2ms);
        
    }
}