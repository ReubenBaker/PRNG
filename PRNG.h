#ifndef PRNG_H
#define PRNG_H

#include <cstdint>
#include <vector>

class PRNG
{
public:
    PRNG();
    uint32_t getRandomNumber();

private:
    uint32_t gatherEntropy();
    uint32_t hashEntropy(const std::vector<uint32_t> &entropySources);
};

#endif // PRNG_H