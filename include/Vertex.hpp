// Daniel Tsadik
// Tsadik88@gmail.com   

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>
#include <cstddef>

class Plot; // Forward declaration of the Plot class
class Edge; // Forward declaration of the Edge class

using namespace std;

class Vertex {
public:
    // Constructor to initialize the vertex with an index
    Vertex(size_t index);

    // Getters and setters for index and owner
    size_t getIndex() const;
    void setOwner(int playerId);
    void setCity(int cityId);
    int getOwner() const;
    int getCity() const;

    // Add an adjacent plot to the vertex
    void addAdjacentPlot(Plot* plot);

    // Get the adjacent plots
    const vector<Plot*>& getAdjacentPlots() const;

    // Add an adjacent vertex to the vertex
    void addNeighbor(Vertex* vertex);

    // Check if a vertex is a neighbor
    bool isNeighbor(const Vertex& vertex) const;

    // Get the adjacent vertices
    const vector<Vertex*>& getNeighbors() const;

    // Add an adjacent edge to the vertex
    void addEdge(Edge* edge);

    // Get the adjacent edges
    const vector<Edge*>& getEdges() const;

private:
    size_t index; // Index of the vertex
    int owner; // ID of the player who owns the vertex, -1 if unowned
    int city; 
    vector<Plot*> adjacentPlots; // Adjacent plots
    vector<Vertex*> neighbors; // Adjacent vertices (neighbors)
    vector<Edge*> edges; // Adjacent edges 
};

#endif // VERTEX_HPP
