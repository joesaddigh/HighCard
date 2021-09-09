#include "HighCardLib/Dealer.hpp"
#include "UtilsLib/RandomNumberGenerator.hpp"

namespace highcardlib
{
    Dealer::Dealer(const GameConfig& gameConfig) :
        m_gameConfig{ gameConfig },
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
            auto randomCardAdvance = utilslib::RandomNumberGenerator::generateRandomNumber(
                0, static_cast<int>(m_availableCards.size() - 1)
            );

            auto randomCard = m_availableCards.begin();
            std::advance(randomCard, randomCardAdvance);
            if (randomCard != m_availableCards.end())
            {
                card = *randomCard;
                m_availableCards.erase(randomCard);
            }
        }

        return card;
    }

    void Dealer::generateFreshDecks()
    {
        m_availableCards.clear();

        for (auto deckNumber = 0; deckNumber < m_gameConfig.getTotalDecks(); deckNumber++)
        {
            auto deck = Deck{ m_gameConfig.getTotalCardsPerSuit(), m_gameConfig.getSupportWildcard() };
            deck.shuffle();
            const auto& cards = deck.getCards();
            m_availableCards.insert(std::end(m_availableCards), std::begin(cards), std::end(cards));
        }
    }
}
