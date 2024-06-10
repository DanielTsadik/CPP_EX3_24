#include "Vertex.hpp"
#include "Plot.hpp"
#include "Edge.hpp"

// Constructor to initialize the vertex with an index
Vertex::Vertex(size_t index) : index(index), owner(-1), city(-1){}

// Get the index of the vertex
size_t Vertex::getIndex() const {
    return index;
}

// Set the owner of the vertex
void Vertex::setOwner(int playerId) {
    owner = playerId;
}

// Get the owner of the vertex
int Vertex::getOwner() const {
    return owner;
}

// Add an adjacent plot to the vertex
void Vertex::addAdjacentPlot(Plot* plot) {
    adjacentPlots.push_back(plot);
}

// Get the adjacent plots
const vector<Plot*>& Vertex::getAdjacentPlots() const {
    return adjacentPlots;
}

// Add an adjacent vertex to the vertex
void Vertex::addNeighbor(Vertex* vertex) {
    neighbors.push_back(vertex);
}

// Check if a vertex is a neighbor
bool Vertex::isNeighbor(const Vertex& vertex) const {
    for (const Vertex* neighbor : neighbors) {
        if (neighbor->getIndex() == vertex.getIndex()) {
            return true;
        }
    }
    return false;
}

// Get the adjacent vertices
const vector<Vertex*>& Vertex::getNeighbors() const {
    return neighbors;
}

// Add an adjacent edge to the vertex
void Vertex::addEdge(Edge* edge) {
    edges.push_back(edge);
}

// Get the adjacent edges
const vector<Edge*>& Vertex::getEdges() const {
    return edges;
}

// Set the city of the vertex
void Vertex::setCity(int cityId) {
    city = cityId;
}

// Get the city of the vertex
int Vertex::getCity() const {
    return city;
}
