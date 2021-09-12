#include "gtest/gtest.h"

#include "DealerMock.hpp"

#include "HighCardLib/HighCardGame.hpp"

namespace hc = highcardlib;

namespace
{
	using HighCardGameType = hc::HighCardGame<DealerMock>;
}

namespace highcardlibtests
{
	// Constructor tests
	TEST(HighCardGameTests, constructor_nullDealer_throws)
	{
		// ARRANGE
		auto dealer = std::unique_ptr<DealerMock>{ nullptr };
		constexpr auto tieResolveStrategy = hc::GameConfig::TieResolveStrategy::allow;
		auto suitPrecedence = hc::GameConfig::SuitPrecedence{};
		auto onCardDealt = [&](const hc::Player& player) {

		};
		auto playerOne = hc::Player{ "Joe", 1 };
		auto playerTwo = hc::Player{ "Tony", 2 };

		// ACT & ASSERT
		ASSERT_THROW(HighCardGameType(
			std::move(dealer),
			tieResolveStrategy,
			suitPrecedence,
			onCardDealt,
			playerOne,
			playerTwo
		), 
		std::invalid_argument);
	}

	TEST(HighCardGameTests, constructor_nullOnCardDealt_throws)
	{
		// ARRANGE
		constexpr auto totalDecks = 1;
		constexpr auto totalCardsPerSuit = 13;
		constexpr auto supportWildcard = false;
		auto dealer = std::make_unique<DealerMock>(totalDecks, totalCardsPerSuit, supportWildcard);
		constexpr auto tieResolveStrategy = hc::GameConfig::TieResolveStrategy::allow;
		auto suitPrecedence = hc::GameConfig::SuitPrecedence{};
		auto onCardDealt = [&](const hc::Player& player) {

		};
		auto playerOne = hc::Player{ "Joe", 1 };
		auto playerTwo = hc::Player{ "Tony", 2 };

		// ACT & ASSERT
		ASSERT_THROW(HighCardGameType(
			std::move(dealer),
			tieResolveStrategy,
			suitPrecedence,
			nullptr,
			playerOne,
			playerTwo
		), 
		std::invalid_argument);
	}

	TEST(HighCardGameTests, constructor_withValiData_noThrow)
	{
		// ARRANGE
		constexpr auto totalDecks = 1;
		constexpr auto totalCardsPerSuit = 13;
		constexpr auto supportWildcard = false;
		auto dealer = std::make_unique<DealerMock>(totalDecks, totalCardsPerSuit, supportWildcard);
		constexpr auto tieResolveStrategy = hc::GameConfig::TieResolveStrategy::allow;
		auto suitPrecedence = hc::GameConfig::SuitPrecedence{};
		auto onCardDealt = [&](const hc::Player& player) {

		};
		auto playerOne = hc::Player{ "Joe", 1 };
		auto playerTwo = hc::Player{ "Tony", 2 };

		// ACT & ASSERT
		auto gameConfig = HighCardGameType{
			std::move(dealer),
			tieResolveStrategy,
			suitPrecedence,
			onCardDealt,
			playerOne,
			playerTwo
		};
	}

	// Public function tests
}
