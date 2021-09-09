#pragma once

#include <string>

#include "Card.hpp"

namespace highcardlib
{
    class Player
    {
    public:

        Player(std::string name, int playerNumber);

        auto getName() const noexcept { return m_name; }
        auto getPlayerNumber() const noexcept { return m_playerNumber; }
        auto getDealtCard() const noexcept { return m_dealtCard; }

        void setDealtCard(const Card& dealtCard) { m_dealtCard = dealtCard; }
    private:

        std::string m_name;
        int m_playerNumber;
        Card m_dealtCard;
    };
}
