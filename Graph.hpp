#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

namespace ariel {

class Graph {

public:
    Graph();

    void loadGraph(const std::vector<std::vector<int>>& graph);

    void printGraphDetails() const;
    void printVisualGraph() const;

    std::vector<std::vector<int>> adjacencyMatrix;

    size_t getNumOfVertices() const;
    bool isEmpty() const;
    bool isContained(Graph secGraph) const;
    size_t edgeCount() const;

    Graph operator+(const Graph& secGraph) const;
    Graph& operator+=(const Graph& secGraph);
    Graph operator+() const;
    Graph operator-(const Graph& secGraph) const;
    Graph& operator-=(const Graph& secGraph);
    Graph operator-() const;

    bool operator==(Graph secGraph) const;
    bool operator!=(Graph secGraph) const;
    bool operator>=(Graph secGraph) const;
    bool operator<=(Graph secGraph) const;
    bool operator<(Graph secGraph) const;
    bool operator>(Graph secGraph) const;

    Graph& operator++();
    Graph& operator--();

    Graph operator*(Graph secGraph) const;
    Graph operator*(int scalar) const;
    Graph& operator*=(Graph secGraph);
    Graph& operator*=(int scalar);

    friend std::ostream& operator<<(std::ostream& out, const Graph& g);


};

} // namespace ariel

#endif // GRAPH_HPP
