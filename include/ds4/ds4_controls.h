#pragma once
#include <stdint.h>

typedef struct ds4_state ds4_state;

#define DS4_SQUARE (1 << 4)   // 16
#define DS4_CROSS (1 << 5)    // 32
#define DS4_CIRCLE (1 << 6)   // 64
#define DS4_TRIANGLE (1 << 7) // 128
typedef enum _DS4_Buttons
{
    DS_DPAD_NORTH,
    DS_DPAD_NORTH_EAST,
    DS_DPAD_EAST,
    DS_DPAD_SOUTH_EAST,
    DS_DPAD_SOUTH,
    DS_DPAD_SOUTH_WEST,
    DS_DPAD_WEST,
    DS_DPAD_NORTH_WEST,
    DS_BTN_None,
    DS_BTN_Square = DS4_SQUARE,
    DS_BTN_Cross = DS4_CROSS,
    DS_BTN_Circle = DS4_CIRCLE,
    DS_BTN_Triangle = DS4_TRIANGLE,
    DS_BTN_L1,
    DS_BTN_R1,
    DS_BTN_L2,
    DS_BTN_R2,
    DS_BTN_Share,
    DS_BTN_Option,
    DS_BTN_L3,
    DS_BTN_R3,
    DS_BTN_TouchPad

} DS4_Buttons;

typedef struct ds4_point
{
    uint8_t x, y;
} ds4_point;
typedef struct ds4_motion_t
{
    int16_t x, y, z;
} ds4_motion_t;

int ds4_button_pressed(ds4_state *state, DS4_Buttons btn);
int ds4_buttons_pressed(ds4_state *state, DS4_Buttons *buttons, int count);
ds4_motion_t ds4_gyro_query(ds4_state *state);
ds4_motion_t ds4_accel_query(ds4_state *state);
int ds4_headphones_present(ds4_state *state);
int ds4_microphone_present(ds4_state *state);
int ds4_btn_state(ds4_state *state);
uint8_t ds4_battery_level(ds4_state *state);
float ds4_battery_level_percentage(ds4_state *state);
uint8_t ds4_get_temperature(ds4_state *state);
ds4_point ds4_left_stick(ds4_state *state);
ds4_point ds4_right_stick(ds4_state *state);