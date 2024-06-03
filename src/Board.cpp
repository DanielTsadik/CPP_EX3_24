#include "Board.hpp"
#include <iostream>
#include <random>
#include <algorithm>
#include <array>

Board::Board()
{
    // Define resource types and counts
    std::array<std::string, 19> resourceTypes = {
        "Forest", "Forest", "Forest", "Forest",
        "Hills", "Hills", "Hills",
        "Pasture", "Pasture", "Pasture", "Pasture",
        "Agricultural", "Agricultural", "Agricultural", "Agricultural",
        "Mountains", "Mountains", "Mountains",
        "Desert"};

    // Define plot numbers excluding the desert
    std::array<int, 18> plotNumbers = {2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};

    // Random number generator
    std::random_device rd;
    std::mt19937 g(rd());

    // Shuffle resources and numbers
    std::shuffle(resourceTypes.begin(), resourceTypes.end(), g);
    std::shuffle(plotNumbers.begin(), plotNumbers.end(), g);

    // Create plots with shuffled resources and numbers
    int plotIndex = 0;
    int numberIndex = 0;
    for (const auto &resource : resourceTypes)
    {
        int number = (resource == "Desert") ? 7 : plotNumbers[numberIndex++];
        plots.emplace_back(resource, number, plotIndex++);
    }

    // Initialize vertices and edges (for simplicity, assume 54 vertices and 72 edges)
    vertices.reserve(54);
    for (std::size_t i = 0; i < 54; ++i)
    {
        vertices.emplace_back(i);
    }

    edges.reserve(72);
    for (std::size_t i = 0; i < 72; ++i)
    {
        edges.emplace_back(nullptr, nullptr, i); // Placeholder for actual vertex pointers
    }

    // Establish connections between plots, vertices, and edges
    for (std::size_t i = 0; i < plots.size(); ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            Vertex *v = &vertices[i * 6 + j];
            plots[i].setVertex(j, *v);
            v->addAdjacentPlot(&plots[i]); // Pass pointer to Plot

            if (j < 6)
            {
                // Adjust the constructor call to pass pointers to vertices
                Edge e(v, &vertices[i * 6 + (j + 1) % 6], edges.size());
                edges.push_back(e);
                plots[i].setEdge(j, e);
            }
        }
    }

    // Print message indicating game setup is complete and initial board configuration
    std::cout << "Game setup is complete. Initial board configuration:" << std::endl;
    printBoard();
}

const std::vector<Plot> &Board::getPlots() const
{
    return plots;
}

const std::vector<Vertex> &Board::getVertices() const
{
    return vertices;
}

const std::vector<Edge> &Board::getEdges() const
{
    return edges;
}

void Board::printBoard() const
{
    for (const Plot &plot : plots)
    {
        std::cout << "Plot " << plot.getIndex() << ": " << plot.getResource() << " (" << plot.getNumber() << ")\n";
    }
}

bool Board::canPlaceSettlement(int playerId, std::size_t vertexIndex) const
{
    // Check if vertexIndex is valid
    if (vertexIndex >= vertices.size() || vertexIndex < 0)
    {
        std::cerr << "Invalid vertex index." << std::endl;
        return false;
    }

    // Get the vertex at the specified index
    const Vertex &vertex = vertices[vertexIndex];

    // Check if the vertex is already occupied by a settlement or city
    if (vertex.getOwner() != -1)
    {
        std::cerr << "Vertex is already occupied." << std::endl;
        return false;
    }

    // Check adjacency of plots to the vertex for existing settlements or cities
    const std::vector<Plot> &adjacentPlots = vertex.getAdjacentPlots();
    for (const Plot &plot : adjacentPlots)
    {
        const std::vector<const Vertex *> plotVertices = plot.getVertices();
        for (const Vertex *adjacentVertex : plotVertices)
        { // Iterate over pointers
            if (adjacentVertex->getOwner() == playerId)
            { // Dereference pointer to access Vertex
                std::cerr << "Adjacent vertex already occupied by the same player." << std::endl;
                return false;
            }
        }
    }

    // If all conditions are met, settlement can be placed
    return true;
}

bool Board::canPlaceRoad(int playerId, std::size_t edgeIndex) const
{
    // Check if edgeIndex is valid
    if (edgeIndex >= edges.size() || edgeIndex < 0)
    {
        std::cerr << "Invalid edge index." << std::endl;
        return false;
    }

    // Get the edge at the specified index
    const Edge &edge = edges[edgeIndex];

    // Check if the edge is already occupied by a road
    if (edge.getOwner() != -1)
    {
        std::cerr << "Edge is already occupied." << std::endl;
        return false;
    }

    // Check if the edge is connected to a settlement or city owned by the player
    const Vertex &v1 = edge.getVertex1();
    const Vertex &v2 = edge.getVertex2();
    if (v1.getOwner() != playerId && v2.getOwner() != playerId)
    {
        std::cerr << "Edge is not connected to a settlement or city owned by the player." << std::endl;
        return false;
    }

    // If all conditions are met, road can be placed
    return true;
}
