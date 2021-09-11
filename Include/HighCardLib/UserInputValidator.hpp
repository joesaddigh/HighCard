#pragma once

#include <string>

namespace highcardlib
{
    class UserInputValidator
    {
    public:

        UserInputValidator() = delete;
        ~UserInputValidator() = delete;

        static bool isNumber(const std::string& str);
        static bool isNumberWithinRange(const std::string& str, int min, int max);
        static bool validateYesNo(const std::string& yesNo);
        static bool yesNoToBool(const std::string& yesNo);
    };
}
