#include <libds4/ds4_output.h>
#include <libds4/ds4_handle.h>

ds4_output_report ds4_create_oreport()
{
    ds4_output_report _r;
    memset(_r.report, 0x00, (DS4_OUTPUT_REPORT_SIZE));
    // Report Id
    _r.report[0] = DS4_REPORT_HEADER;
    //(MASK 1)Flags to enable/disable eg(Vibration, flashing, etc)
    _r.report[1] = 0x07;
    //(Mask 2)Other functions i dont really know
    _r.report[2] = 0x00;
    // Audio control 0x00 for now
    _r.report[3] = 0x00;
    return _r;
}

void ds4_set_vibration(ds4_message *_r, uint8_t right_motor, uint8_t left_motor)
{
    _r->hid_report.report[4] = right_motor;
    _r->hid_report.report[5] = left_motor;
}

void ds4_set_led(ds4_message *_r, int r, int g, int b)
{
    //(Red) Led
    _r->hid_report.report[6] = r;
    _r->hid_report.report[7] = g;
    _r->hid_report.report[8] = b;
}
ds4_message ds4_begin_message()
{
    ds4_output_report report_begin = ds4_create_oreport();
    ds4_message _Message = {
        .hid_report = report_begin};
    return _Message;
}

void ds4_flush_report(ds4_handle *dev, ds4_message *data)
{
    int res = hid_write(dev->handle, data->hid_report.report, DS4_OUTPUT_REPORT_SIZE);
    if (res < 0)
    {
        wprintf(L"[ERROR] Failed to write to DS4 device\n");
    }
}
void ds4_send_commands(ds4_handle *dev, ds4_message *message)
{
    ds4_flush_report(dev, message);
}
void ds4_enable_flash(ds4_message *out_report, uint8_t flash_on, uint8_t flash_off, bool on)
{
    if (on)
    {
        out_report->hid_report.report[9] = flash_on;
        out_report->hid_report.report[10] = flash_off;
    }
    else
    {
        out_report->hid_report.report[9] = 0x00;
        out_report->hid_report.report[10] = 0x00;
    }
}
