#include <algorithm>

#include "gtest/gtest.h"

#include "HighCardLib/Deck.hpp"

namespace hc = highcardlib;

namespace highcardlibtests
{
	// Constructor tests
	TEST(DeckTests, constructor_noParams_dataInitialised)
	{
		// ARRANGE
		auto deck = hc::Deck{};

		// ACT
		auto cards = deck.getCards();

		// ASSERT
		ASSERT_TRUE(cards.empty());
	}

	// Public function tests
	TEST(DeckTests, createDeck_deckCreated)
	{
		// ARRANGE
		auto deck = hc::Deck{};

		// ACT
		deck.createDeck();
		auto cards = deck.getCards();

		// ASSERT
		ASSERT_EQ(cards.size(), 52);
	}

	TEST(DeckTests, addWildcard_wildCardAdded)
	{
		// ARRANGE
		auto deck = hc::Deck{};

		// ACT
		deck.createDeck();
		deck.addWildCard();
		auto cards = deck.getCards();

		// ASSERT
		ASSERT_EQ(cards.size(), 52);
		auto find = std::find_if(std::begin(cards), std::end(cards), [](const hc::Card& cards) {
			return cards.getSuit() == hc::Card::Suit::wildcard;
		});
		ASSERT_TRUE(find != std::end(cards));
	}
}
