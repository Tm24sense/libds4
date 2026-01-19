#include <ds4pp/Device.hpp>
#include <iostream>

using namespace std::chrono_literals;
int main()
{
    DS4::DualShock4 device;
    device.Connect();
    
    std::vector<DS4_Buttons> buttons = {DS_BTN_R2, DS_BTN_L2};
    while (true)
    {
        device.Update();
        if (device.AreButtonsPressed(buttons))
        {
            device.Rumble(125, 230, 100ms);
        }
        device.SendCommandBuffer();
    }
}