// Daniel Tsadik
// Tsadik88@gmail.com   

#include "Edge.hpp"
#include "Vertex.hpp"

Edge::Edge(const Vertex* v1, const Vertex* v2, size_t index)
    : v1(v1), v2(v2), index(index), owner(-1) {}

Edge::Edge(size_t index) : index(index), owner(-1) {}

Edge::Edge(const Edge& other) {
    this->v1 = other.v1;
    this->v2 = other.v2;
    this->index = other.index;
    this->owner = other.owner;
}


Edge& Edge::operator=(const Edge& other) {
    if (this != &other) {  // Self-assignment check
        // Copy member variables from 'other' to 'this'
        this->v1 = other.v1;
        this->v2 = other.v2;
        this->index = other.index;
        this->owner = other.owner;
    }
    return *this;  // Return a reference to the modified object
}


size_t Edge::getIndex() const {
    return index;
}

void Edge::setOwner(int playerId) {
    owner = playerId;
}

int Edge::getOwner() const {
    return owner;
}

const Vertex& Edge::getVertex1() const {
    return *v1;
}

const Vertex& Edge::getVertex2() const {
    return *v2;
}

void Edge::setVertices(Vertex* vertex1, Vertex* vertex2) {
    this->v1 = vertex1;
    this->v2 = vertex2;
}
