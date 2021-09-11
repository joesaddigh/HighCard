#include "gtest/gtest.h"

#include "HighCardLib/Card.hpp"

namespace hc = highcardlib;

namespace highcardlibtests
{
	// Constructor tests
	TEST(CardTests, constructor_noParams_cardIsInitialised)
	{
		// ARRANGE & ACT
		auto card = hc::Card{};

		// ASSERT
		ASSERT_EQ(card.getRank(), 0);
		ASSERT_EQ(card.getSuit(), hc::Card::Suit::undefined);
	}

	TEST(CardTests, constructor_withParams_cardMatchesParams)
	{
		// ARRANGE
		constexpr auto rankName = "Jack";
		constexpr auto rank = 11;
		constexpr auto suit = hc::Card::Suit::diamonds;

		// ACT
		auto card = hc::Card{ rankName, rank, suit };

		// ASSERT
		ASSERT_EQ(card.getRank(), rank);
		ASSERT_EQ(card.getSuit(), suit);
	}

	// Operator overload tests
	// ==
	TEST(CardTests, equalsOperator_withSameCards_returnsTrue)
	{
		// ARRANGE
		// ARRANGE & ACT
		auto card1 = hc::Card{ "Queen", 11, hc::Card::Suit::diamonds };
		auto card2 = hc::Card{ "Queen", 11, hc::Card::Suit::diamonds };

		// ASSERT
		ASSERT_TRUE(card1 == card2);
	}

	TEST(CardTests, equalsOperator_withDifferentCards_returnsFalse)
	{
		// ARRANGE & ACT
		auto card1 = hc::Card{ "Jack", 11, hc::Card::Suit::diamonds };
		auto card2 = hc::Card{ "Jack", 11, hc::Card::Suit::clubs };

		// ASSERT
		ASSERT_FALSE(card1 == card2);
	}

	// !=
	TEST(CardTests, notEqualsOperator_withSameCards_returnsFalse)
	{
		// ARRANGE & ACT
		auto card1 = hc::Card{ "Jack", 11, hc::Card::Suit::diamonds };
		auto card2 = hc::Card{ "Jack", 11, hc::Card::Suit::diamonds };

		// ASSERT
		ASSERT_FALSE(card1 != card2);
	}

	TEST(CardTests, notEqualsOperator_withDifferentCards_returnsTrue)
	{
		// ARRANGE & ACT
		auto card1 = hc::Card{ "Jack", 11, hc::Card::Suit::diamonds };
		auto card2 = hc::Card{ "Jack", 11, hc::Card::Suit::clubs };

		// ASSERT
		ASSERT_TRUE(card1 != card2);
	}

	// <
	TEST(CardTests, lessThanOperator_withLhsLessThanRhs_returnsTrue)
	{
		// ARRANGE & ACT
		auto card1 = hc::Card{ "Jack", 11, hc::Card::Suit::diamonds };
		auto card2 = hc::Card{ "Jack", 12, hc::Card::Suit::diamonds };

		// ASSERT
		ASSERT_TRUE(card1 < card2);
	}

	TEST(CardTests, lessThanOperator_withLhsGreaterThanRhs_returnsFalse)
	{
		// ARRANGE & ACT
		auto card1 = hc::Card{ "Jack", 12, hc::Card::Suit::diamonds };
		auto card2 = hc::Card{ "Jack", 11, hc::Card::Suit::diamonds };

		// ASSERT
		ASSERT_FALSE(card1 < card2);
	}

	// >
	TEST(CardTests, greaterThanOperator_withLhsLessThanRhs_returnsFalse)
	{
		// ARRANGE & ACT
		auto card1 = hc::Card{ "Jack", 11, hc::Card::Suit::diamonds };
		auto card2 = hc::Card{ "Jack", 12, hc::Card::Suit::diamonds };

		// ASSERT
		ASSERT_FALSE(card1 > card2);
	}

	TEST(CardTests, greaterThanOperator_withLhsGreaterThanRhs_returnsTrue)
	{
		// ARRANGE & ACT
		auto card1 = hc::Card{ "Jack", 12, hc::Card::Suit::diamonds };
		auto card2 = hc::Card{ "Jack", 11, hc::Card::Suit::diamonds };

		// ASSERT
		ASSERT_TRUE(card1 > card2);
	}

	// Public function tests
	TEST(CardTests, createWildCard_returnsWildcard)
	{
		// ARRANGE & ACT
		auto card = hc::Card::createWildCard();

		// ASSERT
		ASSERT_EQ(card.getRank(), INT_MAX);
		ASSERT_EQ(card.getSuit(), hc::Card::Suit::wildcard);
	}

	TEST(CardTests, toString_returnsSomething)
	{
		// ARRANGE
		auto card = hc::Card{ "Ace", 14, hc::Card::Suit::hearts };

		// ACT
		auto cardString = card.toString();

		// ASSERT
		ASSERT_FALSE(cardString.empty());
	}
}
