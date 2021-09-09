#pragma once

#include <string>

namespace highcardlib
{
    class Card
    {
    public:
        
        enum class Suit
        {
            undefined, wildcard, clubs, diamonds, hearts, spades
        };

        Card();
        Card(int rank, Suit suit);

        bool operator==(const Card& rhs) const
        {
            return
                this->m_rank == rhs.m_rank &&
                this->m_suit == rhs.m_suit;
        }

        bool operator!=(const Card& rhs) const
        {
            return !(*this == rhs);
        }

        bool operator<(const Card& rhs) const
        {
            return
                this->m_rank < rhs.m_rank;
        }

        bool operator>(const Card& rhs) const
        {
            return
                this->m_rank > rhs.m_rank;
        }

        static Card createWildCard();

        auto getRank() const noexcept { return m_rank; }
        auto getSuit() const noexcept { return m_suit; }
        std::string toString() const noexcept;

    private:
        int m_rank{};
        Suit m_suit{ Suit::wildcard };

        std::string getRankString() const;
        std::string getSuitString() const;
    };
}
