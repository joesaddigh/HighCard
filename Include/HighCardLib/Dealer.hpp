#pragma once

#include "GameConfig.hpp"
#include "Deck.hpp"

namespace highcardlib
{
    class Dealer
    {
    public:

        Dealer(const GameConfig& gameConfig);

        Card dealCard();

    private:
        GameConfig m_gameConfig{};
        Deck::Cards m_availableCards{};

        Card pickCard();
        void generateFreshDecks();
    };
}
