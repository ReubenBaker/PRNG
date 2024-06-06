#ifndef PRNG_H
#define PRNG_H

#include <cstdint>
#include <vector>
#include <string>

class PRNG
{
public:
    float getRandomNumber();

private:
    static const int numEntropySources = 8;

    std::vector<uint64_t> gatherEntropy() const;
    uint64_t getSystemTime() const;
    uint64_t getProcessID() const;
    uint64_t getRAMUsage() const;
    uint64_t getSystemUptime() const;
    uint64_t getThreadID() const;
    uint64_t getStackPointer() const;
    uint64_t hashEntropy(const std::vector<uint64_t> &entropySources) const;
};

#endif // PRNG_H