#pragma once
#include <stdbool.h>
#include <memory.h>
#include <stdint.h>
#include <libds4/ds4_models.h>

typedef struct ds4_handle ds4_handle;

#define DS4_REPORT_HEADER_INPUT 0x01
#define DS4_INPUT_REPORT_SIZE 64

typedef struct ds4_input_report
{
    uint8_t report[DS4_INPUT_REPORT_SIZE];

} ds4_input_report;

typedef enum DS4_DPAD
{
    DPAD_NORTH,
    DPAD_NORTH_EAST,
    DPAD_EAST,
    DPAD_SOUTH_EAST,
    DPAD_SOUTH,
    DPAD_SOUTH_WEST,
    DPAD_WEST,
    DPAD_NORTH_WEST,
    DPAD_NONE
} DS4_DPAD;





typedef struct ds4_state {
    uint8_t leftstickX;
    uint8_t leftstickY;
    uint8_t rightstickX;
    uint8_t rightstickY;

    DS4_DPAD dpad_state;// byte 5
    uint8_t faceButtons; // bits 4-7 of byte 5
    // Buttons from byte 6
    
    //byte 6
    bool L1, R1, L2, R2;
    bool Share, Option, L3, R3; // byte 6 bits


    //byte 7

    bool PS_Button, TouchPad_click;
    uint8_t packet_counter;

    uint8_t l2analog;
    uint8_t r2analog;

    uint8_t Temprature;

    uint8_t timestamp_low;
    uint8_t timestamp_mid;
    uint8_t timestamp_high;


    uint8_t battery_level;
    bool is_plugged;
    bool headphones;

    int16_t gyroX;
    int16_t gyroY;
    int16_t gyroZ; // add this later
    int16_t accelX;
    int16_t accelY;
    int16_t accelZ;
} ds4_state;

ds4_state ds4_update(ds4_handle* handle);

ds4_input_report ds4_read_ireport(ds4_handle *dev);

ds4_state ds4_parse_state(ds4_input_report *input);