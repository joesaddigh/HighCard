#pragma once

#include <array>
#include <algorithm>
#include <random>

#include "HighCardLib/Deck.hpp"
#include "UtilsLib/RandomNumberGenerator.hpp"

namespace highcardlib
{
    Deck::Deck()
    {
        createDeck();
        shuffle();
    }

    void Deck::createDeck()
    {
        static constexpr std::array<Card::Suit, 4> allCardSuits = { 
            Card::Suit::clubs, 
            Card::Suit::diamonds,
            Card::Suit::hearts,
            Card::Suit::spades
        };

        for (auto cardSuit : allCardSuits)
        {
            for (auto cardRank = 2; cardRank <= 13; cardRank++)
            {
                m_cards.emplace_back(Card{ cardRank, cardSuit });
            }
        }
    }

    void Deck::addWildCard()
    {
        auto randomCardIndex = utilslib::RandomNumberGenerator::generateRandomNumber(
            0, static_cast<int>(m_cards.size() - 1)
        );

        m_cards[randomCardIndex] = Card::createWildCard();
    }

    void Deck::shuffle()
    {
        auto rng = std::default_random_engine{};
        std::shuffle(std::begin(m_cards), std::end(m_cards), rng);
    }
}
