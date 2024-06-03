#pragma once
#include <vector>
#include <iostream>
#include "Plot.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"

class Board {
public:
    Board();

    const std::vector<Plot>& getPlots() const;
    const std::vector<Vertex>& getVertices() const;
    const std::vector<Edge>& getEdges() const;

    void printBoard() const;

    bool canPlaceSettlement(int playerId, std::size_t vertexIndex) const;
    bool canPlaceRoad(int playerId, std::size_t edgeIndex) const;

private:
    std::vector<Plot> plots;
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
};
