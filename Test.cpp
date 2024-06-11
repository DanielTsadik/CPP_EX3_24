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
        Plot expectedPlot("Mountains", 10, 0);

        REQUIRE(board.getPlots()[0].getResource() == expectedPlot.getResource());
        REQUIRE(board.getPlots()[0].getNumber() == expectedPlot.getNumber());
        REQUIRE(board.getPlots()[0].getIndex() == expectedPlot.getIndex());
    }

    SUBCASE("Testing canPlaceSettlement")
    {
        REQUIRE(board.canPlaceSettlement(player1.getId(), 0) == false);
    }

    SUBCASE("Testing canPlaceRoad")
    {
        REQUIRE(board.canPlaceRoad(player1.getId(), 0, 1) == false);
    }

    SUBCASE("Testing canPlaceCity")
    {
        REQUIRE(board.canPlaceCity(player1.getId(), 0) == false);
    }

    SUBCASE("Testing getEdge")
    {
        REQUIRE(board.getEdge(0, 1) == 0);
    }

    SUBCASE("Testing canPlaceInitialSettlementAndRoad")
    {
        REQUIRE(board.canPlaceInitialSettlementAndRoad(player1, 0, 1) == true);
    }

    SUBCASE("Testing giveResources")
    {
        board.giveResources(board.players, 8); // example roll
        for (const auto &player : board.players)
        {
            for (const auto &resource : player->resources)
            {
                CHECK(resource.second >= 0); // check resources are non-negative
            }
        }
    }

    SUBCASE("Testing drawDevelopmentCard")
    {
        board.drawDevelopmentCard(player1.getId());
        CHECK(player1.developmentCards.size() == 1); // player should have one card after drawing
    }
}

TEST_CASE("Player methods")
{
    Player player(1, "Player 1");
    Player player2(2, "Player 2");
    Player player3(3, "Player 3");
    Board board(player, player2, player3);

    SUBCASE("Testing placeInitialSettlementAndRoad")
    {
        player.placeInitialSettlementAndRoad(0, 1, board);
        CHECK(player.getRoads(board).size() == 1);
    }

    SUBCASE("Testing placeSettlement")
    {
        player.placeInitialSettlementAndRoad(0, 1, board);
        CHECK(player.getSettlementsVec(board).size() == 1);
    }

    SUBCASE("Testing upgradeToCity")
    {
        player.addResource("Ore", 3);
        player.addResource("Wheat", 2);
        player.placeInitialSettlementAndRoad(0, 1, board);
        player.upgradeToCity(0, board);
        CHECK(player.getCitiesVec(board).size() == 1);
    }

    SUBCASE("Testing placeRoad")
    {
        player.placeRoad(0, 1, board);
        CHECK(player.getRoads(board).size() == 0);
    }

    SUBCASE("Testing addResource")
    {
        player.addResource("Wood", 1);
        CHECK(player.resources[0].second == 1);
    }

    SUBCASE("Testing canbuySettlement")
    {
        CHECK(player.canbuySettlement() == false);
    }

    SUBCASE("Testing canbuyCity")
    {
        CHECK(player.canbuyCity() == false);
    }

    SUBCASE("Testing canbuyRoad")
    {
        CHECK(player.canbuyRoad() == false);
    }

    SUBCASE("Testing rollDice")
    {
        player.rollDice(board);
        for (const auto &player : board.players)
        {
            for (const auto &resource : player->resources)
            {
                CHECK(resource.second >= 0);
            }
        }
    }

    SUBCASE("Testing chooseDevelopmentCard")
    {
        player.addResource("Ore", 1);
        player.addResource("Wheat", 1);
        player.addResource("Wool", 1);
        player.chooseDevelopmentCard(board);
        CHECK(player.developmentCards.size() == 1);
    }

    SUBCASE("Testing tradeResources")
    {
        player.addResource("Wood", 1);
        player2.addResource("Brick", 1);
        player.tradeResources(board, player2.getId(), "Brick", 1, "Wood", 1);
        CHECK(player.resources[0].second == 0);
        CHECK(player.resources[1].second == 1);
    }

    SUBCASE("Testing useKnight")
    {
        player.useKnight(board);
        CHECK(player.knightsPlayed == 0);
    }

    SUBCASE("Testing useYearOfPlenty")
    {
        player.useYearOfPlenty("Wood", "Brick");
        CHECK_FALSE(player.resources[0].second == 1);
        CHECK_FALSE(player.resources[1].second == 1);
    }

    SUBCASE("Testing discardResources")
    {
        player.addResource("Wood", 2);
        player.addResource("Brick", 2);
        player.discardResources(board);
        CHECK(player.resources[0].second == 2);
        CHECK(player.resources[1].second == 2);
    }
}
