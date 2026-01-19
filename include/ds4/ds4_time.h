#include <stdint.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>

uint64_t getTimeMs() {
    return GetTickCount64();
}

#else
#include <time.h>
uint64_t getTimeMs() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000ULL + ts.tv_nsec / 1000000ULL;
}

#endif
