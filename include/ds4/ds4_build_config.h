#pragma once

#ifndef DS4_BUILD_CONFIG_H
#define DS4_BUILD_CONFIG_H

#ifdef USING_XMAKE
    #include <hidapi/hidapi.h>
#else
    #include <hidapi.h>
#endif

#endif // DS4_BUILD_CONFIG_H