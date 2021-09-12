#include "gtest/gtest.h"

#include "UtilsLib/RandomNumberGenerator.hpp"

namespace ul = utilslib;

namespace utilslibtests
{
	// Public function tests
	TEST(RandomNumberGeneratorTests, generateRandomNumber_withinSensibleRange_valueWithinRangeReturned)
	{
		// ARRANGE
		constexpr auto min = 100;
		constexpr auto max = 20000;

		// ACT
		auto randomNumber = ul::RandomNumberGenerator::generateRandomNumber(min, max);

		// ASSERT
		ASSERT_TRUE(randomNumber >= min && randomNumber <= max);
	}

	TEST(RandomNumberGeneratorTests, generateRandomNumber_badRange_zeroReturned)
	{
		// ARRANGE
		constexpr auto min = 20000;
		constexpr auto max = 100;

		// ACT
		auto randomNumber = ul::RandomNumberGenerator::generateRandomNumber(min, max);

		// ASSERT
		ASSERT_EQ(randomNumber, 0);
	}

	TEST(RandomNumberGeneratorTests, generateRandomNumber_zeroRange_zeroReturned)
	{
		// ARRANGE
		constexpr auto min = 0;
		constexpr auto max = 0;

		// ACT
		auto randomNumber = ul::RandomNumberGenerator::generateRandomNumber(min, max);

		// ASSERT
		ASSERT_EQ(randomNumber, 0);
	}
}
