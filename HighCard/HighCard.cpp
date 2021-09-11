#include <memory>
#include <iostream>
#include <string>

#include "ConsoleHelper.hpp"

#include "HighCardLib/GameConfig.hpp"
#include "HighCardLib/Dealer.hpp"
#include "HighCardLib/HighCardGame.hpp"
#include "HighCardLib/Player.hpp"

namespace
{
    auto gameConfig = highcardlib::GameConfig::createDefault();

    auto displayResults(
        highcardlib::HighCardGame<>::PlayResult result,
        const highcardlib::HighCardGame<>& highCardGame
    )
    {
        switch (result)
        {
            case highcardlib::HighCardGame<>::PlayResult::tie:
                ConsoleHelper::printTie();
                break;

            case highcardlib::HighCardGame<>::PlayResult::playerOne:
                ConsoleHelper::printWinner(highCardGame.getPlayerOne());
                break;

            case highcardlib::HighCardGame<>::PlayResult::playerTwo:
                ConsoleHelper::printWinner(highCardGame.getPlayerTwo());
                break;
        }
    }

    auto play(
        const highcardlib::Player& playerOne, 
        const highcardlib::Player& playerTwo
    )
    {
        auto highCardGame = highcardlib::HighCardGame<> {
            std::make_unique<highcardlib::Dealer>(
                gameConfig.getTotalDecks(), 
                gameConfig.getTotalCardsPerSuit(),
                gameConfig.getAddWildcard()
            ),
            gameConfig.getTieResolveStrategy(),
            gameConfig.getSuitPrecedence(),
            ConsoleHelper::printCardDealt,
            playerOne, 
            playerTwo 
        };

        auto result = highCardGame.play();
        displayResults(result, highCardGame);
    }
}

int main(int argc, char* argv[])
{
    try
    {
        ConsoleHelper::printBanner();
        ConsoleHelper::requestRules(gameConfig);
        ConsoleHelper::printConfig(gameConfig);

        auto playerOne = ConsoleHelper::requestPlayer(1);
        auto playerTwo = ConsoleHelper::requestPlayer(2);

        auto playAgain = bool{};
        do
        {
            play(playerOne, playerTwo);
            playAgain = ConsoleHelper::requestPlayAgain();
        } while (playAgain);
    }
    catch (const std::exception& exc)
    {
        std::cerr << exc.what();
    }

    return 0;
}
