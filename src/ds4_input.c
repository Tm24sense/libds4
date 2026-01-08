#include <libds4/ds4_input.h>
#include <libds4/ds4_handle.h>
ds4_input_report ds4_read_ireport(ds4_handle *dev)
{
    ds4_input_report _rep;
    hid_read(dev->handle, _rep.report, DS4_INPUT_REPORT_SIZE);
    return _rep;
}
ds4_state ds4_input_poll(ds4_handle *handle)
{
    ds4_input_report input_report = ds4_read_ireport(handle);
    ds4_state state = ds4_parse_state(&input_report);
    return state;
}
ds4_state ds4_parse_state(ds4_input_report *input)
{
    ds4_state state;
    state.leftstickX = input->report[1];
    state.leftstickY = input->report[2];
    state.rightstickX = input->report[3];
    state.rightstickY = input->report[4];
    state.dpad_state = (DS4_DPAD)input->report[5] & 0x0F;
    state.faceButtons = input->report[5] & 0xF0;
    uint8_t various = input->report[6];
    // byte 6
    state.L1 = various & 0x01;
    state.R1 = various & 0x02;
    state.L2 = various & 0x04;
    state.R2 = various & 0x08;
    state.Share = various & 0x10;
    state.Option = various & 0x20;
    state.L3 = various & 0x40;
    state.R3 = various & 0x80;

    // byte 7
    state.PS_Button = input->report[7] & 0x01;
    state.TouchPad_click = input->report[7] & 0x02;
    state.packet_counter = input->report[7] & 0x3F;

    // byte 8
    state.l2analog = input->report[8];
    state.r2analog = input->report[9];

    state.Temprature = input->report[12];

    state.battery_level = input->report[30] & 0x0F;
    state.is_plugged = input->report[30] & 0x10;
    state.headphones = input->report[30] & 0x20;

    return state;
}
