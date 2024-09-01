
//roei.biton33@gmail.com
//206400426

#include "Graph.hpp"
#include <iostream>
#include <stdexcept>

namespace ariel {

Graph::Graph(): adjacencyMatrix() {}

    void Graph::loadGraph(const std::vector<std::vector<int>>& graph) {
        // Check if the graph is a square matrix
        if (graph.size() != graph[0].size()) {
            throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
        }

        // Check if diagonal elements are all zero
        for (size_t i = 0; i < graph.size(); ++i) {
            if (graph[i][i] != 0) {
                throw std::invalid_argument("Invalid graph: Diagonal elements must be zero.");
            }
        }

        // Load the graph from the provided matrix representation
        // and store it in the adjacencyMatrix member variable.
        adjacencyMatrix = graph;
    }



    void Graph::printGraphDetails() const {
        // Print the graph's adjacency matrix.
        std::cout << "Graph with " << adjacencyMatrix.size() << " vertices and ";
        int edgeCount = 0;
        for (const auto& row : adjacencyMatrix) {
            for (int value : row) {
                if (value != 0) {
                    edgeCount++;
                }
            }
        }
        std::cout << edgeCount << " edges." << std::endl;
    }

    void Graph::printVisualGraph() const{
        std::cout << "Graph with " << this << std::endl;
}

    size_t Graph::getNumOfVertices() const{
        return this->adjacencyMatrix.size();
    }
    bool Graph::isEmpty() const{
    return this->getNumOfVertices()<=0;
}

    bool Graph::isContained(Graph secGraph) const{
        if(secGraph.getNumOfVertices()>this->getNumOfVertices()){
            return false;
        }
        if(secGraph.isEmpty()){
            return true;
        }
        for(size_t i=0; i<secGraph.getNumOfVertices(); i++){
            for(size_t j=0; j<secGraph.getNumOfVertices(); j++) {
                if(secGraph.adjacencyMatrix[i][j] !=0 && this->adjacencyMatrix[i][j] ==0){
                    return false;
                }
            }
        }
        return true;
}
    size_t Graph::edgeCount() const{
    size_t counter=0;
    if(this->isEmpty()){
        return counter;
    }
    for(size_t i = 0; i<this->getNumOfVertices(); i++){
        for(size_t j = 0; j<this->getNumOfVertices(); j++){
            if(this->adjacencyMatrix[i][j]!=0){
                counter++;
            }
        }
    }
    return counter;
}

