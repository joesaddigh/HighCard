#pragma once

#include "Card.hpp"

namespace highcardlib
{
    class GameConfig
    {
    public:
        enum class TieResolveStrategy
        {
            faceValue, suitPrecedence, newCard
        };

        static GameConfig createDefault();

        auto getTieResolveStrategy() const noexcept { return m_tieResolveStrategy; }
        auto getTotalDecks() const noexcept { return m_totalDecks; }
        auto getSupportWildcard() const noexcept { return m_supportWildCard; }
        auto getTotalCardsPerSuit() const noexcept { return m_totalCardsPerSuit; }
        auto getMixDecks() const noexcept { return m_mixDecks; }

    private:
        
        TieResolveStrategy m_tieResolveStrategy{ TieResolveStrategy::faceValue };
        int m_totalDecks{};
        bool m_supportWildCard{};
        int m_totalCardsPerSuit{};
        bool m_mixDecks{};
    };
}
