#ifndef HIDAPI_MACRO_H
#define HIDAPI_MACRO_H

// If we are on Windows, we usually need the prefix
#if defined(_WIN32) || defined(_WIN64)
    #include <hidapi/hidapi.h>
#else
    // On Linux/macOS, the include path usually points 
    // directly to the header's folder
    #include <hidapi.h>
#endif

#endif