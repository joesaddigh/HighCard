#include "gtest/gtest.h"

#include "HighCardLib/Player.hpp"
#include "HighCardLib/Card.hpp"

namespace hc = highcardlib;

namespace highcardlibtests
{
	// Constructor tests
	TEST(PlayerTests, constructor_withParams_playerMatchesParams)
	{
		// ARRANGE
		constexpr auto playerName = "Mr Card Player";
		constexpr auto playerNumber = 97;

		// ACT
		auto player = hc::Player{ playerName, playerNumber };

		// ASSERT
		ASSERT_EQ(player.getName(), playerName);
		ASSERT_EQ(player.getPlayerNumber(), playerNumber);
		auto playersCard = player.getDealtCard();
		ASSERT_EQ(playersCard.getRank(), 0);
		ASSERT_EQ(playersCard.getSuit(), hc::Card::Suit::undefined);
	}

	// Public function tests
	TEST(PlayerTests, setDealtCard_withCard_cardMatches)
	{
		// ARRANGE
		constexpr auto playerName = "Mr Card Player";
		constexpr auto playerNumber = 97;
		auto card = hc::Card{ "Three", 3, hc::Card::Suit::spades };

		// ACT
		auto player = hc::Player{ playerName, playerNumber };
		player.setDealtCard(card);

		// ASSERT
		ASSERT_EQ(player.getName(), playerName);
		ASSERT_EQ(player.getPlayerNumber(), playerNumber);
		ASSERT_EQ(player.getDealtCard(), card);
	}
}
