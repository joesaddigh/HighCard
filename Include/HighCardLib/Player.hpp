#pragma once

#include <string>

#include "Card.hpp"

namespace highcardlib
{
    class Player
    {
    public:
        
        Player() = default;
        Player(std::string name);

        void dealtCard(const Card& card);
    private:

        std::string m_name;
        Card m_card;
    };
}
