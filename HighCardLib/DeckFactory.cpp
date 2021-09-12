#include <stdexcept>

#include "HighCardLib/DeckFactory.hpp"
#include "HighCardLib/CustomDeck.hpp"

namespace
{
    static constexpr auto STANDARD_DECK_CARDS_PER_SUIT = 13;
}

namespace highcardlib
{
    DeckFactory::DeckType DeckFactory::create(int totalCardsPerSuit)
    {
        if (totalCardsPerSuit <= 0)
            throw std::invalid_argument("Can't create a deck with no cards.");

        switch (totalCardsPerSuit)
        {
            case STANDARD_DECK_CARDS_PER_SUIT:
                return std::make_unique<Deck>();
            
            default:
                return std::make_unique<CustomDeck>(totalCardsPerSuit);
        }
    }
}
