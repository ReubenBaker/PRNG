#include "PRNG.h"
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <windows.h>

uint32_t PRNG::getRandomNumber()
{
    const std::vector<uint32_t> entropySources = gatherEntropy();
    const uint32_t hash = hashEntropy(entropySources);

    return hash;
}

std::vector<uint32_t> PRNG::gatherEntropy() const
{
    std::vector<uint32_t> entropySources(numEntropySources);

    entropySources[0] = getSystemTime();
    entropySources[1] = getProcessID();

    return entropySources;
}

uint32_t PRNG::getSystemTime() const
{
    // High-resolution time
    return static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count());
}

uint32_t PRNG::getProcessID() const
{
    // Current process ID
    return static_cast<uint32_t>(getpid());
}

uint32_t PRNG::hashEntropy(const std::vector<uint32_t> &entropySources) const
{
    uint32_t hash = 0;

    for (const auto &source : entropySources)
    {
        hash ^= source + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    }

    return hash;
}