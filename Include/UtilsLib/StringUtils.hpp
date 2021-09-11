#pragma once

#include <string>
#include <vector>

namespace utilslib
{
    class StringUtils
    {
    public:

        using StringSplit = std::vector<std::string>;

        StringUtils() = delete;
        ~StringUtils() = delete;

        static StringSplit splitString(const std::string& str, char delimeter);
        static std::string toUpper(const std::string& str);
    };
}
