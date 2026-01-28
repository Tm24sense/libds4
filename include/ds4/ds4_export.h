#pragma once

#ifdef DS4_BUILD_DLL
    #ifdef DS4_EXPORTS  // Define this when building the DLL
        #define DS4_API __declspec(dllexport)
    #else
        #define DS4_API __declspec(dllimport)
    #endif
#else
    #define DS4_API  // Empty for static library
#endif