#pragma once

#include "Deck.hpp"

namespace highcardlib
{
    class Dealer
    {
    public:

        Dealer(int totalDecks, int totalCardsPerSuit, bool supportWildcard);

        Card dealCard();

    private:
        
        int m_totalDecks{};
        int m_totalCardsPerSuit{};
        bool m_supportWildcard{};
        Deck::Cards m_availableCards{};

        Card pickCard();
        void generateFreshDecks();
    };
}
