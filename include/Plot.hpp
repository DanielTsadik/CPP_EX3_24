#pragma once
#include <string>
#include <array>
#include "Vertex.hpp"
#include "Edge.hpp"

class Plot {
public:
    Plot(const std::string& resource, int number, std::size_t index);

    void setVertex(Vertex& vertex);
    void setEdge(int position, const Edge& edge);

    std::string getResource() const;
    int getNumber() const;
    std::size_t getIndex() const;

    std::vector<Vertex*>& getVertices();
    const std::vector<Edge>& getEdges() const;

private:
    std::string resource;
    int number;
    std::size_t index;
    // std::vector<Vertex> vertices;
    std::vector<Vertex*> vertices;
    std::vector<Edge> edges;
    
};
