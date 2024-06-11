// Daniel Tsadik
// Tsadik88@gmail.com   

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

using namespace std;

class Player
{
public:
    Player(int id, const string &name);

    int getId() const;
    const string &getName() const;
    int getPoints() const;

    void placeInitialSettlementAndRoad(int vertexIndex, int vertexIndex2, Board &board);
    void placeSettlement(int vertexIndex, Board &board);
    void upgradeToCity(int vertexIndex, Board &board);
    void placeRoad(int vertexIndex1, int vertexIndex2, Board &board);
    void canBuyDevelopmentCard();

    void getSettlements(Board &board) const;
    void getCities(Board &board) const;
    const vector<int> &getRoads(Board &board) const;

    const vector<int> &getCitiesVec(Board &board) const;

    const vector<int> &getSettlementsVec(Board &board) const;

    void getResources() const;
    void addResource(const string &resource, int amount);
    // void removeResource(const string &resource, int amount);

    bool canbuySettlement();
    bool canbuyCity();
    bool canbuyRoad();

    void rollDice(Board &board);

    void chooseDevelopmentCard(Board &board);

    // Vector to hold the development cards
    vector<string> developmentCards;

    // Function to trade resources with other players
    void tradeResources(Board &board, int player, string resource1, int amount, string resource2, int amount2);

    // Function to use Knight Development Card
    void useKnight(Board &board);

    // Function to use Road Building Development Card
    void useRoadBuilding(Board &board, int vertexIndex1, int vertexIndex2, int vertexIndex3, int vertexIndex4);

    // Function to use Year of Plenty Development Card
    void useYearOfPlenty(string resource1, string resource2);

    // Function to use Monopoly Development Card
    void useMonopoly(Board &board, string resource);

    // Function to discard half of the resources of a player
    void discardResources(Board &board);

    // Vector to hold the resources
    vector<pair<string, int>> resources;

    // int to get the winner of the game
    int winner;

    // int for the number of knights played
    int knightsPlayed = 0;

private:
    int id;

    // Name of the player
    string name;
    // Number of points the player has
    int points;
    // Vector to hold the settlements
    vector<int> settlements;
    // Vector to hold the cities
    vector<int> cities;
    // Vector to hold the roads
    vector<int> roads;

    // int to keep track of the number of development cards
    int developmentCardCount = 0;
};

#endif // PLAYER_HPP
