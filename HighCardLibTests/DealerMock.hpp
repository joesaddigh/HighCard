#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "HighCardLib/Dealer.hpp"
#include "HighCardLib/Card.hpp"

namespace hc = highcardlib;

class DealerMock : public hc::Dealer
{
public:

	DealerMock(int totalDecks, int totalCardsPerSuit, bool supportWildcard) :
		hc::Dealer{ totalDecks, totalCardsPerSuit, supportWildcard }
	{};

	MOCK_METHOD(hc::Card, dealCard, ());
};