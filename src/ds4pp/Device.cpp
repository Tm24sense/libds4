#include <ds4pp/Device.hpp>
#include <stdexcept>

using namespace std::chrono_literals;

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
void DS4::DualShock4::Rumble(uint8_t RightMotor, uint8_t LeftMotor, std::chrono::duration<double> duration)
{
    this->clock_end = std::chrono::high_resolution_clock::now() +
                      std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(duration);

    ds4_set_vibration(&this->output, RightMotor, LeftMotor);
}

void DS4::DualShock4::EndRumble()
{
    this->output.hid_report.report[4] = 0x00;
    this->output.hid_report.report[5] = 0x00;
}
uint8_t DS4::DualShock4::GetBatteryLevel()
{
    return (ds4_battery_level(&this->state));
}

std::tuple<int16_t, int16_t, int16_t> DS4::DualShock4::GetGyroData()
{
    ds4_motion_t gyro_data = ds4_gyro_query(&this->state);
    return {gyro_data.x, gyro_data.y, gyro_data.z};
}
std::tuple<int16_t, int16_t, int16_t> DS4::DualShock4::GetAccelData()
{
    ds4_motion_t accel_data = ds4_accel_query(&this->state);
    return {accel_data.x, accel_data.y, accel_data.z};
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
    if (!ds4_send_commands(handle, &this->output))
    {
        throw std::runtime_error("Device removed or disconnected could not send buffer to device");
    }
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
        case DS_BTN_Square:
        case DS_BTN_Cross:
        case DS_BTN_Circle:
        case DS_BTN_Triangle:
            if (!(this->state.faceButtons & b))
                return false;
            break;

        case DS_BTN_L1:
            if (!state.L1)
                return false;
            break;
        case DS_BTN_R1:
            if (!state.R1)
                return false;
            break;
        case DS_BTN_L2:
            if (!state.L2)
                return false;
            break;
        case DS_BTN_R2:
            if (!state.R2)
                return false;
            break;
        case DS_BTN_Share:
            if (!state.Share)
                return false;
            break;
        case DS_BTN_Option:
            if (!state.Option)
                return false;
            break;
        case DS_BTN_L3:
            if (!state.L3)
                return false;
            break;
        case DS_BTN_R3:
            if (!state.R3)
                return false;
            break;
        case DS_BTN_TouchPad:
            if (!state.TouchPad_click)
                return false;
            break;
        case DS_DPAD_NORTH:
            if (state.dpad_state != DS_DPAD_NORTH)
                return false;
            break;
        case DS_DPAD_NORTH_EAST:
            if (state.dpad_state != DS_DPAD_NORTH_EAST)
                return false;
            break;
        case DS_DPAD_EAST:
            if (state.dpad_state != DS_DPAD_EAST)
                return false;
            break;
        case DS_DPAD_SOUTH_EAST:
            if (state.dpad_state != DS_DPAD_SOUTH_EAST)
                return false;
            break;
        case DS_DPAD_SOUTH:
            if (state.dpad_state != DS_DPAD_SOUTH)
                return false;
            break;
        case DS_DPAD_SOUTH_WEST:
            if (state.dpad_state != DS_DPAD_SOUTH_WEST)
                return false;
            break;
        case DS_DPAD_WEST:
            if (state.dpad_state != DS_DPAD_WEST)
                return false;
            break;
        case DS_DPAD_NORTH_WEST:
            if (state.dpad_state != DS_DPAD_NORTH_WEST)
                return false;
            break;
        case DS_BTN_None:
            return false;
            break;
        }
    }

    return true;
}
void DS4::DualShock4::Update()
{
    if (IsTimeEnd())
    {
        this->EndRumble();
    }
    this->state = ds4_update(handle);
}
bool DS4::DualShock4::IsTimeEnd()
{
    if (this->clock_end <= std::chrono::high_resolution_clock::now())
    {
        return true;
    }
    return false;
}
