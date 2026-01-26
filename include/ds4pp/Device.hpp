#pragma once

#include <vector>
#include <tuple>
#include <chrono>
#include <cstdint>

#include <ds4pp/Input.hpp>
#include <ds4pp/TouchPad.hpp>
#include <ds4pp/Models.hpp>

namespace DS4 {

class DualShock4 {
public:
    DualShock4();
    ~DualShock4();

    void Connect();
    void Rumble(std::byte RightMotor,
                std::byte LeftMotor,
                std::chrono::duration<double> duration);
    void EndRumble();

    uint8_t GetBatteryLevel();
    TouchPadState GetTouchPadState();

    std::tuple<int16_t,int16_t,int16_t> GetGyroData();
    std::tuple<int16_t,int16_t,int16_t> GetAccelData();

    Models GetDeviceModel();

    void SetLed(uint8_t r, uint8_t g, uint8_t b);
    void EnableFlash(bool enabled);
    bool IsFlashEnabled();
    void SetFlash(uint8_t FlashDurationOn, uint8_t FlashDurationOff);

    void SendCommandBuffer();

    bool IsButtonPressed(ControllerButton Button);
    bool AreButtonsPressed(std::vector<ControllerButton>& Buttons);

    void Update();

private:
    bool IsTimeEnd();

    struct Impl;
    Impl* impl;
};

}
