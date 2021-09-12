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
	TEST(HighCardGameTests, play_getPlayers_returnsCorrectPlayers)
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

		auto gamePlayerOne = gameConfig.getPlayerOne();
		ASSERT_EQ(gamePlayerOne.getName(), playerOne.getName());
		ASSERT_EQ(gamePlayerOne.getPlayerNumber(), playerOne.getPlayerNumber());

		auto gamePlayerTwo = gameConfig.getPlayerTwo();
		ASSERT_EQ(gamePlayerTwo.getName(), playerTwo.getName());
		ASSERT_EQ(gamePlayerTwo.getPlayerNumber(), playerTwo.getPlayerNumber());
	}

	TEST(HighCardGameTests, play_withPlayerOneWinner_playerOneWins)
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
		EXPECT_CALL(*dealer, dealCard())

			// Player one card
			.WillOnce(testing::Return(
				hc::Card{ "Ace", 14, hc::Card::Suit::clubs }
			))

			// Player two card
			.WillOnce(testing::Return(
				hc::Card{ "King", 13, hc::Card::Suit::diamonds }
			)
		);

		auto gameConfig = HighCardGameType{
			std::move(dealer),
			tieResolveStrategy,
			suitPrecedence,
			onCardDealt,
			playerOne,
			playerTwo
		};

		auto playResult = gameConfig.play();

		ASSERT_EQ(playResult, HighCardGameType::PlayResult::playerOne);
	}

	TEST(HighCardGameTests, play_withPlayerTwoWinner_playerTwoWins)
	{
		// ARRANGE
		constexpr auto totalDecks = 1;
		constexpr auto totalCardsPerSuit = 13;
		constexpr auto supportWildcard = false;
		auto dealer = std::make_unique<DealerMock>(totalDecks, totalCardsPerSuit, supportWildcard);
		constexpr auto tieResolveStrategy = hc::GameConfig::TieResolveStrategy::allow;
		auto suitPrecedence = hc::GameConfig::SuitPrecedence{};
		auto dealtCards = int{};
		auto onCardDealt = [&](const hc::Player& player) {
			dealtCards++;
		};
		auto playerOne = hc::Player{ "Joe", 1 };
		auto playerTwo = hc::Player{ "Tony", 2 };

		// ACT & ASSERT
		EXPECT_CALL(*dealer, dealCard())

			// Player one card
			.WillOnce(testing::Return(
				hc::Card{ "Two", 2, hc::Card::Suit::clubs }
			))

			// Player two card
			.WillOnce(testing::Return(
				hc::Card{ "Four", 4, hc::Card::Suit::diamonds }
			)
			);

		auto gameConfig = HighCardGameType{
			std::move(dealer),
			tieResolveStrategy,
			suitPrecedence,
			onCardDealt,
			playerOne,
			playerTwo
		};

		auto playResult = gameConfig.play();

		ASSERT_EQ(playResult, HighCardGameType::PlayResult::playerTwo);
		ASSERT_EQ(dealtCards, 2);
	}

	TEST(HighCardGameTests, play_withTieAndAllowed_gameTies)
	{
		// ARRANGE
		constexpr auto totalDecks = 1;
		constexpr auto totalCardsPerSuit = 13;
		constexpr auto supportWildcard = false;
		auto dealer = std::make_unique<DealerMock>(totalDecks, totalCardsPerSuit, supportWildcard);
		constexpr auto tieResolveStrategy = hc::GameConfig::TieResolveStrategy::allow;
		auto suitPrecedence = hc::GameConfig::SuitPrecedence{};
		auto dealtCards = int{};
		auto onCardDealt = [&](const hc::Player& player) {
			dealtCards++;
		};
		auto playerOne = hc::Player{ "Joe", 1 };
		auto playerTwo = hc::Player{ "Tony", 2 };

		// ACT & ASSERT
		EXPECT_CALL(*dealer, dealCard())

			// Player one card
			.WillOnce(testing::Return(
				hc::Card{ "Two", 2, hc::Card::Suit::clubs }
			))

			// Player two card
			.WillOnce(testing::Return(
				hc::Card{ "Two", 2, hc::Card::Suit::diamonds }
			)
		);

		auto gameConfig = HighCardGameType{
			std::move(dealer),
			tieResolveStrategy,
			suitPrecedence,
			onCardDealt,
			playerOne,
			playerTwo
		};

		auto playResult = gameConfig.play();

		ASSERT_EQ(playResult, HighCardGameType::PlayResult::tie);
		ASSERT_EQ(dealtCards, 2);
	}

	TEST(HighCardGameTests, play_withTieDealNewCardPlayerOneWinsSecondGame_playerOneWins)
	{
		// ARRANGE
		constexpr auto totalDecks = 1;
		constexpr auto totalCardsPerSuit = 13;
		constexpr auto supportWildcard = false;
		auto dealer = std::make_unique<DealerMock>(totalDecks, totalCardsPerSuit, supportWildcard);
		constexpr auto tieResolveStrategy = hc::GameConfig::TieResolveStrategy::dealNewCard;
		auto suitPrecedence = hc::GameConfig::SuitPrecedence{};
		auto dealtCards = int{};
		auto onCardDealt = [&](const hc::Player& player) {
			dealtCards++;
		};
		auto playerOne = hc::Player{ "Joe", 1 };
		auto playerTwo = hc::Player{ "Tony", 2 };

		// ACT & ASSERT
		EXPECT_CALL(*dealer, dealCard())

			// Player one card
			.WillOnce(testing::Return(
				hc::Card{ "Two", 2, hc::Card::Suit::clubs }
			))

			// Player two card
			.WillOnce(testing::Return(
				hc::Card{ "Two", 2, hc::Card::Suit::diamonds }
			))

			// Player one card
			.WillOnce(testing::Return(
				hc::Card{ "Five", 5, hc::Card::Suit::clubs }
			))

			// Player two card
			.WillOnce(testing::Return(
				hc::Card{ "Three", 3, hc::Card::Suit::diamonds }
			)
		);

		auto gameConfig = HighCardGameType{
			std::move(dealer),
			tieResolveStrategy,
			suitPrecedence,
			onCardDealt,
			playerOne,
			playerTwo
		};

		auto playResult = gameConfig.play();

		ASSERT_EQ(playResult, HighCardGameType::PlayResult::playerOne);
		ASSERT_EQ(dealtCards, 4);
	}

	TEST(HighCardGameTests, play_withTieSuitPrecedencePlayerOneHigherScoringSuit_playerOneWins)
	{
		// ARRANGE
		constexpr auto totalDecks = 1;
		constexpr auto totalCardsPerSuit = 13;
		constexpr auto supportWildcard = false;
		auto dealer = std::make_unique<DealerMock>(totalDecks, totalCardsPerSuit, supportWildcard);
		constexpr auto tieResolveStrategy = hc::GameConfig::TieResolveStrategy::suitPrecedence;
		auto suitPrecedence = hc::GameConfig::SuitPrecedence{
			{ hc::Card::Suit::clubs, 1 },
			{ hc::Card::Suit::diamonds, 2 },
			{ hc::Card::Suit::hearts, 3 },
			{ hc::Card::Suit::spades, 4 },
		};
		auto dealtCards = int{};
		auto onCardDealt = [&](const hc::Player& player) {
			dealtCards++;
		};
		auto playerOne = hc::Player{ "Joe", 1 };
		auto playerTwo = hc::Player{ "Tony", 2 };

		// ACT & ASSERT
		EXPECT_CALL(*dealer, dealCard())

			// Player one card
			.WillOnce(testing::Return(
				hc::Card{ "Two", 2, hc::Card::Suit::diamonds }
			))

			// Player two card
			.WillOnce(testing::Return(
				hc::Card{ "Two", 2, hc::Card::Suit::clubs }
			)
		);

		auto gameConfig = HighCardGameType{
			std::move(dealer),
			tieResolveStrategy,
			suitPrecedence,
			onCardDealt,
			playerOne,
			playerTwo
		};

		auto playResult = gameConfig.play();

		ASSERT_EQ(playResult, HighCardGameType::PlayResult::playerOne);
		ASSERT_EQ(dealtCards, 2);
	}
}
