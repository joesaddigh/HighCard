#include <iostream>
#include <string>

#include "HighCardLib/Dealer.hpp"

namespace
{
    auto printBanner()
    {
        std::cout << "  _    _ _       _        _____              _ " << std::endl;
        std::cout << " | |  | (_)     | |      / ____|            | |" << std::endl;
        std::cout << " | |__| |_  __ _| |__   | |     __ _ _ __ __| |" << std::endl;
        std::cout << " |  __  | |/ _` | '_ \  | |    / _` | '__/ _` |" << std::endl;
        std::cout << " | |  | | | (_| | | | | | |___| (_| | | | (_| |" << std::endl;
        std::cout << " |_|  |_|_|\__, |_| |_|  \_____\__,_|_|  \__,_|" << std::endl;
        std::cout << "            __/ |                              " << std::endl;
        std::cout << "           |___/               		 " << std::endl << std::endl;
    }

    auto requestPlayerName(int player)
    {
        std::string playerName;
        std::cout << "Please enter player" << player << " name:";
        std::getline(std::cin, playerName);
        return playerName;
    }
}

int main()
{
    try
    {
        printBanner();
        auto player1 = requestPlayerName(1);
        auto player2 = requestPlayerName(2);
    }
    catch (...)
    {
        
    }

    return 0;
}
