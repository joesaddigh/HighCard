#pragma once

#include <vector>

#include "HighCardLib/Card.hpp"

namespace highcardlib
{
    class Deck
    {
    public:

        Deck(int totalCardsPerSuit, bool supportWildcard);

        using Cards = std::vector<Card>;

        const auto& getCards() const noexcept { return m_cards; }

    private:
        Cards m_cards{};

        void createDeck(int totalCardsPerSuit, bool supportWildcard);
    };
}
