#pragma once

namespace utilslib
{
    class RandomNumberGenerator
    {
    public:
        RandomNumberGenerator() = delete;
        ~RandomNumberGenerator() = delete;

        static int generateRandomNumber(int min, int max);
    };
}
