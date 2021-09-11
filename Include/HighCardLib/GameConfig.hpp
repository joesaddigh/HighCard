#pragma once

#include <string>
#include <unordered_map>

#include "Card.hpp"

namespace highcardlib
{
    class GameConfig
    {
    public:
        enum class TieResolveStrategy
        {
            allow, suitPrecedence, dealNewCard
        };

        using SuitPrecedence = std::unordered_map<Card::Suit, int>;

        GameConfig() = default;
        ~GameConfig() = default;

        static GameConfig createDefault();

        auto getTieResolveStrategy() const noexcept { return m_tieResolveStrategy; }
        auto getTotalDecks() const noexcept { return m_totalDecks; }
        auto getAddWildcard() const noexcept { return m_addWildcard; }
        auto getTotalCardsPerSuit() const noexcept { return m_totalCardsPerSuit; }
        auto getSuitPrecedence() const noexcept { return m_suitPrecedence; }

        auto setTieResolveStrategy(TieResolveStrategy tieResolveStrategy) noexcept { m_tieResolveStrategy = tieResolveStrategy; }
        auto setTotalDecks(int totalDecks) noexcept { return m_totalDecks = totalDecks; }
        auto setAddWildcard(bool addWildcard) noexcept { m_addWildcard = addWildcard; }
        auto setTotalCardsPerSuit(int totalCardsPerSuit) noexcept { m_totalCardsPerSuit = totalCardsPerSuit; }
        auto setSuitPrecedence(SuitPrecedence suitPrecedence) noexcept { m_suitPrecedence = std::move(suitPrecedence); }

        std::string toString() const;

    private:
        
        TieResolveStrategy m_tieResolveStrategy{ TieResolveStrategy::allow };
        int m_totalDecks{};
        bool m_addWildcard{};
        int m_totalCardsPerSuit{};
        bool m_mixDecks{};
        SuitPrecedence m_suitPrecedence{};

        std::string getTieResolveStrategyString() const;
    };
}
