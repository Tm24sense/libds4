#include <ds4pp/Device.hpp>
#include <stdexcept>
#include <iostream>

DS4::DualShock4::DualShock4()
{
    this->handle = nullptr;
    this->output = ds4_begin_message();
    this->flash_enabled = false;
}

DS4::DualShock4::~DualShock4()
{
    ds4_destroy_handle(handle);
}

void DS4::DualShock4::Connect()
{
    this->handle = nullptr;
    this->handle = ds4_open_device();

    if (!handle)
    {
        throw std::runtime_error("Failed to find a DualShock4 device (Maybe try running with admin/sudo rights) ");
        ds4_destroy_handle(handle);
    }
}
void DS4::DualShock4::Rumble(uint8_t RightMotor, uint8_t LeftMotor)
{
    ds4_set_vibration(&this->output, RightMotor, LeftMotor);
}

void DS4::DualShock4::SetLed(uint8_t r, uint8_t g, uint8_t b)
{
    ds4_set_led(&this->output, r, g, b);
}

void DS4::DualShock4::EnableFlash(bool enabled)
{
    this->flash_enabled = enabled;
    (enabled) ? ds4_enable_flash(&this->output, 255, 255, 1) : ds4_enable_flash(&this->output, 0x00, 0x00, 0);
}

bool DS4::DualShock4::IsFlashEnabled()
{
    return flash_enabled;
}
void DS4::DualShock4::SetFlash(uint8_t FlashDurationOn, uint8_t FlashDurationOff)
{
    ds4_enable_flash(&this->output, FlashDurationOn, FlashDurationOff, 1);
}
void DS4::DualShock4::SendCommandBuffer()
{
    ds4_send_commands(handle, &this->output);
}

bool DS4::DualShock4::IsButtonPressed(DS4_Buttons Button)
{
    return ds4_button_pressed(&this->state, (Button));
}

bool DS4::DualShock4::AreButtonsPressed(std::vector<DS4_Buttons> &Buttons)
{
    for (DS4_Buttons b : Buttons)
    {
        switch (b)
        {
        // faceButtons (bitmask)
        case DS_BTN_Square:
        case DS_BTN_Cross:
        case DS_BTN_Circle:
        case DS_BTN_Triangle:
            if (!(this->state.faceButtons & b))
                return false;
            break;

        // other buttons
        case DS_BTN_L1:
            if (!DS_BTN_L1)
                return false;
            break;
        case DS_BTN_R1:
            if (!DS_BTN_R1)
                return false;
            break;
        case DS_BTN_L2:
            if (!DS_BTN_L2)
                return false;
            break;
        case DS_BTN_R2:
            if (!DS_BTN_R2)
                return false;
            break;
        case DS_BTN_Share:
            if (!DS_BTN_Share)
                return false;
            break;
        case DS_BTN_Option:
            if (!DS_BTN_Option)
                return false;
            break;
        case DS_BTN_L3:
            if (!DS_BTN_L3)
                return false;
            break;
        case DS_BTN_R3:
            if (!DS_BTN_R3)
                return false;
            break;
        case DS_BTN_TouchPad:
            if (!DS_BTN_TouchPad)
                return false;
            break;

        case DS_BTN_None:
            return false; // optional
        }
    }

    return true; // all buttons pressed
}
void DS4::DualShock4::Update()
{
    this->state = ds4_update(handle);
}
