#include "Edge.hpp"

Edge::Edge(const Vertex* v1, const Vertex* v2, std::size_t index)
    : v1(v1), v2(v2), index(index), owner(-1) {}

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


std::size_t Edge::getIndex() const {
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
