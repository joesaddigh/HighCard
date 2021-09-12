#include "gtest/gtest.h"

#include "HighCardLib/GameConfig.hpp"
#include "HighCardLib/Card.hpp"

namespace hc = highcardlib;

namespace highcardlibtests
{
	template <typename Map>
	bool mapCompare(Map const& lhs, Map const& rhs) {

		auto pred = [](auto a, auto b)
		{ 
			return
				a.first == b.first &&
				a.second == b.second;
		};

		return lhs.size() == rhs.size()
			&& std::equal(lhs.begin(), lhs.end(), rhs.begin(), pred);
	}

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
		auto suitPrecedenceToSet = hc::GameConfig::SuitPrecedence{			
			{hc::Card::Suit::clubs, 1},
			{hc::Card::Suit::diamonds, 2},
			{hc::Card::Suit::spades, 3},
			{hc::Card::Suit::hearts, 4},
		};

		auto gameConfig = hc::GameConfig{};

		// ACT
		gameConfig.setTieResolveStrategy(tieResolveStrategy);
		gameConfig.setTotalDecks(totalDecks);
		gameConfig.setAddWildcard(addWildCard);
		gameConfig.setTotalCardsPerSuit(totalCardsPerSuit);
		gameConfig.setSuitPrecedence(suitPrecedenceToSet);

		// ASSERT
		ASSERT_EQ(gameConfig.getTieResolveStrategy(), tieResolveStrategy);
		ASSERT_EQ(gameConfig.getTotalDecks(), totalDecks);
		ASSERT_EQ(gameConfig.getAddWildcard(), addWildCard);
		ASSERT_EQ(gameConfig.getTotalCardsPerSuit(), totalCardsPerSuit);
		ASSERT_TRUE(
			mapCompare<hc::GameConfig::SuitPrecedence>(gameConfig.getSuitPrecedence(), suitPrecedenceToSet)
		);
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
