#pragma once

/* DS4_API: portable symbol export/import macro
 * - When building the ds4 shared library, define DS4_BUILD_DLL so
 *   exported symbols use __declspec(dllexport) on Windows.
 * - Consumers linking against the DLL will get __declspec(dllimport).
 */
#if defined(_WIN32) || defined(__CYGWIN__)
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
