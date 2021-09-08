#pragma once

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
        gameConfig.m_tieResolveStrategy = TieResolveStrategy::faceValue;
        gameConfig.m_totalDecks = 1;
        gameConfig.m_supportWildCard = false;
        gameConfig.m_totalCardsPerSuit = DEFAULT_TOTAL_CARDS_PER_SUIT;
        gameConfig.m_mixDecks = false;

        return gameConfig;
    }
}
