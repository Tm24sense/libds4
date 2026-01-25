#pragma once
#include <array>

namespace DS4
{

    struct TouchPoint
    {
        int id;
        bool active;
        int x;
        int y;
    };

    struct TouchPadState
    {
        std::array<TouchPoint, 2> States;
    };
}