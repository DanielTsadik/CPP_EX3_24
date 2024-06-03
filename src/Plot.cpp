#include "Plot.hpp"

Plot::Plot(const std::string& resource, int number, std::size_t index)
    : resource(resource), number(number), index(index), vertices{}, edges{} {}


void Plot::setVertex(int position, const Vertex& vertex) {
    if (position >= 0 && position < 6) {
        vertices[position] = &vertex;
    }
}

void Plot::setEdge(int position, const Edge& edge) {
    if (position >= 0 && position < 6) {
        edges[position] = edge; 
    }
}

std::string Plot::getResource() const {
    return resource;
}

int Plot::getNumber() const {
    return number;
}

std::size_t Plot::getIndex() const {
    return index;
}

const std::vector<const Vertex*>& Plot::getVertices() const {
    return vertices;
}

const std::array<Edge, 6>& Plot::getEdges() const {
    return edges;
}
