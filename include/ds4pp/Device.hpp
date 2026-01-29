#pragma once

#include <chrono>
#include <cstdint>
#include <tuple>
#include <vector>
#include <ds4pp/Input.hpp>
#include <ds4pp/Models.hpp>
#include <ds4pp/TouchPad.hpp>


namespace DS4 {

class DualShock4 {
public:
  DualShock4();
  ~DualShock4();

  bool Connect() const;
  void Rumble(uint8_t RightMotor, uint8_t LeftMotor,
              std::chrono::duration<double> duration) const;
  void EndRumble() const;

  [[nodiscard]] uint8_t GetBatteryLevel() const;
  [[nodiscard]] std::tuple<TouchPoint, TouchPoint> GetTouchPadState() const;

  [[nodiscard]] std::tuple<int16_t, int16_t, int16_t> GetGyroData() const;
  [[nodiscard]] std::tuple<int16_t, int16_t, int16_t> GetAccelData() const;

  [[nodiscard]] Models GetDeviceModel() const;

  void SetLed(uint8_t r, uint8_t g, uint8_t b) const;
  void EnableFlash(bool enabled);
  [[nodiscard]] bool IsFlashEnabled() const;
  void SetFlash(uint8_t FlashDurationOn, uint8_t FlashDurationOff) const;

  bool SendCommandBuffer();

  bool IsButtonPressed(ControllerButton Button);
  bool AreButtonsPressed(std::vector<ControllerButton> &Buttons);

  void Update();

private:
  bool IsTimeEnd();

  struct Impl;
  Impl *impl;
};

} // namespace DS4
