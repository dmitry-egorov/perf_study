#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint64_t u64;
typedef double f64;

#if _WIN32

#include <intrin.h>
#include <windows.h>

static u64 get_os_timer_freq(void)
{
	LARGE_INTEGER Freq;
	QueryPerformanceFrequency(&Freq);
	return Freq.QuadPart;
}

static u64 read_os_timer(void)
{
	LARGE_INTEGER Value;
	QueryPerformanceCounter(&Value);
	return Value.QuadPart;
}

#else

#include <x86intrin.h>
#include <sys/time.h>

static u64 GetOSTimerFreq(void)
{
	return 1000000;
}

static u64 ReadOSTimer(void)
{
	struct timeval Value;
	gettimeofday(&Value, 0);

	u64 Result = GetOSTimerFreq() * (u64)Value.tv_sec + (u64)Value.tv_usec;
	return Result;
}

#endif

inline u64 read_cpu_timer(void)
{
	return __rdtsc();
}

int main(int ArgCount, char** Args)
{
	u64 MillisecondsToWait = 1000;
	if (ArgCount == 2)
	{
		MillisecondsToWait = atol(Args[1]);
	}

	u64 OSFreq = get_os_timer_freq();
	printf("    OS Freq: %llu (reported)\n", OSFreq);

	u64 CPUStart = read_cpu_timer();
	u64 OSStart = read_os_timer();
	u64 OSEnd = 0;
	u64 OSElapsed = 0;
	u64 OSWaitTime = OSFreq * MillisecondsToWait / 1000;
	while (OSElapsed < OSWaitTime)
	{
		OSEnd = read_os_timer();
		OSElapsed = OSEnd - OSStart;
	}

	u64 CPUEnd = read_cpu_timer();
	u64 CPUElapsed = CPUEnd - CPUStart;
	u64 CPUFreq = 0;
	if (OSElapsed)
	{
		CPUFreq = OSFreq * CPUElapsed / OSElapsed;
	}

	printf("   OS Timer: %llu -> %llu = %llu elapsed\n", OSStart, OSEnd, OSElapsed);
	printf(" OS Seconds: %.4f\n", (f64)OSElapsed / (f64)OSFreq);

	printf("  CPU Timer: %llu -> %llu = %llu elapsed\n", CPUStart, CPUEnd, CPUElapsed);
	printf("   CPU Freq: %llu (guessed)\n", CPUFreq);

	return 0;
}