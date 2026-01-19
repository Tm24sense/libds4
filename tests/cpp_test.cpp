#include <ds4pp/Device.hpp>
#include <iostream>

int main()
{
    DS4::DualShock4 device;
    device.Connect(); 
    
    std::vector<DS4_Buttons> buttons = {DS_BTN_Square, DS_BTN_Circle, DS_BTN_Cross, DS_BTN_Triangle};
    while(true)
    {
        device.Update();
        if(device.AreButtonsPressed(buttons))
        {
            break;
        }
    }

    
    
}