#include "gtest/gtest.h"

#include "HighCardLib/DeckFactory.hpp"
#include "HighCardLib/Deck.hpp"
#include "HighCardLib/CustomDeck.hpp"

namespace hc = highcardlib;

namespace highcardlibtests
{	
	// Public function tests
	TEST(DeckFactoryTests, create_withCustomDeckTotalCardsPerSuit_returnsCustomDeck)
	{
		// ARRANGE
		constexpr auto totalCardsPerSuit = 100;

		// ACT
		auto deck = hc::DeckFactory::create(totalCardsPerSuit);
		
		// ASSERT
		ASSERT_TRUE(dynamic_cast<hc::CustomDeck*>(deck.get()) != nullptr);
	}
}
