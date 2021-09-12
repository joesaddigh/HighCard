#include <sstream>
#include <algorithm>

#include "UtilsLib/StringUtils.hpp"

namespace
{
    // trim from start (in place)
    static inline void ltrim(std::string& s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
    }

    // trim from end (in place)
    static inline void rtrim(std::string& s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }
}

namespace utilslib
{
    StringUtils::StringSplit StringUtils::splitString(const std::string& str, char delimeter)
    {
        auto result = std::vector<std::string>{};
        std::stringstream ss(str);
        while (ss.good())
        {
            std::string substr;
            getline(ss, substr, delimeter);
            if (!substr.empty())
            {
                result.push_back(substr);
            }
        }
        return result;
    }

    std::string StringUtils::toUpper(const std::string& str)
    {
        auto upper = str;
        std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
        return upper;
    }

    void StringUtils::trimString(std::string& str)
    {
        ltrim(str);
        rtrim(str);
    }
}
