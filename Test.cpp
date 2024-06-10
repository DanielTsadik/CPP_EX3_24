#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Board.hpp"
#include "Player.hpp"
#include <unordered_set>

// Helper function to compare two vectors of Plots
bool comparePlots(const std::vector<Plot> &expected, const std::vector<Plot> &actual)
{
    if (expected.size() != actual.size())
    {
        return false;
    }

    for (size_t i = 0; i < expected.size(); ++i)
    {
        if (expected[i].getResource() != actual[i].getResource() ||
            expected[i].getNumber() != actual[i].getNumber() ||
            expected[i].getIndex() != actual[i].getIndex())
        {
            return false;
        }
    }

    return true;
}

TEST_CASE("Board constructor")
{
    Player player1(1, "Player 1");
    Player player2(2, "Player 2");
    Player player3(3, "Player 3");

    SUBCASE("Plots are initialized correctly")
    {
        Board board(player1, player2, player3);
        std::vector<Plot> expectedPlots = {
            Plot("Mountains", 10, 0), Plot("Pasture", 2, 1), Plot("Forest", 9, 2), Plot("Agricultural", 12, 3), Plot("Hills", 6, 4), Plot("Pasture", 4, 5), Plot("Hills", 10, 6), Plot("Agricultural", 9, 7), Plot("Forest", 11, 8), Plot("Desert", 7, 9), Plot("Forest", 3, 10), Plot("Mountains", 8, 11), Plot("Forest", 8, 12), Plot("Mountains", 3, 13), Plot("Agricultural", 4, 14), Plot("Pasture", 5, 15), Plot("Hills", 5, 16), Plot("Agricultural", 6, 17), Plot("Pasture", 11, 18)};

        REQUIRE(comparePlots(expectedPlots, board.getPlots()));
    }

    SUBCASE("Players are added correctly")
    {
        Board board(player1, player2, player3);
        std::vector<Player *> expectedPlayers = {&player1, &player2, &player3};

        REQUIRE(board.players == expectedPlayers);
    }

    SUBCASE("Development cards are initialized correctly")
    {
        Board board(player1, player2, player3);
        std::vector<std::string> expectedCards = {
            "Knight", "Knight", "Knight", "Knight", "Knight", "Knight", "Knight", "Knight",
            "Knight", "Knight", "Knight", "Knight", "Knight", "Knight", "Victory Point",
            "Victory Point", "Victory Point", "Victory Point", "Victory Point", "Road Placement",
            "Road Placement", "Year Of Plenty", "Year Of Plenty", "Monopoly", "Monopoly"};

        std::unordered_set<std::string> actualCards;
        for (const auto &card : board.developmentCards)
        {
            actualCards.insert(card.getType());
        }

        std::unordered_set<std::string> expectedCardsSet(expectedCards.begin(), expectedCards.end());

        REQUIRE(actualCards == expectedCardsSet);
    }

}

    TEST_CASE("Player constructor")
    {
        Player player(1, "Player 1");

        SUBCASE("Player ID is set correctly")
        {
            REQUIRE(player.getId() == 1);
        }

        SUBCASE("Player name is set correctly")
        {
            REQUIRE(player.getName() == "Player 1");
        }

        SUBCASE("Player resources are initialized to zero")
        {
            for (const auto &resource : player.resources)
            {
                REQUIRE(resource.second == 0);
            }
        }
    }

    TEST_CASE("Board methods")
    {
        Player player1(1, "Player 1");
        Player player2(2, "Player 2");
        Player player3(3, "Player 3");
        Board board(player1, player2, player3);

        SUBCASE("Testing plot values")
        {
            // Define and initialize expectedPlot
            Plot expectedPlot("Mountains", 10, 0);

            REQUIRE(board.getPlots()[0].getResource() == expectedPlot.getResource());
            REQUIRE(board.getPlots()[0].getNumber() == expectedPlot.getNumber());
            REQUIRE(board.getPlots()[0].getIndex() == expectedPlot.getIndex());
        }
    }
