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

    bool UserInputValidator::validateSuitPrecedence(const utilslib::StringUtils::StringSplit& suits)
    {
        auto valid = bool{};
        if (suits.size() == 4)
        {
            auto findSuit = [&](const std::string& suitToFind) {
                auto find = std::find_if(std::begin(suits), std::end(suits), [&](const std::string& suit) {
                    return suit == suitToFind;
                });
                return find != suits.end();
            };

            valid =
                findSuit("C") &&
                findSuit("D") &&
                findSuit("H") &&
                findSuit("S");

        }
        return valid;
    }
}
