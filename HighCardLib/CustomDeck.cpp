#pragma once

#include <array>
#include <algorithm>
#include <random>

#include "HighCardLib/CustomDeck.hpp"

namespace highcardlib
{
    CustomDeck::CustomDeck(int totalCardsPerSuit) :
        m_totalCardsPerSuit{ totalCardsPerSuit }
    {
    }

    void CustomDeck::createDeck()
    {
        static constexpr std::array<Card::Suit, 4> allCardSuits = { 
            Card::Suit::clubs, 
            Card::Suit::diamonds,
            Card::Suit::hearts,
            Card::Suit::spades
        };

        for (auto cardSuit : allCardSuits)
        {
            for (auto cardRank = 1; cardRank <= m_totalCardsPerSuit; cardRank++)
            {
                m_cards.emplace_back(Card{ cardRank, cardSuit });
            }
        }
    }
}
