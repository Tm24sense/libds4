#pragma once
extern "C"
{
#include <ds4/ds4.h>
}
#include <vector>
#include <chrono>
#include <tuple>
namespace DS4
{
    class DualShock4
    {
    public:
        DualShock4();
        ~DualShock4();
        void Connect();
        void Rumble(uint8_t RightMotor, uint8_t LeftMotor, std::chrono::duration<double> duration);
        void EndRumble();
        uint8_t GetBatteryLevel();
        std::tuple<int16_t, int16_t, int16_t> GetGyroData();
        std::tuple<int16_t, int16_t, int16_t> GetAccelData();
        void SetLed(uint8_t r, uint8_t g, uint8_t b);
        void EnableFlash(bool enabled);
        bool IsFlashEnabled();
        void SetFlash(uint8_t FlashDurationOn, uint8_t FlashDurationOff);
        void SendCommandBuffer();
        bool IsButtonPressed(DS4_Buttons Button);
        bool AreButtonsPressed(std::vector<DS4_Buttons>& Buttons);
        void Update();

    private:
        bool IsTimeEnd();
        ds4_handle *handle;
        std::chrono::milliseconds TargetDuration;
        std::chrono::high_resolution_clock::time_point clock_end;
        uint64_t RumbleTime;
        bool flash_enabled;
        ds4_state state;
        ds4_message output;
    };
};