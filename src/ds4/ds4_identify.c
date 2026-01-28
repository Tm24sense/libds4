#include <stdio.h>
#include <hidapi.h>
#include <ds4/ds4_identify.h>
#include <ds4/ds4_private.h>

DS4_API ds4_device_type pid_to_ds4_model(unsigned short pid)
{
    switch (pid) {
    case DS4_ORIGNAL_PID:
        return DS4_ORIGNAL;
    case DS4_SLIM_PID:
        return DS4_SLIM;
    default:
        return DS4_NONE;
    }
}

DS4_API ds4_device_type ds4_get_model(ds4_handle *device)
{
    return device->dev_type;
}

DS4_API int ds4_scan_devices(void)
{
    hid_init();
    unsigned short pids[] = {DS4_ORIGNAL_PID, DS4_SLIM_PID};
    struct hid_device_info *curr_dev;

    for (size_t i = 0; i < 2; i++) {
        curr_dev = hid_enumerate(SONY_VENDOR_ID, pids[i]);
        if (curr_dev) {
            hid_free_enumeration(curr_dev);
            return pids[i];
        }
    }
    return DS4_NONE;
}