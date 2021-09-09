#include <unordered_map>
#include <sstream>

#include "HighCardLib/Card.hpp"

namespace highcardlib
{
    Card::Card() :
        Card(0, Suit::undefined)
    {
    }

    Card::Card(int rank, Suit suit) :
        m_rank{ rank },
        m_suit{ suit }
    {
    }

    Card Card::createWildCard()
    {
        return Card{ 0, Suit::wildcard };
    }

    std::string Card::toString() const noexcept 
    {
        std::stringstream fmt;
        if (m_suit != Suit::wildcard)
        {
            fmt << getRankString() << " ";
        }
        fmt << getSuitString();

        return fmt.str();
    }

    std::string Card::getRankString() const
    {
        static auto ranks = std::unordered_map<int, std::string>{
            { 1, "Ace"},
            { 2, "Two"},
            { 3, "Three"},
            { 4, "Four"},
            { 5, "Five"},
            { 6, "Six"},
            { 7, "Seven"},
            { 8, "Eight"},
            { 9, "Nine"},
            { 10, "Ten"},
            { 11, "Jack"},
            { 12, "Queen"},
            { 13, "King"}
        };

        auto rankString = std::to_string(m_rank);

        if (const auto& findRank = ranks.find(m_rank); findRank != ranks.end())
        {
            rankString = findRank->second;
        }

        return rankString;
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