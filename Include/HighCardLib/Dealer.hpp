#pragma once

#include <optional>

#include "GameConfig.hpp"
#include "Deck.hpp"

namespace highcardlib
{
    class Dealer
    {
    public:

        Dealer(const GameConfig& gameConfig);

        std::optional<Card> dealCard();

    private:
        GameConfig m_gameConfig{};
        Deck::Cards m_availableCards{};

        std::optional<Card> pickCard();
        void shuffle();
    };
}
