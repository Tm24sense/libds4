#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <ds4/ds4_export.h>

typedef struct ds4_handle ds4_handle;

DS4_API ds4_handle* ds4_open_device(void);
DS4_API void ds4_destroy_handle(ds4_handle* handle);

#ifdef __cplusplus
}
#endif
