#include "PRNG.h"
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <windows.h>
#include <tlhelp32.h>

float PRNG::getRandomNumber()
{
    const std::vector<uint64_t> entropySources = gatherEntropy();
    const uint64_t hash = hashEntropy(entropySources);

    return static_cast<float>(hash) / static_cast<float>(UINT64_MAX);
}

std::vector<uint64_t> PRNG::gatherEntropy() const
{
    std::vector<uint64_t> entropySources(numEntropySources);

    entropySources[0] = getSystemTime();
    entropySources[1] = getProcessID();
    entropySources[2] = getRAMUsage();
    entropySources[3] = getSystemUptime();
    entropySources[4] = getThreadID();
    entropySources[5] = getStackPointer();

    return entropySources;
}

uint64_t PRNG::getSystemTime() const
{
    return static_cast<uint64_t>(std::chrono::system_clock::now().time_since_epoch().count());
}

uint64_t PRNG::getProcessID() const
{
    return static_cast<uint64_t>(getpid());
}

uint64_t PRNG::getRAMUsage() const
{
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);

    if (GlobalMemoryStatusEx(&memoryStatus))
    {
        ULONGLONG totalPhysicalMemory = memoryStatus.ullTotalPhys;
        ULONGLONG availablePhysicalMemory = memoryStatus.ullAvailPhys;
        double ramUsage = (1.0 - static_cast<double>(availablePhysicalMemory) / totalPhysicalMemory) * 1'000'000;

        return static_cast<uint64_t>(ramUsage);
    }
    else
    {
        return 0;
    }
}

uint64_t PRNG::getSystemUptime() const
{
    return static_cast<uint64_t>(GetTickCount64());
}

uint64_t PRNG::getThreadID() const
{
    return static_cast<uint64_t>(GetCurrentThreadId());
}

uint64_t PRNG::getStackPointer() const
{
    uint64_t stackPtr;
    asm volatile("movq %%rsp, %0" : "=r"(stackPtr));

    return stackPtr;
}

uint64_t PRNG::hashEntropy(const std::vector<uint64_t> &entropySources) const
{
    uint64_t hash = 0;

    for (const auto &source : entropySources)
    {
        hash ^= source + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    }

    return hash;
}