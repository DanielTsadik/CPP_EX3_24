// Daniel Tsadik
// Tsadik88@gmail.com   
// 209307727

#include "Board.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Plot.hpp"
#include <iostream>
#include <vector>
#include <tuple>
#include "DevelopmentCard.hpp"
#include <algorithm>
#include <random> // for default_random_engine and random_device
#include <chrono> // for system_clock


// Constructor for the Board class
Board::Board(Player &player1, Player &player2, Player &player3)
{
    cout << "Initializing board..." << endl;

    // Add players to the players vector
    players.push_back(&player1);
    players.push_back(&player2);
    players.push_back(&player3);

    // Define resource types, numbers, and indices for the fixed board setup
    vector<tuple<string, int, size_t>> plotData = {
        {"Mountains", 10, 0}, {"Pasture", 2, 1}, {"Forest", 9, 2}, {"Agricultural", 12, 3}, {"Hills", 6, 4}, {"Pasture", 4, 5}, {"Hills", 10, 6}, {"Agricultural", 9, 7}, {"Forest", 11, 8}, {"Desert", 7, 9}, {"Forest", 3, 10}, {"Mountains", 8, 11}, {"Forest", 8, 12}, {"Mountains", 3, 13}, {"Agricultural", 4, 14}, {"Pasture", 5, 15}, {"Hills", 5, 16}, {"Agricultural", 6, 17}, {"Pasture", 11, 18}};

    // Create plots with fixed resources and numbers
    for (int i = 0; i < 19; i++)
    {
        plots.emplace_back(Plot(get<0>(plotData[i]), get<1>(plotData[i]), get<2>(plotData[i])));
    }

    // Initialize vertices (54 vertices)
    vertices.reserve(54);
    for (size_t i = 0; i < 54; ++i)
    {
        vertices.emplace_back(Vertex(i));
    }

    // Manually establish connections between plots and vertices based on your specified order
    vector<vector<size_t>> vertexMapping = {
        {0, 1, 2, 10, 9, 8}, {2, 3, 4, 12, 11, 10}, {4, 5, 6, 14, 13, 12}, {7, 8, 9, 19, 18, 17}, {9, 10, 11, 21, 20, 19}, {11, 12, 13, 23, 22, 21}, {13, 14, 15, 25, 24, 22}, {16, 17, 18, 29, 28, 27}, {18, 19, 20, 31, 30, 29}, {20, 21, 22, 33, 32, 31}, {22, 23, 24, 35, 34, 33}, {24, 25, 26, 37, 36, 35}, {28, 29, 30, 40, 39, 38}, {30, 31, 32, 42, 41, 40}, {32, 33, 34, 44, 43, 42}, {34, 35, 36, 46, 45, 44}, {39, 40, 41, 49, 48, 47}, {41, 42, 43, 51, 50, 49}, {43, 44, 45, 53, 52, 51}};
    // Set the vertices for each plot
    for (size_t i = 0; i < 19; i++)
    {
        for (size_t j = 0; j < 6; j++)
        {
            plots[i].setVertex(vertices[vertexMapping[i][j]]);
        }
    }

    // Manually set up vertex neighbors to handle roads
    vertices[0].addNeighbor(&vertices[1]);
    vertices[0].addNeighbor(&vertices[8]);
    vertices[1].addNeighbor(&vertices[0]);
    vertices[1].addNeighbor(&vertices[2]);
    vertices[2].addNeighbor(&vertices[1]);
    vertices[2].addNeighbor(&vertices[3]);
    vertices[2].addNeighbor(&vertices[10]);
    vertices[3].addNeighbor(&vertices[2]);
    vertices[3].addNeighbor(&vertices[4]);
    vertices[4].addNeighbor(&vertices[3]);
    vertices[4].addNeighbor(&vertices[5]);
    vertices[4].addNeighbor(&vertices[12]);
    vertices[5].addNeighbor(&vertices[4]);
    vertices[5].addNeighbor(&vertices[6]);
    vertices[6].addNeighbor(&vertices[5]);
    vertices[6].addNeighbor(&vertices[14]);
    vertices[7].addNeighbor(&vertices[8]);
    vertices[8].addNeighbor(&vertices[7]);
    vertices[8].addNeighbor(&vertices[9]);
    vertices[8].addNeighbor(&vertices[0]);
    vertices[9].addNeighbor(&vertices[8]);
    vertices[9].addNeighbor(&vertices[10]);
    vertices[9].addNeighbor(&vertices[19]);
    vertices[10].addNeighbor(&vertices[9]);
    vertices[10].addNeighbor(&vertices[2]);
    vertices[10].addNeighbor(&vertices[11]);
    vertices[11].addNeighbor(&vertices[10]);
    vertices[11].addNeighbor(&vertices[12]);
    vertices[11].addNeighbor(&vertices[21]);
    vertices[12].addNeighbor(&vertices[11]);
    vertices[12].addNeighbor(&vertices[4]);
    vertices[12].addNeighbor(&vertices[13]);
    vertices[13].addNeighbor(&vertices[12]);
    vertices[13].addNeighbor(&vertices[14]);
    vertices[13].addNeighbor(&vertices[23]);
    vertices[14].addNeighbor(&vertices[13]);
    vertices[14].addNeighbor(&vertices[6]);
    vertices[14].addNeighbor(&vertices[15]);
    vertices[15].addNeighbor(&vertices[14]);
    vertices[15].addNeighbor(&vertices[25]);
    vertices[16].addNeighbor(&vertices[17]);
    vertices[17].addNeighbor(&vertices[16]);
    vertices[17].addNeighbor(&vertices[18]);
    vertices[17].addNeighbor(&vertices[7]);
    vertices[18].addNeighbor(&vertices[17]);
    vertices[18].addNeighbor(&vertices[19]);
    vertices[18].addNeighbor(&vertices[29]);
    vertices[19].addNeighbor(&vertices[18]);
    vertices[19].addNeighbor(&vertices[9]);
    vertices[19].addNeighbor(&vertices[20]);
    vertices[20].addNeighbor(&vertices[19]);
    vertices[20].addNeighbor(&vertices[21]);
    vertices[20].addNeighbor(&vertices[31]);
    vertices[21].addNeighbor(&vertices[20]);
    vertices[21].addNeighbor(&vertices[11]);
    vertices[21].addNeighbor(&vertices[22]);
    vertices[22].addNeighbor(&vertices[21]);
    vertices[22].addNeighbor(&vertices[23]);
    vertices[22].addNeighbor(&vertices[33]);
    vertices[23].addNeighbor(&vertices[22]);
    vertices[23].addNeighbor(&vertices[13]);
    vertices[23].addNeighbor(&vertices[24]);
    vertices[24].addNeighbor(&vertices[23]);
    vertices[24].addNeighbor(&vertices[25]);
    vertices[24].addNeighbor(&vertices[35]);
    vertices[25].addNeighbor(&vertices[24]);
    vertices[25].addNeighbor(&vertices[15]);
    vertices[25].addNeighbor(&vertices[26]);
    vertices[26].addNeighbor(&vertices[25]);
    vertices[26].addNeighbor(&vertices[37]);
    vertices[27].addNeighbor(&vertices[28]);
    vertices[28].addNeighbor(&vertices[27]);
    vertices[28].addNeighbor(&vertices[29]);
    vertices[28].addNeighbor(&vertices[16]);
    vertices[29].addNeighbor(&vertices[28]);
    vertices[29].addNeighbor(&vertices[18]);
    vertices[29].addNeighbor(&vertices[30]);
    vertices[30].addNeighbor(&vertices[29]);
    vertices[30].addNeighbor(&vertices[31]);
    vertices[30].addNeighbor(&vertices[40]);
    vertices[31].addNeighbor(&vertices[30]);
    vertices[31].addNeighbor(&vertices[20]);
    vertices[31].addNeighbor(&vertices[32]);
    vertices[32].addNeighbor(&vertices[31]);
    vertices[32].addNeighbor(&vertices[33]);
    vertices[32].addNeighbor(&vertices[42]);
    vertices[33].addNeighbor(&vertices[32]);
    vertices[33].addNeighbor(&vertices[22]);
    vertices[33].addNeighbor(&vertices[34]);
    vertices[34].addNeighbor(&vertices[33]);
    vertices[34].addNeighbor(&vertices[35]);
    vertices[34].addNeighbor(&vertices[44]);
    vertices[35].addNeighbor(&vertices[34]);
    vertices[35].addNeighbor(&vertices[24]);
    vertices[35].addNeighbor(&vertices[36]);
    vertices[36].addNeighbor(&vertices[35]);
    vertices[36].addNeighbor(&vertices[37]);
    vertices[36].addNeighbor(&vertices[46]);
    vertices[37].addNeighbor(&vertices[36]);
    vertices[37].addNeighbor(&vertices[26]);
    vertices[37].addNeighbor(&vertices[38]);
    vertices[38].addNeighbor(&vertices[37]);
    vertices[38].addNeighbor(&vertices[39]);
    vertices[39].addNeighbor(&vertices[38]);
    vertices[39].addNeighbor(&vertices[28]);
    vertices[39].addNeighbor(&vertices[40]);
    vertices[40].addNeighbor(&vertices[39]);
    vertices[40].addNeighbor(&vertices[30]);
    vertices[40].addNeighbor(&vertices[41]);
    vertices[41].addNeighbor(&vertices[40]);
    vertices[41].addNeighbor(&vertices[42]);
    vertices[41].addNeighbor(&vertices[49]);
    vertices[42].addNeighbor(&vertices[41]);
    vertices[42].addNeighbor(&vertices[32]);
    vertices[42].addNeighbor(&vertices[43]);
    vertices[43].addNeighbor(&vertices[42]);
    vertices[43].addNeighbor(&vertices[44]);
    vertices[43].addNeighbor(&vertices[51]);
    vertices[44].addNeighbor(&vertices[43]);
    vertices[44].addNeighbor(&vertices[34]);
    vertices[44].addNeighbor(&vertices[45]);
    vertices[45].addNeighbor(&vertices[44]);
    vertices[45].addNeighbor(&vertices[46]);
    vertices[45].addNeighbor(&vertices[53]);
    vertices[46].addNeighbor(&vertices[45]);
    vertices[46].addNeighbor(&vertices[36]);
    vertices[47].addNeighbor(&vertices[48]);
    vertices[48].addNeighbor(&vertices[47]);
    vertices[48].addNeighbor(&vertices[49]);
    vertices[49].addNeighbor(&vertices[48]);
    vertices[49].addNeighbor(&vertices[41]);
    vertices[49].addNeighbor(&vertices[50]);
    vertices[50].addNeighbor(&vertices[49]);
    vertices[50].addNeighbor(&vertices[51]);
    vertices[51].addNeighbor(&vertices[50]);
    vertices[51].addNeighbor(&vertices[43]);
    vertices[51].addNeighbor(&vertices[52]);
    vertices[52].addNeighbor(&vertices[51]);
    vertices[52].addNeighbor(&vertices[53]);
    vertices[53].addNeighbor(&vertices[52]);
    vertices[53].addNeighbor(&vertices[45]);

    edges.reserve(72);
    for (size_t i = 0; i < 72; ++i)
    {
        edges.emplace_back(Edge(i));
    }

    // Manually establish connections between edges and vertices based on your specified order
    vector<vector<size_t>> edgeMapping = {
        {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {0, 8}, {2, 10}, {4, 12}, {6, 14}, {7, 8}, {8, 9}, {9, 10}, {10, 11}, {11, 12}, {12, 13}, {13, 14}, {14, 15}, {7, 17}, {9, 19}, {11, 21}, {13, 23}, {15, 25}, {16, 17}, {17, 18}, {18, 19}, {19, 20}, {20, 21}, {21, 22}, {22, 23}, {23, 24}, {24, 25}, {25, 26}, {16, 27}, {18, 29}, {20, 31}, {22, 33}, {24, 35}, {26, 37}, {27, 28}, {28, 29}, {29, 30}, {30, 31}, {31, 32}, {32, 33}, {33, 34}, {34, 35}, {35, 36}, {36, 37}, {28, 38}, {30, 40}, {32, 42}, {34, 44}, {36, 46}, {38, 39}, {39, 40}, {40, 41}, {41, 42}, {42, 43}, {43, 44}, {44, 45}, {45, 46}, {39, 47}, {41, 49}, {43, 51}, {45, 53}, {47, 48}, {48, 49}, {49, 50}, {50, 51}, {51, 52}, {52, 53}};

    // Set the vertices for each edge
    for (size_t i = 0; i < edges.size(); ++i)
    {
        edges[i].setVertices(&vertices[edgeMapping[i][0]], &vertices[edgeMapping[i][1]]);
        vertices[edgeMapping[i][0]].addEdge(&edges[i]);
        vertices[edgeMapping[i][1]].addEdge(&edges[i]);
    }

    // initialize the deck of the 25 development cards: 14 knigths, 5 victory points, 2 road building, 2 year of plenty, 2 monopoly
    for (int i = 0; i < 14; i++)
    {
        developmentCards.push_back(DevelopmentCard("Knight"));
    }
    for (int i = 0; i < 5; i++)
    {
        developmentCards.push_back(DevelopmentCard("Victory Point"));
    }
    for (int i = 0; i < 2; i++)
    {
        developmentCards.push_back(DevelopmentCard("Road Placement"));
    }
    for (int i = 0; i < 2; i++)
    {
        developmentCards.push_back(DevelopmentCard("Year Of Plenty"));
    }
    for (int i = 0; i < 2; i++)
    {
        developmentCards.push_back(DevelopmentCard("Monopoly"));
    }

    default_random_engine engine(chrono::system_clock::now().time_since_epoch().count());
    shuffle(developmentCards.begin(), developmentCards.end(), engine);

    // Print message indicating game setup is complete and initial board configuration
    cout << "Game setup is complete. Initial board configuration:" << endl;
    printBoard();
}

const vector<Plot> &Board::getPlots() const
{
    return plots;
}

vector<Vertex> &Board::getVertices()
{
    return vertices;
}

void Board::printBoard() const
{
    for (const Plot &plot : plots)
    {
        cout << "Plot " << plot.getIndex() << ": " << plot.getResource() << " (" << plot.getNumber() << ")\n";
    }
}

int Board::getEdge(size_t vertexIndex1, size_t vertexIndex2)
{
    if (vertexIndex1 > vertexIndex2)
    {
        swap(vertexIndex1, vertexIndex2);
    }
    for (int i = 0; i < 72; i++)
    {
        if (edges[i].getVertex1().getIndex() == vertexIndex1 && edges[i].getVertex2().getIndex() == vertexIndex2)
        {
            return i;
        }
    }
    return -1;
}

void Board::giveResources(vector<Player *> &players, int diceRoll)
{
    for (int i = 0; i < 19; i++)
    {
        if (plots[i].getNumber() == diceRoll)
        {
            cout << "Plot " << i << " has number: " << plots[i].getNumber() << endl;
            const vector<Vertex *> &vertices = plots[i].getVertices();
            for (Vertex *vertex : vertices)
            {
                if (vertex->getOwner() != -1 && vertex->getCity() == -1)
                {
                    if (plots[i].getResource() == "Mountains")
                    {
                        // give the player who owns the vertex a mountain resource
                        int playerId = vertex->getOwner();
                        players[playerId - 1]->addResource("Ore", 1);
                    }
                    else if (plots[i].getResource() == "Pasture")
                    {
                        // give the player who owns the vertex a pasture resource
                        int playerId = vertex->getOwner();
                        players[playerId - 1]->addResource("Wool", 1);
                    }
                    else if (plots[i].getResource() == "Forest")
                    {
                        // give the player who owns the vertex a forest resource
                        int playerId = vertex->getOwner();
                        players[playerId - 1]->addResource("Wood", 1);
                    }
                    else if (plots[i].getResource() == "Agricultural")
                    {
                        // give the player who owns the vertex an agricultural resource
                        int playerId = vertex->getOwner();
                        players[playerId - 1]->addResource("Wheat", 1);
                    }
                    else if (plots[i].getResource() == "Hills")
                    {
                        // give the player who owns the vertex a hills resource
                        int playerId = vertex->getOwner();
                        players[playerId - 1]->addResource("Brick", 1);
                    }
                }
                else if (vertex->getOwner() != -1 && vertex->getCity() == 1)
                {
                    if (plots[i].getResource() == "Mountains")
                    {
                        // give the player who owns the vertex a mountain resource
                        int playerId = vertex->getOwner();
                        players[playerId - 1]->addResource("Ore", 2);
                    }
                    else if (plots[i].getResource() == "Pasture")
                    {
                        // give the player who owns the vertex a pasture resource
                        int playerId = vertex->getOwner();
                        players[playerId - 1]->addResource("Wool", 2);
                    }
                    else if (plots[i].getResource() == "Forest")
                    {
                        // give the player who owns the vertex a forest resource
                        int playerId = vertex->getOwner();
                        players[playerId - 1]->addResource("Wood", 2);
                    }
                    else if (plots[i].getResource() == "Agricultural")
                    {
                        // give the player who owns the vertex an agricultural resource
                        int playerId = vertex->getOwner();
                        players[playerId - 1]->addResource("Wheat", 2);
                    }
                    else if (plots[i].getResource() == "Hills")
                    {
                        // give the player who owns the vertex a hills resource
                        int playerId = vertex->getOwner();
                        players[playerId - 1]->addResource("Brick", 2);
                    }
                }
            }
        }
    }
    cout << "\n"
              << endl;
}

void Board::drawDevelopmentCard(int playerId)
{
    // take the first card from the deck and give it to the player
    players[playerId - 1]->developmentCards.push_back(developmentCards.back().getType());
    developmentCards.erase(developmentCards.begin());
}

bool Board::canPlaceInitialSettlementAndRoad(Player &player, size_t vertexIndex, size_t vertexIndex2)
{
    // Check if vertexIndex is valid
    if (vertexIndex >= vertices.size() || vertexIndex < 0 || vertexIndex2 >= vertices.size() || vertexIndex2 < 0)
    {
        cerr << "Invalid vertex index." << endl;
        return false;
    }

    // Get the vertex at the specified index
    Vertex &vertex = vertices[vertexIndex];

    // Check if the vertex is already occupied by a settlement or city
    if (vertex.getOwner() != -1)
    {
        cerr << "Vertex is already occupied." << endl;
        return false;
    }
    // Check if the vertex is adjacent to a vertex that is already occupied by one of the players
    const vector<Vertex *> &adjacentPlots = vertex.getNeighbors();
    for (const Vertex *adjacentVertex : adjacentPlots)
    {
        if (adjacentVertex->getOwner() != -1)
        {
            cerr << "Adjacent vertex " << adjacentVertex->getIndex() << " already occupied." << endl;
            return false;
        }
    }
    // Check if the edge we are trying to place a road on is occupied
    int edgeIndex = getEdge(vertexIndex, vertexIndex2);
    if (edgeIndex != -1)
    {
        if (edges[edgeIndex].getOwner() != -1)
        {
            cerr << "Edge is already occupied." << endl;
            return false;
        }
    }
    // Set the owner of the vertex to the playerID
    vertex.setOwner(player.getId());

    // Set the owner of the edge to the playerID
    edges[edgeIndex].setOwner(player.getId());

    // int playerId = player.getId();
    // Give the player the resources that the vertex sits on
    for (int i = 0; i < 19; i++)
    {
        const vector<Vertex *> &vertices = plots[i].getVertices();
        for (Vertex *v : vertices)
        {
            if (v->getIndex() == vertexIndex)
            {
                if (plots[i].getResource() == "Mountains")
                {
                    player.addResource("Ore", 1);
                }
                else if (plots[i].getResource() == "Pasture")
                {
                    player.addResource("Wool", 1);
                }
                else if (plots[i].getResource() == "Forest")
                {
                    player.addResource("Wood", 1);
                }
                else if (plots[i].getResource() == "Agricultural")
                {
                    player.addResource("Wheat", 1);
                }
                else if (plots[i].getResource() == "Hills")
                {
                    player.addResource("Brick", 1);
                }
            }
        }
    }

    return true;
}

bool Board::canPlaceSettlement(int playerId, size_t vertexIndex)
{
    // Check if vertexIndex is valid
    if (vertexIndex >= vertices.size() || vertexIndex < 0)
    {
        cerr << "Invalid vertex index." << endl;
        return false;
    }

    // Get the vertex at the specified index
    Vertex &vertex = vertices[vertexIndex];

    // Check if the vertex is already occupied by a settlement or city
    if (vertex.getOwner() != -1)
    {
        cerr << "Vertex is already occupied." << endl;
        return false;
    }

    // Check adjacency of vertecies to the vertex for existing settlements or cities
    const vector<Vertex *> &adjacentPlots = vertex.getNeighbors();
    for (const Vertex *adjacentVertex : adjacentPlots)
    {
        if (adjacentVertex->getOwner() != -1)
        {
            cerr << "Adjacent vertex " << adjacentVertex->getIndex() << " already occupied." << endl;
            return false;
        }
    }

    // check if we have at least one edge that belong to the playerID that connected to the vertex we are trying to place a settlement on
    const vector<Edge *> &adjacentEdges = vertex.getEdges();

    for (const Edge *edge : adjacentEdges)
    {
        if (edge->getOwner() == playerId)
        {
            vertex.setOwner(playerId);
            return true;
        }
    }
    cerr << "No adjacent edges belong to the player." << endl;
    return false;
}

bool Board::canPlaceRoad(int playerId, size_t vertexIndex1, size_t vertexIndex2)
{
    // Check if vertex indices are valid
    if (vertexIndex1 >= vertices.size() || vertexIndex2 >= vertices.size() || vertexIndex1 == vertexIndex2 || vertexIndex1 < 0 || vertexIndex2 < 0)
    {
        cerr << "Invalid vertex indices." << endl;
        return false;
    }

    // Get the vertices at the specified indices
    const Vertex &v1 = vertices[vertexIndex1];
    const Vertex &v2 = vertices[vertexIndex2];

    // Check if the vertices are neighbors
    if (!v1.isNeighbor(v2))
    {
        cerr << "Vertices are not neighbors." << endl;
        return false;
    }

    // Check if the road is already occupied
    const vector<Edge *> &adjacentEdges1 = v1.getEdges();
    const vector<Edge *> &adjacentEdges2 = v2.getEdges();
    for (const Edge *edge1 : adjacentEdges1)
    {
        for (const Edge *edge2 : adjacentEdges2)
        {
            if (edge1 == edge2 && edge1->getOwner() != -1)
            {
                cerr << "Road is already occupied." << endl;
                return false;
            }
        }
    }

    // Check if the player has a settlement or city on one of the vertices
    if (v1.getOwner() == playerId || v2.getOwner() == playerId)
    {
        int edgeIndex = getEdge(vertexIndex1, vertexIndex2);
        if (edgeIndex != -1)
        {
            edges[edgeIndex].setOwner(playerId);
        }
        return true;
    }

    // check if we have at least one edge that belong to the playerID that connected to one of the vertex we are trying to place a settlement on
    for (const Edge *edge1 : adjacentEdges1)
    {
        for (const Edge *edge2 : adjacentEdges2)
        {
            if (edge1->getOwner() == playerId || edge2->getOwner() == playerId)
            {
                int edgeIndex = getEdge(vertexIndex1, vertexIndex2);
                if (edgeIndex != -1)
                {
                    edges[edgeIndex].setOwner(playerId);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::canPlaceCity(int playerId, size_t vertexIndex)
{
    // Check if vertexIndex is valid
    if (vertexIndex >= vertices.size() || vertexIndex < 0)
    {
        cerr << "Invalid vertex index." << endl;
        return false;
    }

    // Get the vertex at the specified index
    Vertex &vertex = vertices[vertexIndex];

    // Check if the vertex is already occupied by a city
    if (vertex.getOwner() != playerId)
    {
        cerr << "Vertex is not occupied by the player." << endl;
        return false;
    }

    // Check if the vertex is already occupied by a city
    if (vertex.getCity() == 1)
    {
        cerr << "Vertex is already occupied by a city." << endl;
        return false;
    }
    vertex.setCity(1);
    return true;
}


void Board::printWinner()
{
    if(winnerIndex != -1)
    {
        cout << "Player " << winnerIndex << " has won the game!" << endl;
    }
    else
    {
        cout << "No winner yet." << endl;
    }
}