#pragma once
#include <string>
#include <array>
#include "Vertex.hpp"
#include "Edge.hpp"

class Plot {
public:
    Plot(const std::string& resource, int number, std::size_t index);

    void setVertex(int position, const Vertex& vertex);
    void setEdge(int position, const Edge& edge);

    std::string getResource() const;
    int getNumber() const;
    std::size_t getIndex() const;

    const std::vector<const Vertex*>& getVertices() const;
    const std::array<Edge, 6>& getEdges() const;

private:
    std::string resource;
    int number;
    std::size_t index;
    std::vector<Vertex> vertices;
    std::array<Edge, 6> edges;
    std::vector<const Vertex*> vertices;
};
