#pragma once
#include "Vertex.hpp"

class Edge
{
public:
    Edge(const Vertex *v1, const Vertex *v2, std::size_t index);
    Edge();

    std::size_t getIndex() const;
    void setOwner(int playerId);
    int getOwner() const;
    const Vertex &getVertex1() const;
    const Vertex &getVertex2() const;
    Edge &operator=(const Edge &other);

private:
    const Vertex *v1;  // Pointer to the first vertex
    const Vertex *v2;  // Pointer to the second vertex
    std::size_t index; // Index of the edge
    int owner;         // Owner of the edge
};
