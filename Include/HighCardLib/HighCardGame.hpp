#pragma once

#include <memory>
#include <functional>

#include "HighCardLib/Player.hpp"
#include "HighCardLib/GameConfig.hpp"

namespace highcardlib
{
    // Inject the dealer for unit testing purposes. Although it might be useful in other
    // situations too.
    template<
        typename DealerType = Dealer
    >
    class HighCardGame
    {
    public:

        enum class PlayResult
        {
            undefined, tie, playerOne, playerTwo
        };

        using OnCardDealt = std::function<void(const Player& player)>;

        HighCardGame(
            std::unique_ptr<DealerType> dealer,
            GameConfig::TieResolveStrategy tieResolveStrategy,
            OnCardDealt onCardDealt,
            const Player& playerOne, 
            const Player& playerTwo
        ) :
            m_dealer{ std::move(dealer) },
            m_tieResolveStrategy{ tieResolveStrategy },
            m_onCardDealt{ onCardDealt },
            m_playerOne{ playerOne },
            m_playerTwo{ playerTwo }
        {
            if (m_dealer == nullptr)
            {
                throw std::invalid_argument("Dealer cannot be null");
            }

            if (m_onCardDealt == nullptr)
            {
                throw std::invalid_argument("Card dealt callback cannot be null");
            }
        }

        PlayResult play()
        {
            auto playResult = challengePlayers();

            if (playResult == PlayResult::tie)
            {
                playResult = handleTie();
            }

            return playResult;
        }

        const Player& getPlayerOne() const { return m_playerOne; }
        const Player& getPlayerTwo() const { return m_playerTwo; }

    private:

        std::unique_ptr<DealerType> m_dealer{ nullptr };
        GameConfig::TieResolveStrategy m_tieResolveStrategy{ GameConfig::TieResolveStrategy::faceValue };
        OnCardDealt m_onCardDealt{ nullptr };
        Player m_playerOne;
        Player m_playerTwo;

        PlayResult handleTie()        
        {
            auto playResult = PlayResult::tie;

            switch (m_tieResolveStrategy)
            {
                case GameConfig::TieResolveStrategy::suitPrecedence:
                    playResult = handleTieSuitPrecedence();
                    break;

                case GameConfig::TieResolveStrategy::newCard:
                    playResult = handleTieRequestNewCard();
                    break;

                case GameConfig::TieResolveStrategy::faceValue:
                default:
                    // Nothing to do, a tie is allowed.
                    break;
            }

            return playResult;
        }

        PlayResult handleTieSuitPrecedence()
        {
            auto playResult = PlayResult::tie;



            return playResult;
        }

        PlayResult handleTieRequestNewCard()
        {
            auto playResult = PlayResult::tie;

            auto requestNewCard = true;
            auto attemptsToResolve = 0;
            constexpr auto GIVE_UP = 100;

            do
            {
                playResult = challengePlayers();

                requestNewCard = 
                    playResult == PlayResult::tie || 
                    attemptsToResolve == GIVE_UP;

                ++attemptsToResolve;

            } while (requestNewCard);

            return playResult;
        }

        PlayResult challengePlayers()
        {
            auto playResult = PlayResult::undefined;
            
            auto playerOneCard = m_dealer->dealCard();
            m_playerOne.setDealtCard(playerOneCard);
            m_onCardDealt(m_playerOne);

            auto playerTwoCard = m_dealer->dealCard();
            m_playerTwo.setDealtCard(playerTwoCard);
            m_onCardDealt(m_playerTwo);

            if (m_playerOne.getDealtCard() > m_playerTwo.getDealtCard())
            {
                playResult = PlayResult::playerOne;
            }
            else if (m_playerTwo.getDealtCard() > m_playerOne.getDealtCard())
            {
                playResult = PlayResult::playerTwo;
            }
            else
            {
                playResult = PlayResult::tie;
            }

            return playResult;
        }
    };
}
