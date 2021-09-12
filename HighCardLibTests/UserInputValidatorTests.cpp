#include "gtest/gtest.h"

#include "HighCardLib/UserInputValidator.hpp"

namespace hc = highcardlib;

namespace highcardlibtests
{	
	// Public function tests
	TEST(UserInputValidatorTests, isNumber_withNumber_returnsTrue)
	{
		// ARRANGE
		constexpr auto str = "13423432";

		// ACT
		auto result = hc::UserInputValidator::isNumber(str);

		// ASSERT
		ASSERT_TRUE(result);
	}

	TEST(UserInputValidatorTests, isNumber_withEmptyString_returnsFalse)
	{
		// ARRANGE
		constexpr auto str = "";

		// ACT
		auto result = hc::UserInputValidator::isNumber(str);

		// ASSERT
		ASSERT_FALSE(result);
	}

	TEST(UserInputValidatorTests, isNumber_withAlphaString_returnsFalse)
	{
		// ARRANGE
		constexpr auto str = "Hello. This is def not a number";

		// ACT
		auto result = hc::UserInputValidator::isNumber(str);

		// ASSERT
		ASSERT_FALSE(result);
	}

	TEST(UserInputValidatorTests, isNumberWithinRange_withAlphaString_returnsFalse)
	{
		// ARRANGE
		constexpr auto str = "Hello. This is def not a number";
		constexpr auto min = 2;
		constexpr auto max = 5666;

		// ACT
		auto result = hc::UserInputValidator::isNumberWithinRange(str, min, max);

		// ASSERT
		ASSERT_FALSE(result);
	}

	TEST(UserInputValidatorTests, isNumber_withNumberOutsideOfRange_returnsFalse)
	{
		// ARRANGE
		constexpr auto str = "1";
		constexpr auto min = 2;
		constexpr auto max = 5666;

		// ACT
		auto result = hc::UserInputValidator::isNumberWithinRange(str, min, max);

		// ASSERT
		ASSERT_FALSE(result);
	}

	TEST(UserInputValidatorTests, isNumber_withNumberMinRange_returnsTrue)
	{
		// ARRANGE
		constexpr auto str = "2";
		constexpr auto min = 2;
		constexpr auto max = 5666;

		// ACT
		auto result = hc::UserInputValidator::isNumberWithinRange(str, min, max);

		// ASSERT
		ASSERT_TRUE(result);
	}

	TEST(UserInputValidatorTests, isNumber_withNumberMaxRange_returnsTrue)
	{
		// ARRANGE
		constexpr auto str = "5666";
		constexpr auto min = 2;
		constexpr auto max = 5666;

		// ACT
		auto result = hc::UserInputValidator::isNumberWithinRange(str, min, max);

		// ASSERT
		ASSERT_TRUE(result);
	}

	TEST(UserInputValidatorTests, isNumber_withNumberWithinRange_returnsTrue)
	{
		// ARRANGE
		constexpr auto str = "444";
		constexpr auto min = 2;
		constexpr auto max = 5666;

		// ACT
		auto result = hc::UserInputValidator::isNumberWithinRange(str, min, max);

		// ASSERT
		ASSERT_TRUE(result);
	}

	TEST(UserInputValidatorTests, validateYesNo_withYLower_returnsTrue)
	{
		// ARRANGE
		constexpr auto str = "y";

		// ACT
		auto result = hc::UserInputValidator::validateYesNo(str);

		// ASSERT
		ASSERT_TRUE(result);
	}

	TEST(UserInputValidatorTests, validateYesNo_withYUpper_returnsTrue)
	{
		// ARRANGE
		constexpr auto str = "Y";

		// ACT
		auto result = hc::UserInputValidator::validateYesNo(str);

		// ASSERT
		ASSERT_TRUE(result);
	}

	TEST(UserInputValidatorTests, validateYesNo_withNLower_returnsTrue)
	{
		// ARRANGE
		constexpr auto str = "n";

		// ACT
		auto result = hc::UserInputValidator::validateYesNo(str);

		// ASSERT
		ASSERT_TRUE(result);
	}

	TEST(UserInputValidatorTests, validateYesNo_withNUpper_returnsTrue)
	{
		// ARRANGE
		constexpr auto str = "N";

		// ACT
		auto result = hc::UserInputValidator::validateYesNo(str);

		// ASSERT
		ASSERT_TRUE(result);
	}

	TEST(UserInputValidatorTests, validateYesNo_withRandomCharacter_returnsFalse)
	{
		// ARRANGE
		constexpr auto str = "afsa";

		// ACT
		auto result = hc::UserInputValidator::validateYesNo(str);

		// ASSERT
		ASSERT_FALSE(result);
	}

	TEST(UserInputValidatorTests, yesNoToBool_withYLower_returnsTrue)
	{
		// ARRANGE
		constexpr auto str = "y";

		// ACT
		auto result = hc::UserInputValidator::yesNoToBool(str);

		// ASSERT
		ASSERT_TRUE(result);
	}

	TEST(UserInputValidatorTests, yesNoToBool_withYUpper_returnsTrue)
	{
		// ARRANGE
		constexpr auto str = "Y";

		// ACT
		auto result = hc::UserInputValidator::yesNoToBool(str);

		// ASSERT
		ASSERT_TRUE(result);
	}

	TEST(UserInputValidatorTests, yesNoToBool_withNLower_returnsFalse)
	{
		// ARRANGE
		constexpr auto str = "n";

		// ACT
		auto result = hc::UserInputValidator::yesNoToBool(str);

		// ASSERT
		ASSERT_FALSE(result);
	}

	TEST(UserInputValidatorTests, yesNoToBool_withNUpper_returnsFalse)
	{
		// ARRANGE
		constexpr auto str = "N";

		// ACT
		auto result = hc::UserInputValidator::yesNoToBool(str);

		// ASSERT
		ASSERT_FALSE(result);
	}

	TEST(UserInputValidatorTests, yesNoToBool_withRandomCharacter_returnsFalse)
	{
		// ARRANGE
		constexpr auto str = "afsa";

		// ACT
		auto result = hc::UserInputValidator::yesNoToBool(str);

		// ASSERT
		ASSERT_FALSE(result);
	}

	TEST(UserInputValidatorTests, validateSuitPrecedence_withAllSuits_returnsTrue)
	{
		// ARRANGE
		auto suits = utilslib::StringUtils::StringSplit{
			"C", "D", "H", "S"
		};

		// ACT
		auto result = hc::UserInputValidator::validateSuitPrecedence(suits);

		// ASSERT
		ASSERT_TRUE(result);
	}

	TEST(UserInputValidatorTests, validateSuitPrecedence_withInsufficientSuits_returnsFalse)
	{
		// ARRANGE
		auto suits = utilslib::StringUtils::StringSplit{
			"C", "D", "H"
		};

		// ACT
		auto result = hc::UserInputValidator::validateSuitPrecedence(suits);

		// ASSERT
		ASSERT_FALSE(result);
	}

	TEST(UserInputValidatorTests, validateSuitPrecedence_withRepeatedSuits_returnsFalse)
	{
		// ARRANGE
		auto suits = utilslib::StringUtils::StringSplit{
			"C", "D", "H", "H"
		};

		// ACT
		auto result = hc::UserInputValidator::validateSuitPrecedence(suits);

		// ASSERT
		ASSERT_FALSE(result);
	}
}
