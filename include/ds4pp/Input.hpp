#pragma once
#include <cstdint>



namespace DS4
{
enum class ControllerButton : uint16_t {
    
    DPadNorth,
    DPadNorthEast,
    DPadEast,
    DPadSouthEast,
    DPadSouth,
    DPadSouthWest,
    DPadWest,
    DPadNorthWest,
    None,
    Square     = 1 << 4,
    Cross      = 1 << 5,
    Circle     = 1 << 6,
    Triangle   = 1 << 7,
    L1,
    R1,
    L2,
    R2,
    Share,
    Options,
    L3,
    R3,
    Touchpad
};

enum class ControllerModel
{
    None,
    DS4_ORIGNAL,
    DS4_PRO,
};
}
