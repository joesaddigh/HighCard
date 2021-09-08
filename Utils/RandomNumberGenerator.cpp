#include <random>

#include "UtilsLib/RandomNumberGenerator.hpp"

namespace utilslib
{
    int RandomNumberGenerator::generateRandomNumber(int min, int max)
    {
        std::random_device rd{};
        std::default_random_engine eng(rd());
        std::uniform_int_distribution<int> distr(min, max);
        return distr(eng);
    }
}
