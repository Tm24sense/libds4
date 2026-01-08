#include <libds4/ds4_identify.h>
#include <hidapi/hidapi.h>
#include <stdio.h>

ds4_device_type pid_to_ds4_model(unsigned short pid)
{
    switch(pid)
    {
        case DS4_DEVICE_NONE: return DS4_NONE;
        case DS4_ORIGNAL_PID: return DS4_ORIGNAL;
        case DS4_SLIM_PID:     return DS4_SLIM;
    }
}

int ds4_scan_devices(void)
{
    hid_init();
    unsigned short pids[] = {DS4_ORIGNAL_PID, DS4_SLIM_PID, DS4_PRO_PID};
    struct hid_device_info *curr_dev;

    for (size_t i = 0; i < 3; i++)
    {
        curr_dev = hid_enumerate(SONY_VENDOR_ID, pids[i]);
        if (curr_dev)
        {
            hid_free_enumeration(curr_dev);
            return pids[i];
        }
    }
    return DS4_NONE;
}



