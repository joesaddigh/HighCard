#pragma once

#include <array>
#include <algorithm>
#include <random>

#include "HighCardLib/Deck.hpp"

namespace highcardlib
{
    Deck::Deck(int totalCardsPerSuit, bool supportWildcard)
    {
        createDeck(totalCardsPerSuit, supportWildcard);
    }

    void Deck::createDeck(int totalCardsPerSuit, bool supportWildcard)
    {
        static constexpr std::array<Card::Suit, 4> allCardSuits = { 
            Card::Suit::clubs, 
            Card::Suit::diamonds,
            Card::Suit::hearts,
            Card::Suit::spades
        };

        for (auto cardSuit : allCardSuits)
        {
            for (auto cardRank = 1; cardRank <= totalCardsPerSuit; cardRank++)
            {
                m_cards.emplace_back(Card{ cardRank, cardSuit });
            }
        }

        if (supportWildcard)
        {
            m_cards.emplace_back(Card{});
        }
    }

    void Deck::shuffle()
    {
        auto rng = std::default_random_engine{};
        std::shuffle(std::begin(m_cards), std::end(m_cards), rng);
    }
}
