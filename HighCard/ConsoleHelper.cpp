#include <sstream>
#include <iostream>
#include <unordered_map>
#include <functional>

#include "ConsoleHelper.hpp"
#include "HighCardLib/Player.hpp"
#include "HighCardLib/UserInputValidator.hpp"
#include "UtilsLib/StringUtils.hpp"

namespace
{
    auto askQuestion(
        std::string_view question,
        std::function<bool(const std::string&)> validate
    )
    {
        auto questionAnswered = false;
        std::string answer;

        // Keep prompting the userthe validation has been fulfilled.
        while (!questionAnswered)
        {
            std::cout << question;
            std::getline(std::cin, answer);

            questionAnswered = validate(answer);
        }

        return answer;
    }

    auto requestAndSetTieResolve(highcardlib::GameConfig& gameConfig)
    {
        static auto tieResolveMapping = std::unordered_map<std::string, highcardlib::GameConfig::TieResolveStrategy>{
            {"ALLOW", highcardlib::GameConfig::TieResolveStrategy::allow},
            {"SUITPRECEDENCE", highcardlib::GameConfig::TieResolveStrategy::suitPrecedence},
            {"DEALNEWCARD", highcardlib::GameConfig::TieResolveStrategy::dealNewCard}
        };

        askQuestion(
            "How would you like to resolve ties? [Allow/SuitPrecedence/DealNewCard]",
            [&](const std::string& answer) {
                auto upper = utilslib::StringUtils::toUpper(answer);
                if (auto findTieResolve = tieResolveMapping.find(upper);
                    findTieResolve != tieResolveMapping.end())
                {
                    gameConfig.setTieResolveStrategy(findTieResolve->second);
                    return true;
                }
                return false;
            }
        );

        if (gameConfig.getTieResolveStrategy() == highcardlib::GameConfig::TieResolveStrategy::suitPrecedence)
        {
            static auto allowedSuits = std::unordered_map<std::string, highcardlib::Card::Suit>{
                {"C", highcardlib::Card::Suit::clubs},
                {"D", highcardlib::Card::Suit::diamonds},
                {"H", highcardlib::Card::Suit::hearts},
                {"S", highcardlib::Card::Suit::spades}
            };

            askQuestion(
                "Please enter the order of suit precedence, in ascending order. For example Clubs, Diamonds, Hearts, Spades, would be entered like so, C,D,H,S:",
                [&](const std::string& answer) {
                    auto valid = bool{};
                    auto suits = utilslib::StringUtils::splitString(answer, ',');
                    // All suits must be defined.
                    if (suits.size() == 4)
                    {
                        auto suitPrecedence = highcardlib::GameConfig::SuitPrecedence{};
                        auto precedence = int{};
                        for (const auto& suit : suits)
                        {
                            if (auto findSuit = allowedSuits.find(suit); findSuit != allowedSuits.end())
                            {
                                suitPrecedence[findSuit->second] = precedence;
                                precedence++;
                                valid = true;
                            }
                            else
                            {
                                return false;
                            }
                        }

                        if (valid)
                        {
                            gameConfig.setSuitPrecedence(suitPrecedence);
                        }
                    }
                    return valid;
                }
            );
        }
    }

    auto requestAndSetTotalDecks(highcardlib::GameConfig& gameConfig)
    {
        askQuestion(
            "How many decks would you like to use? [1 - 10]",
            [&](const std::string& answer) {
                if (highcardlib::UserInputValidator::isNumberWithinRange(answer, 1, 10))
                {
                    gameConfig.setTotalDecks(std::stoi(answer));
                    return true;
                }
                return false;
            }
        );
    }

    auto requestAndSetAddWildCard(highcardlib::GameConfig& gameConfig)
    {
        askQuestion(
            "Would you like to substitute one of the cards in a deck with a wildcard (beats all others)? [y,n]",
            [&](const std::string& answer) {
                if (highcardlib::UserInputValidator::validateYesNo(answer))
                {
                    gameConfig.setAddWildcard(highcardlib::UserInputValidator::yesNoToBool(answer));
                    return true;
                }
                return false;
            }
        );
    }

    auto requestAndSetCustomDeck(highcardlib::GameConfig& gameConfig)
    {
        std::string customDeckOfCards = askQuestion(
            "Would you like to use a custom deck of cards? [y,n]",
            [&](const std::string& answer) {
                return highcardlib::UserInputValidator::validateYesNo(answer);
            }
        );

        if (highcardlib::UserInputValidator::yesNoToBool(customDeckOfCards))
        {
            std::string totalCardsPerSuit = askQuestion(
                "How many cards per suit would you like to have? [1-100]",
                [&](const std::string& answer) {
                    if (highcardlib::UserInputValidator::isNumberWithinRange(answer, 1, 100))
                    {
                        gameConfig.setTotalCardsPerSuit(std::stoi(answer));
                        return true;
                    }
                    return false;
                }
            );
        }
    }
}

void ConsoleHelper::printBanner()
{
    std::cout << " ********* HIGH CARD *********" << std::endl;
    std::cout << "  ___   ___   ___   ___   ___ " << std::endl;
    std::cout << " |A  | |K  | |Q  | |J  | |10 |" << std::endl;
    std::cout << " |(`)| |(`)| |(`)| |(`)| |(`)|" << std::endl;
    std::cout << " |_\\_| |_\\_| |_\\_| |_\\_| |_\\_|" << std::endl;
    std::cout << " ****************************" << std::endl << std::endl;
}

void ConsoleHelper::requestRules(highcardlib::GameConfig& gameConfig)
{
    requestAndSetTieResolve(gameConfig);
    requestAndSetTotalDecks(gameConfig);
    requestAndSetAddWildCard(gameConfig);
    requestAndSetCustomDeck(gameConfig);
}

void ConsoleHelper::printConfig(const highcardlib::GameConfig& gameConfig)
{
    std::cout << " ********* Game Configuration *********" << std::endl;
    std::cout << gameConfig.toString() << std::endl;
    std::cout << " ****************************" << std::endl << std::endl;
}

highcardlib::Player ConsoleHelper::requestPlayer(int playerNumber)
{
    std::string playerName = askQuestion(
        "Please enter player" + std::to_string(playerNumber) + " name: ",
        [&](const std::string& answer) {
            return !answer.empty();
        }
    );
    return highcardlib::Player{ playerName, playerNumber };
}

bool ConsoleHelper::requestPlayAgain()
{
    std::string playAgain = askQuestion(
        "Would you like to play again? [y,n]",
        [&](const std::string& answer) {
            return highcardlib::UserInputValidator::validateYesNo(answer);
        }
    );
    return highcardlib::UserInputValidator::yesNoToBool(playAgain);
}

void ConsoleHelper::printCardDealt(const highcardlib::Player& player)
{
    std::cout
        << "Player " << player.getPlayerNumber() << ": " << player.getName()
        << " dealt card: " << player.getDealtCard().toString()
        << std::endl;
};

void ConsoleHelper::printTie()
{
    std::cout << "It was a tie!" << std::endl;
}

void ConsoleHelper::printWinner(const highcardlib::Player& winner)
{
    std::cout
        << "Player " << winner.getPlayerNumber() << ": " << winner.getName()
        << " won with card: " << winner.getDealtCard().toString()
        << std::endl;
};
