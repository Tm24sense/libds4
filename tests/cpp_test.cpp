#include <ds4pp/Device.hpp>
#include <iostream>

int main()
{
    DS4::DualShock4 device;
    while(true)
    {
        device.Update();
        if(device.IsButtonPressed(DS_BTN_Square))
        {
            break;
        }
    }

    
    
}