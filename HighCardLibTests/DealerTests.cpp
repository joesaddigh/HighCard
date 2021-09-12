#include "gtest/gtest.h"

#include "HighCardLib/Dealer.hpp"

namespace hc = highcardlib;

namespace highcardlibtests
{
	// Constructor tests
	TEST(DealerTests, constructor_zeroCards_throws)
	{
		// ARRANGE, ACT & ASSERT
		ASSERT_THROW(
			hc::Dealer(1, 0, false),
			std::invalid_argument
		);
	}

	TEST(DealerTests, constructor_negativeCards_throws)
	{
		// ARRANGE, ACT & ASSERT
		ASSERT_THROW(
			hc::Dealer(1, -100, false),
			std::invalid_argument
		);
	}

	// Public function tests
	TEST(DealerTests, dealCard_returnsACard)
	{
		// ARRANGE 
		auto dealer = hc::Dealer(1, 13, false);

		// ACT
		auto card = dealer.dealCard();

		// ASSERT
		ASSERT_NE(card.getSuit(), hc::Card::Suit::undefined);
		ASSERT_NE(card.getRank(), 0);
	}

	TEST(DealerTests, dealCard_allCardsDealt_packShuffled)
	{
		// ARRANGE 
		auto dealer = hc::Dealer(1, 13, false);

		// ACT
		for (auto cardIndex = 0; cardIndex < 200; cardIndex++)
		{
			auto card = dealer.dealCard();

			// ASSERT
			ASSERT_NE(card.getSuit(), hc::Card::Suit::undefined);
			ASSERT_NE(card.getRank(), 0);
		}
	}
}
