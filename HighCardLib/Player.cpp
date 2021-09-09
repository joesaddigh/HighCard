#include "HighCardLib/Player.hpp"

namespace highcardlib
{
    Player::Player(std::string name) :
        m_name{ std::move(name) }
    {
    }

    void Player::dealtCard(const Card& card)
    {
        m_card = card;
    }
}
