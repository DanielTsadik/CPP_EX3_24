#include "Player.hpp"
#include "Board.hpp"
#include <iostream>
#include "DevelopmentCard.hpp"
#include "Board.hpp"

Player::Player(int id, const std::string &name)
    : id(id), name(name), points(0)
{
    resources.resize(5);
    resources[0] = std::make_pair("Wood", 0);
    resources[1] = std::make_pair("Brick", 0);
    resources[2] = std::make_pair("Wool", 0);
    resources[3] = std::make_pair("Wheat", 0);
    resources[4] = std::make_pair("Ore", 0);
}

int Player::getId() const
{
    return id;
}

const std::string &Player::getName() const
{
    return name;
}

bool Player::canbuySettlement()
{

    std::cout << resources[0].second << " " << resources[1].second << " " << resources[2].second << " " << resources[3].second << " " << resources[4].second << std::endl;
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
    std::cout << "Player " << this->getName() << " rolled a " << diceRoll << std::endl;
    board.giveResources(diceRoll);
}

void Player::placeInitialSettlementAndRoad(int vertexIndex, int vertexIndex2, Board &board)
{
    if (board.canPlaceInitialSettlementAndRoad(*this, vertexIndex, vertexIndex2))
    {
        settlements.push_back(vertexIndex);
        roads.push_back(board.getEdge(vertexIndex, vertexIndex2));
        std::cout << this->getName() << " placed an initial settlement on vertex " << vertexIndex << " and a road between vertices " << vertexIndex << " and " << vertexIndex2 << std::endl;
    }
    else
    {
        std::cout << this->getName() << " cannot place an initial settlement on vertex " << vertexIndex << " and a road between vertices " << vertexIndex << " and " << vertexIndex2 << std::endl;
    }
}

void Player::placeSettlement(int vertexIndex, Board &board)
{
    std::cout << resources[0].second << " " << resources[1].second << " " << resources[2].second << " " << resources[3].second << " " << resources[4].second << std::endl;

    if (!canbuySettlement())
    {
        std::cout << "Player " << this->getName() << " cannot place a settlement on vertex " << vertexIndex << " because he is broke" << std::endl;
        return;
    }

    if (board.canPlaceSettlement(this->getId(), vertexIndex))
    {
        settlements.push_back(vertexIndex);
        std::cout << "Player " << this->getName() << " placed a settlement on vertex " << vertexIndex << std::endl;
        for (int i = 0; i < 4; i++)
        {
            resources[i].second -= 1;
        }
        points += 1;
    }
    else
    {
        std::cout << "Player " << this->getName() << " cannot place a settlement on vertex " << vertexIndex << std::endl;
    }
}

void Player::upgradeToCity(int vertexIndex, Board &board)
{
    if (!canbuyCity())
    {
        std::cout << "Player " << this->getName() << " cannot upgrade a settlement to a city on vertex " << vertexIndex << "because he is broke" << std::endl;
        return;
    }
    if (board.canPlaceCity(this->getId(), vertexIndex))
    {
        cities.push_back(vertexIndex);
        std::cout << "Player " << this->getName() << " upgraded a settlement to a city on vertex " << vertexIndex << std::endl;
        resources[3].second -= 2;
        resources[4].second -= 3;
        points += 1;
    }
    else
    {
        std::cout << "Player " << this->getName() << " cannot upgrade a settlement to a city on vertex " << vertexIndex << std::endl;
    }
}

void Player::placeRoad(int vertexIndex1, int vertexIndex2, Board &board)
{
    if (!canbuyRoad())
    {
        std::cout << "Player " << this->getName() << " cannot place a road between vertices " << vertexIndex1 << " and " << vertexIndex2 << "because he is broke" << std::endl;
        return;
    }
    if (board.canPlaceRoad(this->getId(), vertexIndex1, vertexIndex2))
    {
        roads.push_back(board.getEdge(vertexIndex1, vertexIndex2));
        std::cout << "Player " << this->getName() << " placed a road between vertices " << vertexIndex1 << " and " << vertexIndex2 << std::endl;
        resources[0].second -= 1;
        resources[1].second -= 1;
    }
    else
    {
        std::cout << "Player " << this->getName() << " cannot place a road between vertices " << vertexIndex1 << " and " << vertexIndex2 << std::endl;
    }
}

void Player::buyDevelopmentCard()
{
    if (resources[2].second >= 1 && resources[3].second >= 1 && resources[4].second >= 1)
    {
        resources[2].second -= 1;
        resources[3].second -= 1;
        resources[4].second -= 1;
        std::cout << "Player " << this->getName() << " bought a development card" << std::endl;
        developmentCardCount++;
    }
    else
    {
        std::cout << "Player " << this->getName() << " cannot buy a development card because he is broke" << std::endl;
    }
}

void Player::getSettlements(Board &board) const
{
    std::cout << "Player " << this->getName() << " has settlements on vertices: ";
    for (int i = 0; i < (int)settlements.size(); i++)
    {
        std::cout << settlements[i] << " ";
    }
}

