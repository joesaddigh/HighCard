#include "HighCardLib/Card.hpp"

namespace highcardlib
{
    Card::Card() :  
        m_rank{},
        m_suit{ Suit::none },
        m_wildcard{ true }
    {
    }

    Card::Card(int rank, Suit suit) :
        m_rank{ rank },
        m_suit{ suit },
        m_wildcard{ false }
    {
    }
}