#pragma once

namespace highcardlib
{
    class Card
    {
    public:
        
        enum class Suit
        {
            none, clubs, diamonds, hearts, spades
        };

        Card();
        Card(int rank, Suit suit);

        auto getRank() const noexcept { return m_rank; }
        auto getSuit() const noexcept { return m_suit; }
        auto getWildcard() const noexcept { return m_wildcard; }

    private:
        int m_rank{};
        Suit m_suit{};
        bool m_wildcard{};
    };
}
