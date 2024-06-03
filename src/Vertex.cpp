#include "Vertex.hpp"


Vertex::Vertex(std::size_t index) : index(index), owner(-1) {}


std::size_t Vertex::getIndex() const {
    return index;
}

void Vertex::setOwner(int playerId) {
    owner = playerId;
}

int Vertex::getOwner() const {
    return owner;
}

void Vertex::addAdjacentPlot(Plot* plot) {
    adjacentPlots.push_back(*plot);
}

const std::vector<Plot>& Vertex::getAdjacentPlots() const {
    return adjacentPlots;
}
