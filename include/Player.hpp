#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Plot.hpp"
#include "Board.hpp"

// Forward declaration of Board class
class Board;

class Player
{
public:
    Player(int id, const std::string &name);

    int getId() const;
    const std::string &getName() const;
    int getPoints() const;

    void placeInitialSettlementAndRoad(int vertexIndex, int vertexIndex2, Board &board);
    void placeSettlement(int vertexIndex, Board &board);
    void upgradeToCity(int vertexIndex, Board &board);
    void placeRoad(int vertexIndex1, int vertexIndex2, Board &board);
    void buyDevelopmentCard();

    void getSettlements(Board &board) const;
    void getCities(Board &board) const;
    const std::vector<int> &getRoads(Board &board) const;

    void getResources() const;
    void addResource(const std::string &resource, int amount);
    // void removeResource(const std::string &resource, int amount);

    bool canbuySettlement();
    bool canbuyCity();
    bool canbuyRoad();

    void rollDice(Board &board);

    void chooseDevelopmentCard(Board &board);

    // Vector to hold the development cards
    std::vector<std::string> developmentCards;

    // Function to trade resources with other players
    void tradeResources(Board &board, int player, std::string resource1, int amount, std::string resource2, int amount2);

private:
    int id;
    // Vector to hold the resources
    std::vector<std::pair<std::string, int>> resources;
    // Name of the player
    std::string name;
    // Number of points the player has
    int points;
    // Vector to hold the settlements
    std::vector<int> settlements;
    // Vector to hold the cities
    std::vector<int> cities;
    // Vector to hold the roads
    std::vector<int> roads;
    // int for the number of knights played
    int knightsPlayed;

    // Function to use Knight Development Card
    void useKnight(Board &board);

    // Function to use Road Building Development Card
    void useRoadBuilding(Board &board, int vertexIndex1, int vertexIndex2, int vertexIndex3, int vertexIndex4);

    // Function to use Year of Plenty Development Card
    void useYearOfPlenty(std::string resource1, std::string resource2);

    // Function to use Monopoly Development Card
    void useMonopoly(Board &board, std::string resource);

    // int to keep track of the number of development cards
    int developmentCardCount = 0;
};

#endif // PLAYER_HPP
