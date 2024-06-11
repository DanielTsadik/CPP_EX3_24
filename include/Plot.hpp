// Daniel Tsadik
// Tsadik88@gmail.com   

#pragma once
#include <string>
#include <array>
#include "Vertex.hpp"
#include "Edge.hpp"
using namespace std;

class Plot {
public:
    Plot(const string& resource, int number, size_t index);

    void setVertex(Vertex& vertex);
    void setEdge(int position, const Edge& edge);

    string getResource() const;
    int getNumber() const;
    size_t getIndex() const;

    vector<Vertex*>& getVertices();
    const vector<Edge>& getEdges() const;

private:
    string resource;
    int number;
    size_t index;
    // vector<Vertex> vertices;
    vector<Vertex*> vertices;
    vector<Edge> edges;
    
};
