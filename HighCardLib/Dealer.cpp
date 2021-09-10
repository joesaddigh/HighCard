#include <assert.h>

#include "HighCardLib/Dealer.hpp"
#include "HighCardLib/DeckFactory.hpp"
#include "UtilsLib/RandomNumberGenerator.hpp"

namespace highcardlib
{
    Dealer::Dealer(int totalDecks, int totalCardsPerSuit, bool supportWildcard) :
        m_totalDecks{ totalDecks }, 
        m_totalCardsPerSuit{ totalCardsPerSuit }, 
        m_supportWildcard{ supportWildcard },
        m_availableCards{}
    {
        generateFreshDecks();
    };

    Card Dealer::dealCard()
    {
        if (m_availableCards.empty())
        {
            generateFreshDecks();
        }

        return pickCard();
    }

    Card Dealer::pickCard()
    {
        auto card = Card{};

        if (!m_availableCards.empty())
        {
            // In order to obtain a random card, using the random number generator to obtain
            // a random number within the specified range of 0 - no advancement and the total items
            // in the vector - 1.
            auto randomCardAdvance = utilslib::RandomNumberGenerator::generateRandomNumber(
                0, static_cast<int>(m_availableCards.size() - 1)
            );

            // Set our iterator to the beginning.
            auto randomCard = m_availableCards.begin();
            // If there is any advancement required, do it.
            if (randomCardAdvance > 0)
            {
                std::advance(randomCard, randomCardAdvance);
            }

            // This shouldn't happen.
            assert(randomCard != m_availableCards.end());

            if (randomCard != m_availableCards.end())
            {
                // Populate the return object with the random card that has been picked.
                card = *randomCard;

                // Remove this card now so that it can't be picked again.
                m_availableCards.erase(randomCard);
            }
        }

        return card;
    }

    void Dealer::generateFreshDecks()
    {
        m_availableCards.clear();

        for (auto deckNumber = 0; deckNumber < m_totalDecks; deckNumber++)
        {
            auto deck = DeckFactory::create(m_totalCardsPerSuit);
            if (m_supportWildcard)
            {
                deck->addWildCard();
            }
            const auto& cards = deck->getCards();
            m_availableCards.insert(std::end(m_availableCards), std::begin(cards), std::end(cards));
        }
    }
}
