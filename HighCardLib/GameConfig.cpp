#pragma once

#include <sstream>
#include <unordered_map>

#include "HighCardLib/GameConfig.hpp"

namespace
{
    static auto constexpr DEFAULT_TOTAL_CARDS_PER_SUIT = 13;
}

namespace highcardlib
{
    GameConfig GameConfig::createDefault()
    {
        auto gameConfig = GameConfig{};
        gameConfig.m_tieResolveStrategy = TieResolveStrategy::allow;
        gameConfig.m_totalDecks = 1;
        gameConfig.m_addWildcard = false;
        gameConfig.m_totalCardsPerSuit = DEFAULT_TOTAL_CARDS_PER_SUIT;

        return gameConfig;
    }

    std::string GameConfig::toString() const
    {
        std::stringstream fmt;
        fmt << "Tie Resolve Strategy: " << getTieResolveStrategyString() << std::endl
            << "Total Decks: " << m_totalDecks << std::endl
            << "Add WildCard: " << std::boolalpha << m_addWildcard << std::endl
            << "Total Cards Per Suit: " << m_totalCardsPerSuit << std::endl
            << "Tie Resolve Strategy: " << getTieResolveStrategyString() << std::endl;

        return fmt.str();
    }

    std::string GameConfig::getTieResolveStrategyString() const
    {
        static auto resolveStrategies = std::unordered_map<TieResolveStrategy, std::string>{
            { TieResolveStrategy::allow, "Allow"},
            { TieResolveStrategy::dealNewCard, "Deal New Card"},
            { TieResolveStrategy::suitPrecedence, "Suit Precedence"},
        };

        auto resolveStrategyString = std::string{};

        if (const auto& findTieResolveStrategy = resolveStrategies.find(m_tieResolveStrategy); 
            findTieResolveStrategy != resolveStrategies.end())
        {
            resolveStrategyString = findTieResolveStrategy->second;
        }

        return resolveStrategyString;
    }
}
