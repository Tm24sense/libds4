#include <ds4pp/Device.hpp>
#include <iostream>

using namespace std::chrono_literals;
int main()
{
    DS4::DualShock4 device;
    device.Connect();

    std::vector<DS4_Buttons> buttons = {DS_BTN_R2, DS_BTN_L2, DS_DPAD_EAST};
    while (true)
    {
        std::cout << "\033[H\033[J";
        device.Update();

        auto [x, y, z] = device.GetAccelData();

        std::cout << "x: " << x << " y: " << y << " z: " << z << "\n";

        device.SendCommandBuffer();
    }
}