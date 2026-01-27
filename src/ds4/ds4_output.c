#include <string.h>
#include "ds4/ds4_output.h"
#include "ds4/ds4_handle.h"
#include "ds4/ds4_private.h"
#include <hidapi/hidapi.h>

ds4_output_report ds4_create_oreport(void) {
    ds4_output_report r;
    memset(r.report, 0, 32);
    r.report[0] = 0x05; // Report header
    r.report[1] = 0x07; // Flags
    return r;
}

ds4_message ds4_begin_message(void) {
    ds4_message msg = { .hid_report = ds4_create_oreport() };
    return msg;
}

void ds4_set_vibration(ds4_message* msg, uint8_t right, uint8_t left) {
    msg->hid_report.report[4] = right;
    msg->hid_report.report[5] = left;
}

void ds4_set_led(ds4_message* msg, uint8_t r, uint8_t g, uint8_t b) {
    msg->hid_report.report[6] = r;
    msg->hid_report.report[7] = g;
    msg->hid_report.report[8] = b;
}

void ds4_enable_flash(ds4_message* msg, uint8_t flash_on, uint8_t flash_off, bool on) {
    if (on) {
        msg->hid_report.report[9] = flash_on;
        msg->hid_report.report[10] = flash_off;
    } else {
        msg->hid_report.report[9] = 0;
        msg->hid_report.report[10] = 0;
    }
}

int ds4_send_commands(ds4_handle* dev, ds4_message* msg) {
    int res = hid_write(dev->handle, msg->hid_report.report, 32);
    return res >= 0 ? 1 : 0;
}
