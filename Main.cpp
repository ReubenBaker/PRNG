#include "PRNG.h"
#include <iostream>
#include <chrono>
#include <random>

int main()
{
    auto startPRNG = std::chrono::high_resolution_clock::now();
    PRNG prng;

    for (int i = 0; i < 1'000'000; i++)
    {
        float randomNumber = prng.getRandomNumber();

        if (i == 0)
        {
            std::cout << "PRNG: " << randomNumber << std::endl;
        }
    }

    auto endPRNG = std::chrono::high_resolution_clock::now();
    auto durationPRNG = std::chrono::duration_cast<std::chrono::milliseconds>(endPRNG - startPRNG);

    std::cout << "Time taken by PRNG: " << durationPRNG.count() << " milliseconds" << std::endl;

    auto startStdPRNG = std::chrono::high_resolution_clock::now();
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    for (int i = 0; i < 1'000'000; i++)
    {
        float randomNumber = dist(mt);

        if (i == 0)
        {
            std::cout << "Standard PRNG: " << randomNumber << std::endl;
        }
    }

    auto endStdPRNG = std::chrono::high_resolution_clock::now();
    auto durationStdPRNG = std::chrono::duration_cast<std::chrono::milliseconds>(endStdPRNG - startStdPRNG);

    std::cout << "Time taken by Standard PRNG: " << durationStdPRNG.count() << " milliseconds" << std::endl;

    return 0;
}