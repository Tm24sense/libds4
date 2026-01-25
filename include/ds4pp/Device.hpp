#pragma once
extern "C"
{
#include <ds4/ds4.h>
}
#include <vector>
#include <chrono>
#include <tuple>
#include "Input.hpp"
#include "TouchPad.hpp"
#include "Models.hpp"
namespace DS4
{
    class DualShock4
    {
    public:
        DualShock4();
        ~DualShock4();
        void Connect();
        void Rumble(std::byte RightMotor, std::byte LeftMotor, std::chrono::duration<double> duration);
        void EndRumble();
        uint8_t GetBatteryLevel();
        TouchPadState GetTouchPadState();
        std::tuple<int16_t, int16_t, int16_t> GetGyroData();
        std::tuple<int16_t, int16_t, int16_t> GetAccelData();
        Models GetDeviceModel();
        void SetLed(std::byte r, std::byte g, std::byte b);
        void EnableFlash(bool enabled);
        bool IsFlashEnabled();
        void SetFlash(std::byte FlashDurationOn, std::byte FlashDurationOff);
        void SendCommandBuffer();
        bool IsButtonPressed(ControllerButton Button);
        bool AreButtonsPressed(std::vector<ControllerButton> &Buttons);
        void Update();

    private:
        bool IsTimeEnd();
        TouchPadState TouchPad;
        ds4_handle *handle;
        std::chrono::milliseconds TargetDuration;
        std::chrono::high_resolution_clock::time_point clock_end;
        uint64_t RumbleTime;
        bool flash_enabled;
        ds4_state state;
        ds4_message output;
    };
};