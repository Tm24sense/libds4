#ifndef DS4_EXPORT_H
#define DS4_EXPORT_H

#if defined(_WIN32) || defined(__CYGWIN__)
#ifdef DS4_BUILD_SHARED

#define DS4_API __declspec(dllexport)
#elif defined(DS4_STATIC)

#define DS4_API
#else

#define DS4_API __declspec(dllimport)
#endif
#else

#define DS4_API
#endif

#endif // DS4_EXPORT_H