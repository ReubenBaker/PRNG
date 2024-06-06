#ifndef PRNG_H
#define PRNG_H

#include <cstdint>
#include <vector>

class PRNG
{
public:
    uint32_t getRandomNumber();

private:
    static const int numEntropySources = 2;

    std::vector<uint32_t> gatherEntropy() const;
    uint32_t getSystemTime() const;
    uint32_t getProcessID() const;
    uint32_t hashEntropy(const std::vector<uint32_t> &entropySources) const;
};

#endif // PRNG_H