#pragma once
#include "ds4_models.h"
#include <ds4/ds4_export.h>

typedef struct ds4_handle ds4_handle;

#define SONY_VENDOR_ID 0x054C
#define DS4_DEVICE_NONE 0x00 
#define DS4_ORIGNAL_PID 0x05C4
#define DS4_SLIM_PID 0x09CC
DS4_API ds4_device_type ds4_get_model(ds4_handle* device);

DS4_API ds4_device_type pid_to_ds4_model(unsigned short pid);
DS4_API int ds4_scan_devices(void);



