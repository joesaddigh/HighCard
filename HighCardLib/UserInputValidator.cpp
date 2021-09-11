#include <algorithm>

#include "HighCardLib/UserInputValidator.hpp"
#include "UtilsLib/StringUtils.hpp"

namespace highcardlib
{
    bool UserInputValidator::isNumber(const std::string& str)
    {
        return !str.empty() && std::find_if(str.begin(), str.end(), [](unsigned char c) {
            return !std::isdigit(c);
        }) == str.end();
    }

    bool UserInputValidator::isNumberWithinRange(const std::string& str, int min, int max)
    {
        auto numberWithinRange = bool{};
        if (UserInputValidator::isNumber(str))
        {
            auto number = std::stoi(str);
            numberWithinRange = number >= min && number <= max;
        }
        return numberWithinRange;
    }

    bool UserInputValidator::validateYesNo(const std::string& yesNo)
    {
        auto upper = utilslib::StringUtils::toUpper(yesNo);
        return upper == "Y" || upper == "N";
    }

    bool UserInputValidator::yesNoToBool(const std::string& yesNo)
    {
        auto upper = utilslib::StringUtils::toUpper(yesNo);
        return upper == "Y";
    }
}
