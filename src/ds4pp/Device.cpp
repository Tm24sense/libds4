#include <ds4pp/Device.hpp>
#include <stdexcept>
#include <tuple>

extern "C" {
#include <ds4/ds4.h>
}

using namespace std::chrono_literals;

namespace DS4 {
  struct DualShock4::Impl {
    ds4_handle *handle = nullptr;
    ds4_state state{};
    ds4_message output{};
    bool flash_enabled = false;

    std::chrono::high_resolution_clock::time_point clock_end{};
  };

  DualShock4::DualShock4() : impl(new Impl{}) {
    impl->output = ds4_begin_message();
  }

  DualShock4::~DualShock4() {
    if (impl->handle)
      ds4_destroy_handle(impl->handle);
    delete impl;
  }

  bool DualShock4::Connect() const {
    impl->handle = ds4_open_device();
    if (!impl->handle)
      return false;
    return true;
  }

  void DualShock4::Rumble(uint8_t RightMotor, uint8_t LeftMotor,
                          const std::chrono::duration<double> duration) const {
    impl->clock_end =
        std::chrono::high_resolution_clock::now() +
        std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(
          duration);

    ds4_set_vibration(&impl->output, (RightMotor), (LeftMotor));
  }

  void DualShock4::EndRumble() const {
    impl->output.hid_report.report[4] = 0x00;
    impl->output.hid_report.report[5] = 0x00;
  }

  uint8_t DualShock4::GetBatteryLevel() const {
    return ds4_battery_level(&impl->state);
  }

  std::tuple<TouchPoint, TouchPoint> DualShock4::GetTouchPadState() const {
    TouchPoint Finger0{};
    TouchPoint Finger1{};

    Finger0.id = impl->state.touchpad.N1_id;
    Finger0.active = impl->state.touchpad.N1_touching;
    Finger0.x = impl->state.touchpad.N1_pos_x;
    Finger0.y = impl->state.touchpad.N1_pos_y;

    // Finger 2
    Finger1.id = impl->state.touchpad.N2_id;
    Finger1.active = impl->state.touchpad.N2_touching;
    Finger1.x = impl->state.touchpad.N2_pos_x;
    Finger1.y = impl->state.touchpad.N2_pos_y;

    return {Finger0, Finger1};
  }

  std::tuple<int16_t, int16_t, int16_t> DualShock4::GetGyroData() const {
    ds4_motion_t g = ds4_gyro_query(&impl->state);
    return {g.x, g.y, g.z};
  }

  std::tuple<int16_t, int16_t, int16_t> DualShock4::GetAccelData() const {
    ds4_motion_t a = ds4_accel_query(&impl->state);
    return {a.x, a.y, a.z};
  }

  Models DualShock4::GetDeviceModel() const {
    switch (ds4_get_model(impl->handle)) {
      case DS4_ORIGNAL:
        return Models::Orignal;
      case DS4_SLIM:
      case DS4_PRO:
        return Models::Slim_Pro;
      default:
        return Models::None;
    }
  }

  void DualShock4::SetLed(const uint8_t r, const uint8_t g, const uint8_t b) const {
    ds4_set_led(&impl->output, r, g, b);
  }

  void DualShock4::EnableFlash(const bool enabled) {
    impl->flash_enabled = enabled;
    ds4_enable_flash(&impl->output, enabled ? 255 : 0, enabled ? 255 : 0,
                     enabled);
  }

  bool DualShock4::IsFlashEnabled() const { return impl->flash_enabled; }

  void DualShock4::SetFlash(const uint8_t FlashDurationOn, const uint8_t FlashDurationOff) const {
    ds4_enable_flash(&impl->output, (FlashDurationOn), FlashDurationOff, true);
  }

  bool DualShock4::SendCommandBuffer() {
    if (!ds4_send_commands(impl->handle, &impl->output))
      return false;
    return true;
  }

  bool DualShock4::IsButtonPressed(ControllerButton Button) {
    return ds4_button_pressed(&impl->state, static_cast<DS4_Buttons>(Button));
  }

  bool DualShock4::AreButtonsPressed(std::vector<ControllerButton> &Buttons) {
    for (ControllerButton _button: Buttons) {
      DS4_Buttons b = static_cast<DS4_Buttons>(_button);
      switch (b) {
        case DS_BTN_Square:
        case DS_BTN_Cross:
        case DS_BTN_Circle:
        case DS_BTN_Triangle:
          if (!(impl->state.faceButtons & b))
            return false;
          break;

        case DS_BTN_L1:
          if (!impl->state.L1)
            return false;
          break;
        case DS_BTN_R1:
          if (!impl->state.R1)
            return false;
          break;
        case DS_BTN_L2:
          if (!impl->state.L2)
            return false;
          break;
        case DS_BTN_R2:
          if (!impl->state.R2)
            return false;
          break;
        case DS_BTN_Share:
          if (!impl->state.Share)
            return false;
          break;
        case DS_BTN_Option:
          if (!impl->state.Option)
            return false;
          break;
        case DS_BTN_L3:
          if (!impl->state.L3)
            return false;
          break;
        case DS_BTN_R3:
          if (!impl->state.R3)
            return false;
          break;
        case DS_BTN_TouchPad:
          if (!impl->state.TouchPad_click)
            return false;
          break;
        case DS_DPAD_NORTH:
          if (impl->state.dpad_state != DS_DPAD_NORTH)
            return false;
          break;
        case DS_DPAD_NORTH_EAST:
          if (impl->state.dpad_state != DS_DPAD_NORTH_EAST)
            return false;
          break;
        case DS_DPAD_EAST:
          if (impl->state.dpad_state != DS_DPAD_EAST)
            return false;
          break;
        case DS_DPAD_SOUTH_EAST:
          if (impl->state.dpad_state != DS_DPAD_SOUTH_EAST)
            return false;
          break;
        case DS_DPAD_SOUTH:
          if (impl->state.dpad_state != DS_DPAD_SOUTH)
            return false;
          break;
        case DS_DPAD_SOUTH_WEST:
          if (impl->state.dpad_state != DS_DPAD_SOUTH_WEST)
            return false;
          break;
        case DS_DPAD_WEST:
          if (impl->state.dpad_state != DS_DPAD_WEST)
            return false;
          break;
        case DS_DPAD_NORTH_WEST:
          if (impl->state.dpad_state != DS_DPAD_NORTH_WEST)
            return false;
          break;
        case DS_BTN_None:
          return false;
      }
    }

    return true;
  }

  void DualShock4::Update() {
    if (IsTimeEnd())
      EndRumble();

    impl->state = ds4_update(impl->handle);
  }

  bool DualShock4::IsTimeEnd() {
    return impl->clock_end <= std::chrono::high_resolution_clock::now();
  }
} // namespace DS4
