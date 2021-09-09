#include "HighCardLib/Player.hpp"

namespace highcardlib
{
    Player::Player(std::string name, int playerNumber) :
        m_name{ std::move(name) },
        m_playerNumber{ playerNumber }
    {
    }
}
