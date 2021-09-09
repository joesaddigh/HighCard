#pragma once

#include <vector>

#include "HighCardLib/Card.hpp"

namespace highcardlib
{
    class Deck
    {
    public:

        using Cards = std::vector<Card>;

        Deck();
        virtual ~Deck() = default;

        const auto& getCards() const noexcept { return m_cards; }
        
        virtual void createDeck();
        void addWildCard();

    protected:
        Cards m_cards{};
        void shuffle();
    };
}
