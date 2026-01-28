#pragma once
#if defined(DS4_STATIC)
  #define DS4_API
#elif defined(_WIN32) || defined(__CYGWIN__)
  #ifdef DS4_BUILD_DLL
    #define DS4_API __declspec(dllexport)
  #else
    #define DS4_API __declspec(dllimport)
  #endif
#else
  #if __GNUC__ >= 4
    #define DS4_API __attribute__((visibility("default")))
  #else
    #define DS4_API
  #endif
#endif