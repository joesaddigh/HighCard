#include "gtest/gtest.h"

#include "HighCardLib/Card.hpp"

namespace hc = highcardlib;

namespace highcardlibtests
{
	TEST(CardTests, constructor_noParams_cardIsUndefined)
	{
		// ARRANGE & ACT
		auto card = hc::Card{};

		// ASSERT
		ASSERT_EQ(card.getRank(), 0);
		ASSERT_EQ(card.getSuit(), hc::Card::Suit::undefined);
	}
}