void Player::getCities(Board &board) const
{
    std::cout << "Player " << this->getName() << " has cities on vertices: ";
    for (int i = 0; i < (int)cities.size(); i++)
    {
        std::cout << cities[i] << " ";
    }
}

const std::vector<int> &Player::getRoads(Board &board) const
{
    return roads;
}

void Player::getResources() const
{
    std::cout << "Player " << this->getName() << " has resources: \n";
    for (int i = 0; i < 5; i++)
    {
        std::cout << resources[i].first << ": " << resources[i].second << " \n";
    }
}

void Player::addResource(const std::string &resource, int amount)
{
    for (int i = 0; i < 5; i++)
    {
        if (resources[i].first == resource)
        {
            std::cout << "checking if the player has the resource\n";
            std::cout << "Player " << this->getName() << " got " << amount << " " << resource << std::endl;
            resources[i].second += amount;
            std::cout << "Player " << this->getName() << " now has " << resources[i].second << " " << resource << std::endl;
            std::cout << "Player " << this->getName() << " now has " << resources[i].second << " " << resource << std::endl;
            // print the amount of resources the player has
            std::cout << "Player " << this->getName() << " has " << resources[i].second << " " << resource << std::endl;
        }
    }
    std::cout << resources[0].second << " " << resources[1].second << " " << resources[2].second << " " << resources[3].second << " " << resources[4].second << std::endl;
}

// A function that took 1 random development card from the deck and gave it to the player. the card will be deleted from the deck
// the deck is already shuffled, so in here we will just take the first card from the deck and give it to the player
// also, we will delete the card from the deck
void Player::chooseDevelopmentCard(Board &board)
{
    if (board.developmentCards.size() == 0)
    {
        std::cout << "No more development cards in the deck" << std::endl;
        return;
    }
    board.drawDevelopmentCard(this->getId());
    std::string card = this->developmentCards.back();
    // print the development card that the player got
    std::cout << "Player " << this->getName() << " got a:" << card << std::endl;
    developmentCardCount++;

    if (card == "Victory Point")
    {
        this->points += 1;
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
            // check the number of knights played for the largest army
            if (knightsPlayed > board.biggestArmy)
            {
                if (board.biggestArmyIndex != -1 && board.biggestArmyIndex != this->getId())
                {
                    board.players[board.biggestArmyIndex].points -= 2;
                    board.biggestArmy = knightsPlayed;
                    board.biggestArmyIndex = this->getId();
                    points += 2;
                }
                else if (board.biggestArmyIndex == -1)
                {
                    board.biggestArmy = knightsPlayed;
                    board.biggestArmyIndex = this->getId();
                    points += 2;
                }
            }
            // delete the knight card from the player's deck
            developmentCards.erase(developmentCards.begin() + i);
            developmentCardCount--;
        }
    }
    std::cout << "Player " << this->getName() << " does not have a knight card" << std::endl;
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
            }
        }
    }
    std::cout << "Player " << this->getName() << " does not have a road building card" << std::endl;
}

void Player::useYearOfPlenty(std::string resource1, std::string resource2)
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
        }
    }
    std::cout << "Player " << this->getName() << " does not have a year of plenty card" << std::endl;
}

void Player::useMonopoly(Board &board, std::string resource)
{
    // check if the player has a monopoly card
    for (int i = 0; i < developmentCardCount; i++)
    {
        if (developmentCards[i] == "Monopoly")
        {
            // check if the player can get the resources
            for (int j = 0; j < 3; j++)
            {
                if (board.players[j].getId() != this->getId())
                {
                    for (int k = 0; (long unsigned int)k < board.players[j].resources.size(); k++)
                    {
                        if (board.players[j].resources[k].first == resource)
                        {
                            addResource(resource, board.players[j].resources[k].second);
                            board.players[j].resources[k].second = 0;
                        }
                    }
                }
            }
            // delete the monopoly card from the player's deck
            developmentCards.erase(developmentCards.begin() + i);
            developmentCardCount--;
        }
    }
    std::cout << "Player " << this->getName() << " does not have a monopoly card" << std::endl;
}

// A function that allows the player to trade resources with other players
// resorce1 is the resource that the player wants to get from the other player
void Player::tradeResources(Board &board, int player, std::string resource1, int amount, std::string resource2, int amount2)
{
    // check if the player has the resources
    for (int i = 0; i < 5; i++)
    {
        if (resources[i].first == resource1 && resources[i].second >= amount)
        {
            // check if the other player has the resources
            for (int j = 0; j < 5; j++)
            {
                if (board.players[player].resources[j].first == resource2 && board.players[player].resources[j].second >= amount2)
                {
                    // trade the resources
                    resources[i].second += amount;
                    resources[j].second -= amount;
                    board.players[player].resources[j].second += amount2;
                    board.players[player].resources[i].second -= amount2;
                    std::cout << "Player " << this->getName() << " traded " << amount << " " << resource1 << " with player " << board.players[player].getName() << " for " << amount2 << " " << resource2 << std::endl;
                    return;
                }
            }
        }
    }
}