#pragma once
#include <ds4/ds4_build_config.h>
#include <ds4/ds4_models.h>
#include <ds4/ds4_input.h>
#include <ds4/ds4_output.h>

struct ds4_handle {
    hid_device *handle;
    int pid;
    wchar_t *serial_number;
    int vid;
    ds4_device_type dev_type;
    ds4_state prev_state;
    ds4_state current_state;
    ds4_input_report input_report;
    ds4_output_report output_report;
};
