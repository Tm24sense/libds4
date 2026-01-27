#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ds4_handle ds4_handle;

ds4_handle* ds4_open_device(void);
void ds4_destroy_handle(ds4_handle* handle);

#ifdef __cplusplus
}
#endif
