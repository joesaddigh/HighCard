#pragma once

#include <array>
#include <algorithm>
#include <random>
#include <stdexcept>

#include "HighCardLib/CustomDeck.hpp"

namespace highcardlib
{
    CustomDeck::CustomDeck(int totalCardsPerSuit) :
        m_totalCardsPerSuit{ totalCardsPerSuit }
    {
        if (m_totalCardsPerSuit <= 0)
        {
            throw std::invalid_argument("Can't create a custom deck of cards with no cards.");
        }
    }

    void CustomDeck::createDeck()
    {
        for (auto cardSuit : { Card::Suit::clubs, Card::Suit::diamonds, Card::Suit::hearts, Card::Suit::spades})
        {
            for (auto cardRank = 1; cardRank <= m_totalCardsPerSuit; cardRank++)
            {
                m_cards.emplace_back(Card{ std::to_string(cardRank), cardRank, cardSuit });
            }
        }
        shuffle();
    }
}
