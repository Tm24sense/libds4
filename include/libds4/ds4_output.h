#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <memory.h>

typedef struct ds4_handle ds4_handle;

#define DS4_REPORT_HEADER 0x05
#define DS4_OUTPUT_REPORT_SIZE 32

typedef struct ds4_output_report
{
    uint8_t report[DS4_OUTPUT_REPORT_SIZE];

} ds4_output_report;


typedef struct ds4_message
{
    ds4_output_report hid_report;

} ds4_message;
ds4_output_report ds4_create_oreport(void);

void ds4_enable_flash(ds4_message *out_report, uint8_t flash_on, uint8_t flash_off, bool on);
void ds4_set_vibration(ds4_message *_r, uint8_t right_motor, uint8_t left_motor);
ds4_message ds4_begin_message();
void ds4_send_commands(ds4_handle *dev, ds4_message *message);

void ds4_set_led(ds4_message *_r, int r, int g, int b);

void ds4_flush_report(ds4_handle *dev, ds4_message *data);
