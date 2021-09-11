#pragma once

#include <array>
#include <algorithm>
#include <random>

#include "HighCardLib/Deck.hpp"
#include "UtilsLib/RandomNumberGenerator.hpp"

namespace
{
    struct RankMapping
    {
        int rank;
        std::string name;
    };

    static auto ranks = std::array<RankMapping, 13>{{
        { 2, "Two"},
        { 3, "Three" },
        { 4, "Four" },
        { 5, "Five" },
        { 6, "Six" },
        { 7, "Seven" },
        { 8, "Eight" },
        { 9, "Nine" },
        { 10, "Ten" },
        { 11, "Jack" },
        { 12, "Queen" },
        { 13, "King" },
        { 14, "Ace" }
    }};
}

namespace highcardlib
{
    void Deck::createDeck()
    {
        for (auto cardSuit : { Card::Suit::clubs, Card::Suit::diamonds, Card::Suit::hearts, Card::Suit::spades })
        {
            for (const auto& cardRank : ranks)
            {
                m_cards.emplace_back(Card{ cardRank.name, cardRank.rank, cardSuit });
            }
        }
        shuffle();
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