    Graph Graph::operator+(const Graph& secGraph) const{
        if (this->getNumOfVertices() != secGraph.getNumOfVertices()) {
            throw std::invalid_argument("The graphs have different sizes, operation cant be done !");
        }

        Graph sumResult;
        sumResult.adjacencyMatrix.resize(adjacencyMatrix.size(), std::vector<int>(adjacencyMatrix.size()));

        for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
            for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) {
                sumResult.adjacencyMatrix[i][j] = adjacencyMatrix[i][j] + secGraph.adjacencyMatrix[i][j];
            }
        }

        return sumResult;
    }

    Graph& Graph::operator+=(const Graph& secGraph) {
        if (adjacencyMatrix.size() != secGraph.adjacencyMatrix.size()) {
            throw std::invalid_argument("The graphs have different sizes, operation cant be done !");
        }

        for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
            for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) {
                adjacencyMatrix[i][j] += secGraph.adjacencyMatrix[i][j];
            }
        }

        return *this;
    }

    Graph Graph::operator+() const {
        return *this;
    }


    Graph Graph::operator-(const Graph& secGraph) const{
        if (this->adjacencyMatrix.size() != secGraph.adjacencyMatrix.size()) {
            throw std::invalid_argument("The graphs have different sizes, operation cant be done !");
        }

        Graph difResult;
        difResult.adjacencyMatrix.resize(adjacencyMatrix.size(), std::vector<int>(adjacencyMatrix.size()));

        for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
            for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) {
                difResult.adjacencyMatrix[i][j] = adjacencyMatrix[i][j] - secGraph.adjacencyMatrix[i][j];
            }
        }

        return difResult;
    }

    Graph& Graph::operator-=(const Graph& secGraph) {
        if (adjacencyMatrix.size() != secGraph.adjacencyMatrix.size()) {
            throw std::invalid_argument("The graphs have different sizes, operation cant be done !");
        }

        for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
            for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) {
                adjacencyMatrix[i][j] -= secGraph.adjacencyMatrix[i][j];
            }
        }

        return *this;
    }

    Graph Graph::operator-() const {
        Graph result;
        result.adjacencyMatrix.resize(adjacencyMatrix.size(), std::vector<int>(adjacencyMatrix.size()));

        for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
            for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) {
                result.adjacencyMatrix[i][j] = -adjacencyMatrix[i][j];
            }
        }
        return result;
    }

    Graph& Graph::operator++() {
        for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
            for (size_t j = 0; j < adjacencyMatrix.size(); ++j) {

                if (this->adjacencyMatrix[i][j] != 0) {
                    this->adjacencyMatrix[i][j]++;
                }
            }
        }
        return *this;
    }
    Graph& Graph::operator--() {
        for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
            for (size_t j = 0; j < adjacencyMatrix.size(); ++j) {

                if (this->adjacencyMatrix[i][j] != 0) {
                    this->adjacencyMatrix[i][j]--;
                }
            }
        }
        return *this;
    }

    bool Graph::operator==(Graph secGraph) const{
        if(this->getNumOfVertices()!=secGraph.getNumOfVertices()){
            return false;
        }
        for(size_t i=0; i<secGraph.getNumOfVertices(); i++){
            for(size_t j=0; j<secGraph.getNumOfVertices(); j++) {
                if(secGraph.adjacencyMatrix[i][j] != this->adjacencyMatrix[i][j]){
                    return false;
                }
            }
        }
        return true;
}
    bool Graph::operator!=(Graph secGraph) const{
        return !(*this==secGraph);
    }

    bool Graph::operator<(Graph secGraph) const {
        return secGraph>*this;
    }

    bool Graph::operator>(Graph secGraph) const{
        if(secGraph.isEmpty() || this->isContained(secGraph)){
            return true;
        }
        if(this->edgeCount()>secGraph.edgeCount()){
            return true;
        }
        else if(this->edgeCount()==secGraph.edgeCount()){
            if(this->getNumOfVertices()>secGraph.getNumOfVertices()){
                return true;
            }
        }
            return false;
    }

    bool Graph::operator<=(Graph secGraph) const{
        return *this==secGraph || *this<secGraph;
    }

    bool Graph::operator>=(Graph secGraph) const{
        return *this==secGraph || *this>secGraph;
    }



    Graph Graph::operator*(Graph secGraph) const{
        if (this->getNumOfVertices() != secGraph.getNumOfVertices()) {
            throw std::invalid_argument("The graphs have different sizes, multiplication cant be done !");
        }

        Graph mulResult;
        mulResult.adjacencyMatrix.resize(adjacencyMatrix.size(), std::vector<int>(adjacencyMatrix.size()));

        for (size_t i = 0; i < this->getNumOfVertices(); ++i) {
            for (size_t j = 0; j < this->getNumOfVertices(); ++j) {
                int sum = 0;
                for (size_t k = 0; k < this->getNumOfVertices(); ++k) {
                    sum += adjacencyMatrix[i][k] * secGraph.adjacencyMatrix[k][j];
                }
                mulResult.adjacencyMatrix[i][j] = sum;
            }
        }

        for (size_t i = 0; i < this->getNumOfVertices(); ++i) {
            mulResult.adjacencyMatrix[i][i]=0;
        }

        return mulResult;
    }

    Graph Graph::operator*(int scalar) const{
        Graph mulResult;
        mulResult.adjacencyMatrix.resize(adjacencyMatrix.size(), std::vector<int>(adjacencyMatrix.size()));

        for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
            for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) {
                mulResult.adjacencyMatrix[i][j] = adjacencyMatrix[i][j] * scalar;
            }
        }

        return mulResult;
    }

    Graph& Graph::operator*=(Graph secGraph){
        if (this->getNumOfVertices() != secGraph.getNumOfVertices()) {
            throw std::invalid_argument("The graphs have different sizes, multiplication cant be done !");
        }

        Graph mulResult;
        mulResult.adjacencyMatrix.resize(adjacencyMatrix.size(), std::vector<int>(adjacencyMatrix.size()));

        for (size_t i = 0; i < this->getNumOfVertices(); ++i) {
            for (size_t j = 0; j < this->getNumOfVertices(); ++j) {
                int sum = 0;
                for (size_t k = 0; k < this->getNumOfVertices(); ++k) {
                    sum += adjacencyMatrix[i][k] * secGraph.adjacencyMatrix[k][j];
                }
                mulResult.adjacencyMatrix[i][j] = sum;
            }
        }

        for (size_t i = 0; i < this->getNumOfVertices(); ++i) {
            mulResult.adjacencyMatrix[i][i]=0;
        }
        this->loadGraph(mulResult.adjacencyMatrix);
        return *this;

    }

    Graph& Graph::operator*=(int scalar){

        for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
            for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) {
                adjacencyMatrix[i][j] = adjacencyMatrix[i][j] * scalar;
            }
        }

        return *this;

    }

    std::ostream& operator<<(std::ostream& out, const Graph& g) {
        out<< "\n";
        for (size_t i = 0; i < g.getNumOfVertices(); ++i) {
            out << "[";
            for (size_t j = 0; j < g.adjacencyMatrix[i].size(); ++j) {
                out << g.adjacencyMatrix[i][j];
                if (j < g.adjacencyMatrix[i].size() - 1) {
                    out << ", ";
                }
            }
            out << "]";
            if (i < g.adjacencyMatrix.size() - 1) {
                out << std::endl;
            }
        }
        return out;
    }

} // namespace ariel

