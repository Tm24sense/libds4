#include <ds4pp/Device.hpp>
#include <stdexcept>
DS4::DualShock4::DualShock4()
{
    this->handle = nullptr;
    this->handle = ds4_open_device();

    if (!handle)
    {
        throw std::runtime_error("Failed to find a DualShock4 device (Maybe try running with admin/sudo rights) ");
        ds4_destroy_handle(handle);
    }
    


}

DS4::DualShock4::~DualShock4()
{
    ds4_destroy_handle(handle);
}

bool DS4::DualShock4::IsButtonPressed(DS4_Buttons Button)
{
    return ds4_button_pressed(&this->state, (Button));
}

void DS4::DualShock4::Update()
{
    this->state = ds4_update(handle);
}
