#pragma once

#include "Deck.hpp"

namespace highcardlib
{
    class CustomDeck : public Deck
    {
    public:

        CustomDeck(int totalCardsPerSuit);

        void createDeck() override;

    private:
        int m_totalCardsPerSuit{};
    };
}
