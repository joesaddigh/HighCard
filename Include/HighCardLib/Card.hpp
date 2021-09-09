#pragma once

#include <string>

namespace highcardlib
{
    class Card
    {
    public:
        
        enum class Suit
        {
            wildcard, clubs, diamonds, hearts, spades
        };

        Card();
        Card(int rank, Suit suit);

        auto getRank() const noexcept { return m_rank; }
        auto getSuit() const noexcept { return m_suit; }
        std::string toString() const noexcept;

    private:
        int m_rank{};
        Suit m_suit{ Suit::wildcard };
    };
}
