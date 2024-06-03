#pragma once
#include <vector>

class Plot;

class Vertex {
public:
    Vertex(std::size_t index);

    std::size_t getIndex() const;
    void setOwner(int playerId);
    int getOwner() const;

    void addAdjacentPlot(Plot* plot);
    const std::vector<Plot>& getAdjacentPlots() const;

private:
    std::size_t index;
    int owner;
    std::vector<Plot> adjacentPlots;
};
