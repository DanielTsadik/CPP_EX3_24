#include "Player.hpp"
#include "Board.hpp"
#include <iostream>
#include "DevelopmentCard.hpp"
#include "Board.hpp"

Player::Player(int id, const string &name)
    : id(id), name(name)
{
    resources.resize(5);
    resources[0] = make_pair("Wood", 0);
    resources[1] = make_pair("Brick", 0);
    resources[2] = make_pair("Wool", 0);
    resources[3] = make_pair("Wheat", 0);
    resources[4] = make_pair("Ore", 0);
    points = 2;
    developmentCardCount = 0;
    knightsPlayed = 0;
    winner = -1;
}

int Player::getId() const
{
    return id;
}

const string &Player::getName() const
{
    return name;
}

bool Player::canbuySettlement()
{
    if (resources[0].second >= 1 && resources[1].second >= 1 && resources[2].second >= 1 && resources[3].second >= 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Player::canbuyCity()
{
    if (resources[3].second >= 2 && resources[4].second >= 3)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Player::canbuyRoad()
{
    if (resources[0].second >= 1 && resources[1].second >= 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Player::rollDice(Board &board)
{
    int diceRoll = rand() % 6 + 1 + rand() % 6 + 1;
    if (diceRoll == 7)
    {
        cout << "Player " << this->getName() << " rolled a 7" << endl;
        // every player with more than 7 resources will have to discard half of his resources
        discardResources(board);
    }
    else
    {
        cout << "Player " << this->getName() << " rolled a " << diceRoll << endl;

        board.giveResources(board.players, diceRoll);
    }
}

void Player::discardResources(Board &board)
{
    for (int i = 0; i < 3; i++)
    {
        // check if the player has more than 7 resources
        int totalResources = board.players[i]->resources[0].second + board.players[i]->resources[1].second + board.players[i]->resources[2].second + board.players[i]->resources[3].second + board.players[i]->resources[4].second;
        if (totalResources > 7)
        {
            // calculate the number of resources to discard
            int resourcesToDiscard = totalResources / 2;

            // first, discard half of each resource type (rounded down)
            for (int j = 0; j < 5; j++)
            {
                int discardFromThisResource = board.players[i]->resources[j].second / 2;
                board.players[i]->resources[j].second -= discardFromThisResource;
                resourcesToDiscard -= discardFromThisResource;
            }

            // if there are still resources to discard, continue discarding one by one from each resource type
            int j = 0;
            while (resourcesToDiscard > 0)
            {
                if (board.players[i]->resources[j].second > 0)
                {
                    board.players[i]->resources[j].second--;
                    resourcesToDiscard--;
                }
                j = (j + 1) % 5; // move to the next resource type, wrap around to the first one if necessary
            }

            // print the resources that the player has after discarding
            cout << "Player " << board.players[i]->getName() << " now has resources: Wood: " << board.players[i]->resources[0].second << ", Brick: " << board.players[i]->resources[1].second << ", Wool: " << board.players[i]->resources[2].second << ", Wheat: " << board.players[i]->resources[3].second << ", Ore: " << board.players[i]->resources[4].second << endl;
        }
    }
}

void Player::placeInitialSettlementAndRoad(int vertexIndex, int vertexIndex2, Board &board)
{
    if (board.canPlaceInitialSettlementAndRoad(*this, vertexIndex, vertexIndex2))
    {
        settlements.push_back(vertexIndex);
        roads.push_back(board.getEdge(vertexIndex, vertexIndex2));
        cout << this->getName() << " placed an initial settlement on vertex " << vertexIndex << " and a road between vertices " << vertexIndex << " and " << vertexIndex2 << "\n"
                  << endl;
    }
    else
    {
        cout << this->getName() << " cannot place an initial settlement on vertex " << vertexIndex << " and a road between vertices " << vertexIndex << " and " << vertexIndex2 << endl;
    }
}

void Player::placeSettlement(int vertexIndex, Board &board)
{
    if (!canbuySettlement())
    {
        cout << "Player " << this->getName() << " cannot place a settlement because he is broke" << endl;
        return;
    }

    if (board.canPlaceSettlement(this->getId(), vertexIndex))
    {
        settlements.push_back(vertexIndex);
        cout << "Player " << this->getName() << " placed a settlement on vertex " << vertexIndex << endl;
        for (int i = 0; i < 4; i++)
        {
            resources[i].second -= 1;
        }
        points += 1;
        // print the resources that the player has after placing the settlement
        cout << "Player " << this->getName() << " now has resources: Wood: " << resources[0].second << ", Brick: " << resources[1].second << ", Wool: " << resources[2].second << ", Wheat: " << resources[3].second << ", Ore: " << resources[4].second << endl;
        // print the points that the player has after placing the settlement
        cout << "Player " << this->getName() << " now has " << points << " points \n"
                  << endl;
        // check if the player won the game
        if (points >= 10)
        {
            // make sure no one else won the game
            if (board.winnerIndex == -1)
            {
                board.winnerIndex = this->getId();
                cout << "Player " << this->getName() << " won the game!" << endl;
            } 
        }
    }
    else
    {
        cout << "Player " << this->getName() << " cannot place a settlement on vertex " << vertexIndex << endl;
    }
}

void Player::upgradeToCity(int vertexIndex, Board &board)
{
    if (!canbuyCity())
    {
        cout << "Player " << this->getName() << " cannot upgrade a settlement to a city on vertex " << vertexIndex << " because he is broke" << endl;
        return;
    }
    if (board.canPlaceCity(this->getId(), vertexIndex))
    {
        cities.push_back(vertexIndex);
        cout << "Player " << this->getName() << " upgraded a settlement to a city on vertex " << vertexIndex << endl;
        resources[3].second -= 2;
        resources[4].second -= 3;
        points += 1;
        // print the resources that the player has after upgrading the settlement to a city
        cout << "Player " << this->getName() << " now has resources: Wood: " << resources[0].second << ", Brick: " << resources[1].second << ", Wool: " << resources[2].second << ", Wheat: " << resources[3].second << ", Ore: " << resources[4].second << endl;
        // print the points that the player has after upgrading the settlement to a city
        cout << "Player " << this->getName() << " now has " << points << " points \n"
                  << endl;
        if (points >= 10)
        {
            // make sure no one else won the game
            if (board.winnerIndex == -1)
            {
                board.winnerIndex = this->getId();
                cout << "Player " << this->getName() << " won the game!" << endl;
            }
        }
    }
    else
    {
        cout << "Player " << this->getName() << " cannot upgrade a settlement to a city on vertex " << vertexIndex << endl;
    }
}

void Player::placeRoad(int vertexIndex1, int vertexIndex2, Board &board)
{
    if (!canbuyRoad())
    {
        cout << "Player " << this->getName() << " cannot place a road between vertices " << vertexIndex1 << " and " << vertexIndex2 << " because he is broke" << endl;
        return;
    }
    if (board.canPlaceRoad(this->getId(), vertexIndex1, vertexIndex2))
    {
        roads.push_back(board.getEdge(vertexIndex1, vertexIndex2));
        cout << "Player " << this->getName() << " placed a road between vertices " << vertexIndex1 << " and " << vertexIndex2 << endl;
        resources[0].second -= 1;
        resources[1].second -= 1;
        // print the resources that the player has after placing the road
        cout << "Player " << this->getName() << " now has resources: Wood: " << resources[0].second << ", Brick: " << resources[1].second << ", Wool: " << resources[2].second << ", Wheat: " << resources[3].second << ", Ore: " << resources[4].second << endl;
    }
    else
    {
        cout << "Player " << this->getName() << " cannot place a road between vertices " << vertexIndex1 << " and " << vertexIndex2 << endl;
    }
}

void Player::canBuyDevelopmentCard()
{
    if (resources[2].second >= 1 && resources[3].second >= 1 && resources[4].second >= 1)
    {
        resources[2].second -= 1;
        resources[3].second -= 1;
        resources[4].second -= 1;
        cout << "Player " << this->getName() << " bought a development card" << endl;
        // print the resources that the player has after buying the development card
        cout << "Player " << this->getName() << " now has resources: Wood: " << resources[0].second << ", Brick: " << resources[1].second << ", Wool: " << resources[2].second << ", Wheat: " << resources[3].second << ", Ore: " << resources[4].second << endl;
        developmentCardCount++;
    }
    else
    {
        cout << "Player " << this->getName() << " cannot buy a development card because he is broke" << endl;
    }
}

void Player::getSettlements(Board &board) const
{
    cout << "Player " << this->getName() << " has settlements on vertices: ";
    for (int i = 0; i < (int)settlements.size(); i++)
    {
        cout << settlements[i] << ", ";
    }
    cout << endl;
}

void Player::getCities(Board &board) const
{
    cout << "Player " << this->getName() << " has cities on vertices: ";
    for (int i = 0; i < (int)cities.size(); i++)
    {
        cout << cities[i] << " ";
    }
}

const vector<int> &Player::getRoads(Board &board) const
{
    return roads;
}

void Player::getResources() const
{
    cout << "Player " << this->getName() << " has resources: \n";
    for (int i = 0; i < 5; i++)
    {
        cout << resources[i].first << ": " << resources[i].second << " \n";
    }
}

void Player::addResource(const string &resource, int amount)
{
    for (int i = 0; i < 5; i++)
    {
        if (resources[i].first == resource)
        {
            cout << "Player " << this->getName() << " got " << amount << " " << resource << endl;
            resources[i].second += amount;
            cout << "Player " << this->getName() << " now has " << resources[i].second << " " << resource << endl;
        }
    }
    // print the resources that the player got:
    cout << "Player " << this->getName() << " got the next resources: Wood: " << resources[0].second << ", Brick: " << resources[1].second << ", Wool: " << resources[2].second << ", Wheat: " << resources[3].second << ", Ore: " << resources[4].second << endl;
}

// A function that took 1 random development card from the deck and gave it to the player. the card will be deleted from the deck
// the deck is already shuffled, so in here we will just take the first card from the deck and give it to the player
// also, we will delete the card from the deck
void Player::chooseDevelopmentCard(Board &board)
{
    if (board.developmentCards.size() == 0)
    {
        cout << "No more development cards in the deck" << endl;
        return;
    }
    // check if the player has the resources to buy a development card
    if (resources[2].second < 1 || resources[3].second < 1 || resources[4].second < 1)
    {
        cout << "Player " << this->getName() << " cannot buy a development card because he is broke" << endl;
        return;
    }
    board.drawDevelopmentCard(this->getId());
    string card = this->developmentCards.back();
    // print the development card that the player got
    cout << "Player " << this->getName() << " bought a development card, and got a: " << card << " card" << endl;
    developmentCardCount++;
    // subtract the resources that the player used to buy the development card
    resources[2].second -= 1;
    resources[3].second -= 1;
    resources[4].second -= 1;

    // print the resources that the player has after buying the development card
    cout << "Player " << this->getName() << " now has resources: Wood: " << resources[0].second << ", Brick: " << resources[1].second << ", Wool: " << resources[2].second << ", Wheat: " << resources[3].second << ", Ore: " << resources[4].second << endl;

    if (card == "Victory Point")
    {
        this->points += 1;
        if (points >= 10)
        {
            // make sure no one else won the game
            if (board.winnerIndex == -1)
            {
                board.winnerIndex = this->getId();
                cout << "Player " << this->getName() << " won the game!" << endl;
            }
        }
    }
}

void Player::useKnight(Board &board)
{
    // check if the player has a knight card
    for (int i = 0; i < developmentCardCount; i++)
    {
        if (developmentCards[i] == "Knight")
        {
            knightsPlayed++;
            // print that the player played a knight card
            cout << "Player " << this->getName() << " played a knight card" << endl;
            // print the number of knights played by the player
            cout << "Player " << this->getName() << " played " << knightsPlayed << " knights" << endl;
            // check the number of knights played for the largest army
            if (knightsPlayed > board.biggestArmy)
            {
                if (board.biggestArmyIndex != -1 && board.biggestArmyIndex != this->getId())
                {
                    board.players[board.biggestArmyIndex]->points -= 2;
                    board.biggestArmy = knightsPlayed;
                    board.biggestArmyIndex = this->getId();
                    points += 2;
                    if (points >= 10)
                    {
                        // make sure no one else won the game
                        if (board.winnerIndex == -1)
                        {
                            board.winnerIndex = this->getId();
                            cout << "Player " << this->getName() << " won the game!" << endl;
                        }
                    }
                }
                else if (board.biggestArmyIndex == -1)
                {
                    board.biggestArmy = knightsPlayed;
                    board.biggestArmyIndex = this->getId();
                    points += 2;
                    if (points >= 10)
                    {
                        // make sure no one else won the game
                        if (board.winnerIndex == -1)
                        {
                            board.winnerIndex = this->getId();
                            cout << "Player " << this->getName() << " won the game!" << endl;
                        }
                    }
                }
            }
            // delete the knight card from the player's deck
            developmentCards.erase(developmentCards.begin() + i);
            developmentCardCount--;
            return;
        }
    }
    cout << "Player " << this->getName() << " does not have a knight card" << endl;
}

void Player::useRoadBuilding(Board &board, int vertexIndex1, int vertexIndex2, int vertexIndex3, int vertexIndex4)
{
    // check if the player has a road building card
    for (int i = 0; i < developmentCardCount; i++)
    {
        if (developmentCards[i] == "Road Placement")
        {
            // check if the player can place the roads
            if (board.canPlaceRoad(this->getId(), vertexIndex1, vertexIndex2) && board.canPlaceRoad(this->getId(), vertexIndex3, vertexIndex4))
            {
                placeRoad(vertexIndex1, vertexIndex2, board);
                placeRoad(vertexIndex3, vertexIndex4, board);
                // delete the road building card from the player's deck
                developmentCards.erase(developmentCards.begin() + i);
                developmentCardCount--;
                return;
            }
        }
    }
    cout << "Player " << this->getName() << " does not have a road building card" << endl;
}

void Player::useYearOfPlenty(string resource1, string resource2)
{
    // check if the player has a year of plenty card
    for (int i = 0; i < developmentCardCount; i++)
    {
        if (developmentCards[i] == "Year of Plenty")
        {
            // check if the player can get the resources
            addResource(resource1, 1);
            addResource(resource2, 1);
            // delete the year of plenty card from the player's deck
            developmentCards.erase(developmentCards.begin() + i);
            developmentCardCount--;
            return;
        }
    }
    cout << "Player " << this->getName() << " does not have a year of plenty card" << endl;
}

void Player::useMonopoly(Board &board, string resource)
{
    // check if the player has a monopoly card
    for (int i = 0; i < developmentCardCount; i++)
    {
        if (developmentCards[i] == "Monopoly")
        {
            // check if the player can get the resources
            for (int j = 0; j < 3; j++)
            {
                if (board.players[j]->getId() != this->getId())
                {
                    for (int k = 0; (long unsigned int)k < board.players[j]->resources.size(); k++)
                    {
                        if (board.players[j]->resources[k].first == resource)
                        {
                            addResource(resource, board.players[j]->resources[k].second);
                            board.players[j]->resources[k].second = 0;
                        }
                    }
                }
            }
            // delete the monopoly card from the player's deck
            developmentCards.erase(developmentCards.begin() + i);
            developmentCardCount--;
            return;
        }
    }
    cout << "Player " << this->getName() << " does not have a monopoly card" << endl;
}

// A function that allows the player to trade resources with other players
// resorce1 is the resource that the player wants to get from the other player
void Player::tradeResources(Board &board, int player, string resource1, int amount, string resource2, int amount2)
{
    // check if the player has the resources
    for (int i = 0; i < 5; i++)
    {
        if (resources[i].first == resource2 && resources[i].second >= amount2)
        {
            // check if the other player has the resources
            for (int j = 0; j < 5; j++)
            {
                if (board.players[player - 1]->resources[j].first == resource1 && board.players[player - 1]->resources[j].second >= amount)
                {
                    // trade the resources
                    resources[j].second += amount2;
                    resources[i].second -= amount2;
                    board.players[player - 1]->resources[i].second += amount;
                    board.players[player - 1]->resources[j].second -= amount;
                    cout << "Player " << this->getName() << " traded " << amount << " " << resource1 << " with player " << board.players[player - 1]->getName() << " for " << amount2 << " " << resource2 << endl;
                    // print the resources that the player has after trading
                    cout << "Player " << this->getName() << " now has resources: Wood: " << resources[0].second << ", Brick: " << resources[1].second << ", Wool: " << resources[2].second << ", Wheat: " << resources[3].second << ", Ore: " << resources[4].second << endl;
                    // print the resources that the other player has after trading
                    cout << "Player " << board.players[player - 1]->getName() << " now has resources: Wood: " << board.players[player - 1]->resources[0].second << ", Brick: " << board.players[player - 1]->resources[1].second << ", Wool: " << board.players[player - 1]->resources[2].second << ", Wheat: " << board.players[player - 1]->resources[3].second << ", Ore: " << board.players[player - 1]->resources[4].second << endl;
                    return;
                }
            }
        }
    }
    // print that the trade was not successful
    cout << "Player " << this->getName() << " cannot trade " << amount << " " << resource1 << " with player " << board.players[player - 1]->getName() << " for " << amount2 << " " << resource2 << endl;
}