#include <unordered_map>
#include <sstream>

#include "HighCardLib/Card.hpp"

namespace highcardlib
{
    Card::Card() :
        Card("", 0, Suit::undefined)
    {
    }

    Card::Card(std::string rankName, int rank, Suit suit) :
        m_rankName{ std::move(rankName) },
        m_rank{ rank },
        m_suit{ suit }
    {
    }

    Card Card::createWildCard()
    {
        return Card{ "Wildcard", INT_MAX, Suit::wildcard};
    }

    std::string Card::toString() const noexcept 
    {
        std::stringstream fmt;
        fmt << m_rankName << " "
            << getSuitString();

        return fmt.str();
    }

    std::string Card::getSuitString() const
    {
        static auto suits = std::unordered_map<Suit, std::string>{
            { Suit::wildcard, "**"},
            { Suit::clubs, "Clubs"},
            { Suit::diamonds, "Diamonds"},
            { Suit::hearts, "Hearts"},
            { Suit::spades, "Spades"}
        };

        std::string suitString = "Unknown";

        if (const auto& findSuit = suits.find(m_suit); findSuit != suits.end())
        {
            suitString = findSuit->second;
        }

        return suitString;
    }
}