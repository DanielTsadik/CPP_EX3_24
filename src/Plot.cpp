#include "Plot.hpp"

Plot::Plot(const string& resource, int number, size_t index)
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

string Plot::getResource() const {
    return resource;
}

int Plot::getNumber() const {
    return number;
}

size_t Plot::getIndex() const {
    return index;
}

 vector< Vertex*>& Plot::getVertices() {
    return vertices;
}

const vector<Edge>& Plot::getEdges() const {
    return edges;
}