#include <sstream>
#include <algorithm>

#include "UtilsLib/StringUtils.hpp"

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
            result.push_back(substr);
        }
        return result;
    }

    std::string StringUtils::toUpper(const std::string& str)
    {
        auto upper = str;
        std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
        return upper;
    }
}
