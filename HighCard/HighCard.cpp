#include <iostream>
#include <string>

#include "HighCardLib/GameConfig.hpp"
#include "HighCardLib/Dealer.hpp"
#include "HighCardLib/Player.hpp"

namespace
{
    auto printBanner()
    {
        std::cout << "  ___   ___   ___   ___   ___ " << std::endl;
        std::cout << " |A  | |K  | |Q  | |J  | |10 |" << std::endl;
        std::cout << " |(`)| |(`)| |(`)| |(`)| |(`)|" << std::endl;
        std::cout << " |_\\_| |_\\_| |_\\_| |_\\_| |_\\_|" << std::endl << std::endl;
    }

    auto createPlayer(int player)
    {
        std::string playerName;
        std::cout << "Please enter player" << player << " name: ";
        std::getline(std::cin, playerName);
        return highcardlib::Player{ playerName };
    }
}

int main()
{
    try
    {
        printBanner();

        /*auto playerOne = createPlayer(1);
        auto playerTwo = createPlayer(2);*/

        auto gameConfig = highcardlib::GameConfig::createDefault();
        auto dealer = highcardlib::Dealer{ gameConfig };

        for (int i = 0; i < 20000; i++)
        {
            auto card = dealer.dealCard();
            std::cout << card.toString() << std::endl;
        }

        /*auto card1 = dealer.dealCard();
        std::cout << card1.toString() << std::endl;

        auto card2 = dealer.dealCard();
        std::cout << card2.toString() << std::endl;

        playerOne.dealtCard(card1);
        playerTwo.dealtCard(card2);*/
    }
    catch (const std::exception& exc)
    {
        std::cerr << exc.what();
    }

    return 0;
}
