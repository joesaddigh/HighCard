#pragma once

#include "HighCardLib/GameConfig.hpp"
#include "HighCardLib/Player.hpp"

namespace highcardlib
{
    class HighCardGame
    {
    public:

        HighCardGame();

        void start(const Player& playerOne, const Player& playerTwo);

    private:

        Player m_playerOne{};
        Player m_playerTwo{};
        GameConfig m_gameConfig{};
    };
}
