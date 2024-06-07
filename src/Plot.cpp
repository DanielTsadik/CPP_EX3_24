#include "Plot.hpp"

Plot::Plot(const std::string& resource, int number, std::size_t index)
    : resource(resource), number(number), index(index), vertices{}, edges{} {}


void Plot:: setVertex(Vertex& vertex) {
    {
        vertices.push_back(&vertex);
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

 std::vector< Vertex*>& Plot::getVertices() {
    return vertices;
}

const std::vector<Edge>& Plot::getEdges() const {
    return edges;
}