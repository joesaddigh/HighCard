#include <unordered_map>
#include <sstream>

#include "HighCardLib/Card.hpp"

namespace highcardlib
{
    Card::Card() :  
        m_rank{},
        m_suit{ Suit::wildcard }
    {
    }

    Card::Card(int rank, Suit suit) :
        m_rank{ rank },
        m_suit{ suit }
    {
    }

    std::string Card::toString() const noexcept 
    {
        /*auto mapping = std::unordered_map<Suit, std::string>{
            { Suit::wildcard, u8"\u2605"},
            { Suit::clubs, u8"\u2663"},
            { Suit::diamonds, u8"\u2666"},
            { Suit::hearts, u8"\u2665"},
            { Suit::spades, u8"\u2660"}
        };*/

        static auto mapping = std::unordered_map<Suit, std::string>{
            { Suit::wildcard, "**"},
            { Suit::clubs, "Clubs"},
            { Suit::diamonds, "Diamonds"},
            { Suit::hearts, "Hearts"},
            { Suit::spades, "Spades"}
        };

        static auto pictureCards = std::unordered_map<int, std::string>{
            { 11, "Jack"},
            { 12, "Queen"},
            { 13, "King"},
            { 1, "Ace"}
        };

        auto str = std::string{};

        if (const auto& findSuit = mapping.find(m_suit); findSuit != mapping.end())
        {
            std::stringstream fmt;
            if (m_suit != Suit::wildcard)
            {
                if (const auto& findRank = pictureCards.find(m_rank); findRank != pictureCards.end())
                {
                    fmt << findRank->second << " ";
                }
                else
                {
                    fmt << m_rank << " ";
                }
            }
            fmt << findSuit->second;
            str = fmt.str();
        }

        return str;
    }
}