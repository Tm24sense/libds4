#pragma once

#ifndef DS4_BUILD_CONFIG_H
#define DS4_BUILD_CONFIG_H

#ifdef USING_XMAKE
    #define HIDAPI_INCLUDE <hidapi/hidapi.h>
#else
    #define HIDAPI_INCLUDE <hidapi.h>
#endif

#endif // DS4_BUILD_CONFIG_H