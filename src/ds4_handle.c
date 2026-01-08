#include <libds4/ds4_handle.h>

#include <stdlib.h>
#include <wchar.h>
#include <stdio.h>
#include <hidapi/hidapi.h>

ds4_handle *ds4_make_handle(void)
{
    int PID = ds4_scan_devices();
    if (PID == 0)
    {
        printf("[ERROR] Could Not find a device please connnect the controller\n");
        return NULL;
    }
    wchar_t wstr[512];
    hid_device *dev = hid_open(SONY_VENDOR_ID, PID, NULL);
    hid_get_serial_number_string(dev, wstr, 512);

    ds4_handle *handle = malloc(sizeof(ds4_handle));
    if (!handle)
        return NULL;

    handle->handle = dev;
    handle->pid = PID;
    handle->serial_number = wcsdup(wstr);
    handle->vid = SONY_VENDOR_ID;
    handle->dev_type = pid_to_ds4_model(PID);

    return handle;
}

void ds4_destroy_handle(ds4_handle* handle)
{
    hid_close(handle->handle);
}

