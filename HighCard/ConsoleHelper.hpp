#pragma once

#include "HighCardLib/GameConfig.hpp"
#include "HighCardLib/Player.hpp"

class ConsoleHelper
{
public:

    ConsoleHelper() = delete;
    ~ConsoleHelper() = delete;

    static void printBanner(); 
    static void requestRules(highcardlib::GameConfig& gameConfig);
    static void printConfig(const highcardlib::GameConfig& gameConfig);
    static highcardlib::Player requestPlayer(int playerNumber);
    static void printCardDealt(const highcardlib::Player& player);
    static void printTie();
    static void printWinner(const highcardlib::Player& winner);
};
