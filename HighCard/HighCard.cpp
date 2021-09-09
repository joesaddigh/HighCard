#include <memory>
#include <iostream>
#include <string>

#include "HighCardLib/Dealer.hpp"
#include "HighCardLib/HighCardGame.hpp"
#include "HighCardLib/Player.hpp"

namespace
{
    auto printBanner()
    {
        std::cout << " ********* HIGH CARD *********" << std::endl;
        std::cout << "  ___   ___   ___   ___   ___ " << std::endl;
        std::cout << " |A  | |K  | |Q  | |J  | |10 |" << std::endl;
        std::cout << " |(`)| |(`)| |(`)| |(`)| |(`)|" << std::endl;
        std::cout << " |_\\_| |_\\_| |_\\_| |_\\_| |_\\_|" << std::endl;
        std::cout << " ****************************" << std::endl << std::endl;
    }

    auto createPlayer(int playerNumber)
    {
        std::string playerName;
        std::cout << "Please enter player" << playerNumber << " name: ";
        std::getline(std::cin, playerName);
        return highcardlib::Player{ playerName, playerNumber };
    }

    auto printCardDealt(const highcardlib::Player& player)
    {
        std::cout
            << "Player " << player.getPlayerNumber() << ": " << player.getName()
            << " dealt card: " << player.getDealtCard().toString()
            << std::endl;
    };

    auto printError()
    {
        std::cout
            << "Oops, Something Went Wrong." << std::endl;
    };

    auto printTie()
    {
        std::cout
            << "It was a tie!" << std::endl;
    }

    auto printWinner(const highcardlib::Player& winner) 
    {
        std::cout
            << "Player " << winner.getPlayerNumber() << ": " << winner.getName()
            << " won with card: " << winner.getDealtCard().toString()
            << std::endl;
    };

    auto play(
        const highcardlib::Player& playerOne, 
        const highcardlib::Player& playerTwo
    )
    {
        auto gameConfig = highcardlib::GameConfig::createDefault();

        auto highCardGame = highcardlib::HighCardGame<> {
            std::make_unique<highcardlib::Dealer>(gameConfig),
            gameConfig.getTieResolveStrategy(),
            printCardDealt,
            playerOne, 
            playerTwo 
        };

        auto result = highCardGame.play();

        switch (result)
        {
            case highcardlib::HighCardGame<>::PlayResult::undefined:
                printError();
                break;

            case highcardlib::HighCardGame<>::PlayResult::tie:
                printTie();
                break;

            case highcardlib::HighCardGame<>::PlayResult::playerOne:
                printWinner(highCardGame.getPlayerOne());
                break;

            case highcardlib::HighCardGame<>::PlayResult::playerTwo:
                printWinner(highCardGame.getPlayerTwo());
                break;
        }
    }
}

int main()
{
    try
    {
        printBanner();

        auto playerOne = createPlayer(1);
        auto playerTwo = createPlayer(2);

        play(playerOne, playerTwo);
    }
    catch (const std::exception& exc)
    {
        std::cerr << exc.what();
    }

    return 0;
}
