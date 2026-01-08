#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <memory.h>

/* Forward declaration */
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

/**
 * DETAILED BUFFER BREAKDOWN (Report ID 0x05 - USB)
 * -------------------------------------------------------------------------
 * buf[0]  : REPORT ID
 * Value: 0x05. This identifies the packet as a standard USB output report.
 *
 * buf[1]  : MASK 1 (The "Enable" flags)
 * Bit 0 (0x01): Enable Rumble (Motors).
 * Bit 1 (0x02): Enable LED Lightbar color.
 * Bit 2 (0x04): Enable LED Blinking/Flashing.
 * Value: 0x07 (00000111) enables all three.
 *
 * buf[2]  : MASK 2
 * Reserved for other functions (Microphone/Speaker toggles). Usually 0x00.
 *
 * buf[3]  : AUDIO CONTROL
 * Controls volume for the built-in speaker. Keep 0x00 for now.
 *
 * buf[4]  : RIGHT MOTOR (Weak/Small Motor)
 * Range: 0 - 255. High frequency, "buzzing" feel.
 *
 * buf[5]  : LEFT MOTOR (Strong/Large Motor)
 * Range: 0 - 255. Low frequency, heavy "thumping" feel.
 *
 * buf[6]  : LED RED
 * Range: 0 - 255. Intensity of the Red LED.
 *
 * buf[7]  : LED GREEN
 * Range: 0 - 255. Intensity of the Green LED.
 *
 * buf[8]  : LED BLUE
 * Range: 0 - 255. Intensity of the Blue LED.
 *
 * buf[9]  : FLASH ON DURATION
 * Time the LED stays ON during a blink. (Unit: ~10ms. 255 = ~2.5s).
 *
 * buf[10] : FLASH OFF DURATION
 * Time the LED stays OFF during a blink. (Unit: ~10ms).
 *
 * buf[11..31] : PADDING / UNUSED
 * These bytes are reserved for additional features like gyro reset
 * or audio streaming data.
 */
