#include "gtest/gtest.h"

#include "UtilsLib/StringUtils.hpp"

namespace ul = utilslib;

namespace utilslibtests
{
	// Public function tests
	TEST(StringUtilsTests, splitString_withValuesToSplit_valuesSplit)
	{
		// ARRANGE
		constexpr auto str = "Fred,Bob,Steve";

		// ACT
		auto splitValues = ul::StringUtils::splitString(str, ',');

		// ASSERT
		ASSERT_EQ(splitValues.size(), 3);
	}

	TEST(StringUtilsTests, splitString_withEmptyString_splitEmpty)
	{
		// ARRANGE
		auto str = std::string{};
		
		// ACT
		auto splitValues = ul::StringUtils::splitString(str, ',');

		// ASSERT
		ASSERT_TRUE(splitValues.empty());
	}

	TEST(StringUtilsTests, splitString_withStringWithoutDelimiter_splitContainsFullString)
	{
		// ARRANGE
		constexpr auto str = "Fred,Bob,Steve";

		// ACT
		auto splitValues = ul::StringUtils::splitString(str, '-');

		// ASSERT
		ASSERT_EQ(splitValues.size(), 1);
		ASSERT_EQ(splitValues[0], str);
	}

	TEST(StringUtilsTests, toUpper_withLowerCaseString_convertedToUpper)
	{
		// ARRANGE
		constexpr auto str = "Fred,Bob,Steve";

		// ACT
		auto upperStr = ul::StringUtils::toUpper(str);

		// ASSERT
		ASSERT_EQ(upperStr, "FRED,BOB,STEVE");
	}

	TEST(StringUtilsTests, toUpper_withUpperCaseString_stringStaysTheSame)
	{
		// ARRANGE
		constexpr auto str = "FRED,BOB,STEVE";

		// ACT
		auto upperStr = ul::StringUtils::toUpper(str);

		// ASSERT
		ASSERT_EQ(upperStr, str);
	}

	TEST(StringUtilsTests, trimString_withSpaceL_spaceRemoved)
	{
		// ARRANGE
		auto str = std::string{ "    FRED   ,BOB,STEVE" };

		// ACT
		ul::StringUtils::trimString(str);

		// ASSERT
		ASSERT_EQ(str, "FRED   ,BOB,STEVE");
	}

	TEST(StringUtilsTests, trimString_withSpaceR_spaceRemoved)
	{
		// ARRANGE
		auto str = std::string{ "FRED,BOB,     S T E V E         " };

		// ACT
		ul::StringUtils::trimString(str);

		// ASSERT
		ASSERT_EQ(str, "FRED,BOB,     S T E V E");
	}

	TEST(StringUtilsTests, trimString_withSpaceLR_spaceRemoved)
	{
		// ARRANGE
		auto str = std::string{ "           FRED,BOB,     S T E V E         " };

		// ACT
		ul::StringUtils::trimString(str);

		// ASSERT
		ASSERT_EQ(str, "FRED,BOB,     S T E V E");
	}
}
