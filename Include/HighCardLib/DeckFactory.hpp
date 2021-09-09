#pragma once

#include <memory>

#include "Deck.hpp"

namespace highcardlib
{
    class DeckFactory
    {
    public:

        using DeckType = std::unique_ptr<Deck>;

        DeckFactory() = delete;
        ~DeckFactory() = delete;

        static DeckType create(int totalCardsPerSuit);
    };
}
