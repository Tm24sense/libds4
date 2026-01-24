#include <ds4/hidapi_macro.h>
#include <ds4/ds4_input.h>
#include <ds4/ds4_handle.h>
ds4_input_report ds4_read_ireport(ds4_handle *dev)
{
    ds4_input_report _rep;
    hid_read(dev->handle, _rep.report, DS4_INPUT_REPORT_SIZE);
    return _rep;
}

ds4_state ds4_update(ds4_handle *handle)
{
    ds4_input_report input_report = ds4_read_ireport(handle);
    ds4_state state = ds4_parse_state(&input_report);
    return state;
}

ds4_state ds4_parse_state(ds4_input_report *input)
{
    ds4_state state = {0};

    /* Left and right stick values */
    state.leftstickX = input->report[1];
    state.leftstickY = input->report[2];
    state.rightstickX = input->report[3];
    state.rightstickY = input->report[4];

    /* Byte 5: D-Pad and face buttons */
    state.dpad_state = (input->report[5] & 0x0F);
    state.faceButtons = input->report[5] & 0xF0;

    /* Byte 6: Trigger and button states */
    uint8_t various = input->report[6];
    state.L1 = various & 0x01;
    state.R1 = various & 0x02;
    state.L2 = various & 0x04;
    state.R2 = various & 0x08;
    state.Share = various & 0x10;
    state.Option = various & 0x20;
    state.L3 = various & 0x40;
    state.R3 = various & 0x80;

    /* Byte 7: PS button, touchpad, and packet counter */
    state.PS_Button = input->report[7] & 0x01;
    state.TouchPad_click = input->report[7] & 0x02;
    state.packet_counter = input->report[7] & 0x3F;

    /* Bytes 8-9: Analog trigger values */
    state.l2analog = input->report[8];
    state.r2analog = input->report[9];

    /* Byte 12: Temperature */
    state.Temprature = input->report[12];

    /* Byte 13-18 (Gyro)*/
    state.gyroX = (int16_t)(input->report[13] | (input->report[14] << 8));
    state.gyroY = (int16_t)(input->report[15] | (input->report[16] << 8));
    state.gyroZ = (int16_t)(input->report[17] | (input->report[18] << 8));

    state.accelX = (int16_t)(input->report[19] | (input->report[20] << 8));
    state.accelY = (int16_t)(input->report[21] | (input->report[22] << 8));
    state.accelZ = (int16_t)(input->report[23] | (input->report[24] << 8));

    /* Byte 30: Battery and status flags */

    state.microphone = input->report[30] & (1 << 6);
    state.battery_level = input->report[30] & 0x0F;
    state.is_plugged = input->report[30] & 0x10;
    state.headphones = input->report[30] & 0x20;

    // Touchpad data
    state.touchpad = parse_touchpad_data(input);
    return state;
}

Touchpad_t parse_touchpad_data(ds4_input_report *_R)
{
    Touchpad_t tp;

    tp.N1_touching = !(_R->report[35] & 0x80);
    
    tp.N1_id = _R->report[35] & 0x7F;

    
    tp.N1_pos_x = (uint16_t)_R->report[36] | (((uint16_t)_R->report[37] & 0x0F) << 8);
    
    tp.N1_pos_y = ((uint16_t)_R->report[37] >> 4) | ((uint16_t)_R->report[38] << 4);


    
    tp.N2_touching = !(_R->report[39] & 0x80);
    tp.N2_id = _R->report[39] & 0x7F;

    
    tp.N2_pos_x = (uint16_t)_R->report[40] | (((uint16_t)_R->report[41] & 0x0F) << 8);
    
    tp.N2_pos_y = ((uint16_t)_R->report[41] >> 4) | ((uint16_t)_R->report[42] << 4);

    return tp;
}
