#include <memory>
#include <iostream>
#include <string>
#include <unordered_map>

#include "HighCardLib/GameConfig.hpp"
#include "HighCardLib/Dealer.hpp"
#include "HighCardLib/HighCardGame.hpp"
#include "HighCardLib/Player.hpp"

namespace
{
    auto gameConfig = highcardlib::GameConfig::createDefault();

    auto printBanner()
    {
        std::cout << " ********* HIGH CARD *********" << std::endl;
        std::cout << "  ___   ___   ___   ___   ___ " << std::endl;
        std::cout << " |A  | |K  | |Q  | |J  | |10 |" << std::endl;
        std::cout << " |(`)| |(`)| |(`)| |(`)| |(`)|" << std::endl;
        std::cout << " |_\\_| |_\\_| |_\\_| |_\\_| |_\\_|" << std::endl;
        std::cout << " ****************************" << std::endl << std::endl;
    }

    auto printConfig()
    {
        std::cout << " ********* Game Configuration *********" << std::endl;
        std::cout << gameConfig.toString() << std::endl;
        std::cout << " ****************************" << std::endl << std::endl;
    }

    auto yesNoToBool(const std::string& yesNo)
    {
        return yesNo == "y";
    }

    auto isNumber(const std::string str)
    {
        return !str.empty() && 
            std::find_if(str.begin(), str.end(), [](unsigned char c) { 
                return !std::isdigit(c); 
        }) == str.end();
    }

    auto isNumberWithinRange(const std::string& str, int min, int max)
    {
        auto numberWithinRange = bool{};
        if (isNumber(str))
        {
            auto number = std::stoi(str);
            numberWithinRange = number >= min && number <= max;
        }
        return numberWithinRange;
    }
    
    auto askQuestion(
        const std::string& question,
        std::function<bool(const std::string&)> validate
    )
    {
        auto questionAnswered = false;
        std::string answer;

        while (!questionAnswered)
        {
            std::cout << question;
            std::getline(std::cin, answer);

            questionAnswered = validate(answer);
        }

        return answer;
    }

    auto requestRules()
    {
        static auto tieResolveMapping = std::unordered_map<std::string, highcardlib::GameConfig::TieResolveStrategy>{
            {"Allow", highcardlib::GameConfig::TieResolveStrategy::allow},
            {"SuitPrecedence", highcardlib::GameConfig::TieResolveStrategy::suitPrecedence},
            {"DealNewCard", highcardlib::GameConfig::TieResolveStrategy::dealNewCard}
        };

        std::string tieResolve = askQuestion(
            "How would you like to resolve ties? [Allow/SuitPrecedence/DealNewCard]",
            [](const std::string& answer) {
                return tieResolveMapping.find(answer) != tieResolveMapping.end();
            }
        );
        gameConfig.setTieResolveStrategy(tieResolveMapping[tieResolve]);

        std::string totalDecks = askQuestion(
            "How many decks would you like to use? [1 - 10]",
            [](const std::string& answer) {
                return isNumberWithinRange(answer, 1, 10);
            }
        );
        gameConfig.setTotalDecks(std::stoi(totalDecks));

        std::string addWildCard = askQuestion(
            "Would you like to make one of the cards across all of the decks a wilcard? [y,n]",
            [](const std::string& answer) {
                return
                    answer == "y" ||
                    answer == "n";
            }
        );
        gameConfig.setAddWildcard(yesNoToBool(addWildCard));

        std::string customDeckOfCards = askQuestion(
            "Would you like to use a custom deck of cards? [y,n]",
            [](const std::string& answer) {
                return
                    answer == "y" ||
                    answer == "n";
            }
        );

        if (yesNoToBool(customDeckOfCards))
        {
            std::string totalCardsPerSuit = askQuestion(
                "How many cards per suit would you like to have? [1-100]",
                [](const std::string& answer) {
                    return isNumberWithinRange(answer, 1, 100);
                }
            );
            gameConfig.setTotalCardsPerSuit(std::stoi(totalCardsPerSuit));
        }
    }

    auto requestPlayer(int playerNumber)
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
        auto highCardGame = highcardlib::HighCardGame<> {
            std::make_unique<highcardlib::Dealer>(
                gameConfig.getTotalDecks(), 
                gameConfig.getTotalCardsPerSuit(),
                gameConfig.getAddWildcard()
            ),
            gameConfig.getTieResolveStrategy(),
            printCardDealt,
            playerOne, 
            playerTwo 
        };

        auto result = highCardGame.play();

        switch (result)
        {
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

int main(int argc, char* argv[])
{
    try
    {
        printBanner();
        requestRules();
        printConfig();

        auto playerOne = requestPlayer(1);
        auto playerTwo = requestPlayer(2);

        play(playerOne, playerTwo);

        system("pause");
    }
    catch (const std::exception& exc)
    {
        std::cerr << exc.what();
    }

    return 0;
}
