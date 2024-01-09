#pragma once

#include <stdint.h>

typedef uint64_t u64;
typedef double f64;

#include <intrin.h>
#include <windows.h>

inline u64 get_os_timer_freq() {
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    return freq.QuadPart;
}

inline u64 read_os_timer() {
    LARGE_INTEGER value;
    QueryPerformanceCounter(&value);
    return value.QuadPart;
}

inline u64 read_cpu_timer() {
    return __rdtsc();
}

inline u64 guess_cpu_frequency(u64 milliseconds_to_wait = 1000) {
    u64 os_freq = get_os_timer_freq();
    u64 cpu_start = read_cpu_timer();
    u64 os_start = read_os_timer();
    u64 os_elapsed = 0;
    u64 os_wait_time = os_freq * milliseconds_to_wait / 1000;
    while (os_elapsed < os_wait_time)
    {
        u64 os_end = read_os_timer();
        os_elapsed = os_end - os_start;
    }

    u64 cpu_end = read_cpu_timer();
    u64 cpu_elapsed = cpu_end - cpu_start;

    if (!os_elapsed)
        return 0;

    return os_freq * cpu_elapsed / os_elapsed;
}