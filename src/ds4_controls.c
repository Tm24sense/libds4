#include <libds4/ds4_controls.h>
#include <libds4/ds4_input.h> // full ds4_state definition

int ds4_btn_pressed(ds4_state *state, DS4_Buttons btn)
{
    switch (btn)
    {
        case DS_BTN_Square:   return !!(state->faceButtons & DS4_SQUARE);
        case DS_BTN_Cross:    return !!(state->faceButtons & DS4_CROSS);
        case DS_BTN_Circle:   return !!(state->faceButtons & DS4_CIRCLE);
        case DS_BTN_Triangle: return !!(state->faceButtons & DS4_TRIANGLE);
        case DS_BTN_L1:       return state->L1;
        case DS_BTN_R1:       return state->R1;
        case DS_BTN_L2:       return state->L2;
        case DS_BTN_R2:       return state->R2;
        case DS_BTN_Share:    return state->Share;
        case DS_BTN_Option:   return state->Option;
        case DS_BTN_L3:       return state->L3;
        case DS_BTN_R3:       return state->R3;
        case DS_BTN_TouchPad: return state->TouchPad_click;
        default:              return 0;
    }
}


uint8_t ds4_get_temprature(ds4_state* state)
{

}

ds4_point ds4_left_stick(ds4_state* state)
{
    ds4_point coord;
    coord.x = state->leftstickX;
    coord.y = state->leftstickY;
    return coord;
    
}

ds4_point ds4_right_stick(ds4_state *state)
{
    ds4_point coord;
    coord.x = state->rightstickX;
    coord.y = state->rightstickY;
    return coord;
}
