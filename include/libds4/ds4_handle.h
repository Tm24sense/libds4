#pragma once
#include "ds4_identify.h"
#include "ds4_input.h"
#include "ds4_output.h"
#include <stdint.h>
#include <stdbool.h>
#include <hidapi/hidapi.h>

typedef struct ds4_handle
{
    hid_device *handle;
    int pid;
    wchar_t *serial_number;
    int vid;
    ds4_state prev_state;
    ds4_state current_state;
    ds4_input_report input_report;
    ds4_output_report output_report;
    ds4_device_type dev_type;

} ds4_handle;

ds4_handle *ds4_make_handle(void);
void ds4_destroy_handle(ds4_handle *handle);
