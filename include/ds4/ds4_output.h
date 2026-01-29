#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "ds4/ds4_export.h"
#include "ds4/ds4_handle.h"
#define DS4_OUTPUT_REPORT_SIZE 32

typedef struct ds4_output_report {
    uint8_t report[32];
} ds4_output_report;

typedef struct ds4_message {
    ds4_output_report hid_report;
} ds4_message;

DS4_API ds4_output_report ds4_create_oreport(void);

DS4_API ds4_message ds4_begin_message(void);

DS4_API void ds4_set_vibration(ds4_message *, uint8_t right_motor, uint8_t left_motor);

DS4_API void ds4_set_led(ds4_message *, uint8_t r, uint8_t g, uint8_t b);

DS4_API void ds4_enable_flash(ds4_message *, uint8_t flash_on, uint8_t flash_off, bool on);

DS4_API int ds4_send_commands(ds4_handle *dev, ds4_message *msg);
