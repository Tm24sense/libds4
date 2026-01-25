#pragma once
#include <array>

namespace DS4
{

    struct TouchPoint
    {
        uint8_t id;
        bool active;
        uint16_t x;
        uint16_t y;
    };

    struct TouchPadState
    {
        std::array<TouchPoint, 2> States;
    }
}