#include "gtest/gtest.h"

#include "HighCardLib/CustomDeck.hpp"

namespace hc = highcardlib;

namespace
{
	constexpr auto TOTAL_SUITS = 4;
}

namespace highcardlibtests
{
	// Constructor tests
	TEST(CustomDeckTests, constructor_zeroCards_throws)
	{
		// ARRANGE, ACT & ASSERT
		ASSERT_THROW(
			hc::CustomDeck{0},
			std::invalid_argument
		);
	}

	TEST(CustomDeckTests, constructor_negativeCards_throws)
	{
		// ARRANGE, ACT & ASSERT
		ASSERT_THROW(
			hc::CustomDeck{ -3300 },
			std::invalid_argument
		);
	}

	// Public function tests
	TEST(CustomDeckTests, createDeck_deckCreated)
	{
		// ARRANGE
		constexpr auto cardsPerDeck = 5;
		constexpr auto totalCards = TOTAL_SUITS * cardsPerDeck;
		auto deck = hc::CustomDeck{ cardsPerDeck };

		// ACT
		deck.createDeck();
		auto cards = deck.getCards();

		// ASSERT
		ASSERT_EQ(cards.size(), totalCards);
	}

	TEST(CustomDeckTests, addWildcard_wildCardAdded)
	{
		// ARRANGE
		constexpr auto cardsPerDeck = 50;
		constexpr auto totalCards = TOTAL_SUITS * cardsPerDeck;
		auto deck = hc::CustomDeck{ cardsPerDeck };

		// ACT
		deck.createDeck();
		deck.addWildCard();
		auto cards = deck.getCards();

		// ASSERT
		ASSERT_EQ(cards.size(), totalCards);
		auto find = std::find_if(std::begin(cards), std::end(cards), [](const hc::Card& cards) {
			return cards.getSuit() == hc::Card::Suit::wildcard;
		});
		ASSERT_TRUE(find != std::end(cards));
	}
}
