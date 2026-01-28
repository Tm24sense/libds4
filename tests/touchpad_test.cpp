
#include <ds4pp/Device.hpp>
#include <iostream>

int main() {
  DS4::DualShock4 ds4;

  ds4.Connect();

  while (true) {
    ds4.Update();
    auto [Finger1, Finger2] = ds4.GetTouchPadState();

    std::cout << "Finger1 pressed: " << Finger1.active << std::endl;
    std::cout << "Finger2 pressed: " << Finger2.active << std::endl;
  }
}