// Daniel Tsadik
// Tsadik88@gmail.com   

#pragma once
#include "Vertex.hpp"

class Vertex; // Forward declaration
using namespace std;

class Edge
{
public:
    Edge(const Vertex *v1, const Vertex *v2, size_t index);
    Edge(size_t index);

    Edge(const Edge &other); // Copy constructor

    size_t getIndex() const;
    void setOwner(int playerId);
    int getOwner() const;
    const Vertex &getVertex1() const;
    const Vertex &getVertex2() const;
    Edge &operator=(const Edge &other);
    void setVertices(Vertex* vertex1, Vertex* vertex2);

private:
    const Vertex *v1;  // Pointer to the first vertex
    const Vertex *v2;  // Pointer to the second vertex
    size_t index; // Index of the edge
    int owner;         // Owner of the edge
};
