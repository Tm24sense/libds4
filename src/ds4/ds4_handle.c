#include <stdlib.h>
#include <wchar.h>
#include <ds4/ds4_build_config.h>
#include "ds4/ds4_handle.h"
#include "ds4/ds4_private.h"
#include "ds4/ds4_identify.h"

DS4_API ds4_handle *ds4_open_device(void) {
    int pid = ds4_scan_devices();
    if (!pid) return NULL;
    wchar_t serial[512];
    hid_device *dev = hid_open(SONY_VENDOR_ID, pid, NULL);
    if (!dev) return NULL;

    hid_get_serial_number_string(dev, serial, 512);

    ds4_handle *handle = malloc(sizeof(ds4_handle));
    if (!handle) {
        hid_close(dev);
        return NULL;
    }
    handle->handle = dev;
    handle->pid = pid;
    handle->serial_number = wcsdup(serial);
    handle->vid = SONY_VENDOR_ID;
    handle->dev_type = pid_to_ds4_model(pid);
    return handle;
}

DS4_API void ds4_destroy_handle(ds4_handle *handle) {
    if (!handle) return;
    hid_close(handle->handle);
    free(handle->serial_number);
    free(handle);
}
