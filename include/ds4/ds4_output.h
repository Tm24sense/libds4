#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "ds4/ds4_handle.h"

typedef struct ds4_output_report {
    uint8_t report[32];
} ds4_output_report;

typedef struct ds4_message {
    ds4_output_report hid_report;
} ds4_message;

ds4_output_report ds4_create_oreport(void);
ds4_message ds4_begin_message(void);
void ds4_set_vibration(ds4_message*, uint8_t right_motor, uint8_t left_motor);
void ds4_set_led(ds4_message*, uint8_t r, uint8_t g, uint8_t b);
void ds4_enable_flash(ds4_message*, uint8_t flash_on, uint8_t flash_off, bool on);
int ds4_send_commands(ds4_handle* dev, ds4_message* msg);
