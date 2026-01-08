#pragma once
#include "ds4_models.h"

#define SONY_VENDOR_ID 0x054C
#define DS4_DEVICE_NONE 0x00 
#define DS4_ORIGNAL_PID 0x05C4
#define DS4_SLIM_PID 0x09CC
#define DS4_PRO_PID 0x09CC

ds4_device_type pid_to_ds4_model(unsigned short pid);
int ds4_scan_devices(void);


