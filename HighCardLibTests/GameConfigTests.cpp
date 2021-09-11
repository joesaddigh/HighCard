#include "gtest/gtest.h"

#include "HighCardLib/GameConfig.hpp"
#include "HighCardLib/Card.hpp"

namespace hc = highcardlib;

namespace highcardlibtests
{
	// Constructor tests
	TEST(GameConfigTests, constructor_noParams_configIsInitialised)
	{
		// ARRANGE && ACT
		auto gameConfig = hc::GameConfig{};

		// ASSERT
		ASSERT_EQ(gameConfig.getTieResolveStrategy(), hc::GameConfig::TieResolveStrategy::allow);
		ASSERT_EQ(gameConfig.getTotalDecks(), 0);
		ASSERT_EQ(gameConfig.getAddWildcard(), false);
		ASSERT_EQ(gameConfig.getTotalCardsPerSuit(), 0);
		ASSERT_TRUE(gameConfig.getSuitPrecedence().empty());
	}

	// Public function tests

	TEST(GameConfigTests, gettersAndSetters_returnExpectedValues)
	{
		// ARRANGE
		constexpr auto tieResolveStrategy = hc::GameConfig::TieResolveStrategy::suitPrecedence;
		constexpr auto totalDecks = 57;
		constexpr auto addWildCard = true;
		constexpr auto totalCardsPerSuit = 25;

		auto gameConfig = hc::GameConfig{};

		// ACT
		gameConfig.setTieResolveStrategy(tieResolveStrategy);
		gameConfig.setTotalDecks(totalDecks);
		gameConfig.setAddWildcard(addWildCard);
		gameConfig.setTotalCardsPerSuit(totalCardsPerSuit);
		gameConfig.setSuitPrecedence(hc::GameConfig::SuitPrecedence{
			{hc::Card::Suit::clubs, 1},
			{hc::Card::Suit::diamonds, 2},
			{hc::Card::Suit::spades, 3},
			{hc::Card::Suit::hearts, 4},
		});

		// ASSERT
		ASSERT_EQ(gameConfig.getTieResolveStrategy(), tieResolveStrategy);
		ASSERT_EQ(gameConfig.getTotalDecks(), totalDecks);
		ASSERT_EQ(gameConfig.getAddWildcard(), addWildCard);
		ASSERT_EQ(gameConfig.getTotalCardsPerSuit(), totalCardsPerSuit);
		
		auto suitPrecedence = gameConfig.getSuitPrecedence();
		ASSERT_FALSE(suitPrecedence.empty());
		ASSERT_EQ(suitPrecedence.size(), 4);
		ASSERT_EQ(suitPrecedence[hc::Card::Suit::clubs], 1);
		ASSERT_EQ(suitPrecedence[hc::Card::Suit::diamonds], 2);
		ASSERT_EQ(suitPrecedence[hc::Card::Suit::spades], 3);
		ASSERT_EQ(suitPrecedence[hc::Card::Suit::hearts], 4);
	}

	TEST(GameConfigTests, createDefault_returnsExpectedValues)
	{
		// ARRANGE && ACT
		auto gameConfig = hc::GameConfig::createDefault();

		// ASSERT
		ASSERT_EQ(gameConfig.getTieResolveStrategy(), hc::GameConfig::TieResolveStrategy::allow);
		ASSERT_EQ(gameConfig.getTotalDecks(), 1);
		ASSERT_EQ(gameConfig.getAddWildcard(), false);
		ASSERT_EQ(gameConfig.getTotalCardsPerSuit(), 13);
		ASSERT_TRUE(gameConfig.getSuitPrecedence().empty());
	}

	TEST(GameConfigTests, toString_returnsSomething)
	{
		// ARRANGE
		auto gameConfig = hc::GameConfig::createDefault();

		// ACT
		auto gameConfigString = gameConfig.toString();

		// ASSERT
		ASSERT_FALSE(gameConfigString.empty());
	}
}
