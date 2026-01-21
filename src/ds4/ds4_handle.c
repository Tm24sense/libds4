#include <stdlib.h>
#include <wchar.h>
#include <stdio.h>
#include <ds4/hidapi_macro.h>
#include <ds4/ds4_handle.h>

ds4_handle *ds4_open_device(void)
{
    int PID = ds4_scan_devices();
    if (PID == 0)
    {
        return NULL;
    }

    wchar_t wstr[512];
    hid_device *dev = hid_open(SONY_VENDOR_ID, PID, NULL);
    if (!dev)
    {
        return NULL;
    }

    hid_get_serial_number_string(dev, wstr, 512);

    ds4_handle *handle = malloc(sizeof(ds4_handle));
    if (!handle)
    {
        hid_close(dev);
        return NULL;
    }

    handle->handle = dev;
    handle->pid = PID;
    handle->serial_number = wcsdup(wstr);
    handle->vid = SONY_VENDOR_ID;
    handle->dev_type = pid_to_ds4_model(PID);

    return handle;
}

void ds4_destroy_handle(ds4_handle *handle)
{
    if (!handle)
    {
        return;
    }
    hid_close(handle->handle);
    free(handle->serial_number);
    free(handle);
}
