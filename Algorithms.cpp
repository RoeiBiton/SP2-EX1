//roei.biton33@gmail.com
//206400426
#include "Algorithms.hpp"
#include <queue>
#include <vector>
#include <iostream>
#include <sstream>
#include <unordered_set>


namespace ariel {

    /**
 * @brief Checks if the graph is connected.
 *
 * This function performs a BFS starting from vertex 0 and checks if all vertices are visited.
 *
 * @param graph The graph object containing the adjacency matrix.
 * @return True if the graph is connected; otherwise, false.
 */
    bool Algorithms::isConnected(const Graph& graph) {
        std::vector<bool> visited(graph.adjacencyMatrix.size(), false);
        std::queue<size_t> q;

        q.push(0);
        visited[0] = true;

        while (!q.empty()) {
            size_t currentVertex = q.front();
            q.pop();

            for (size_t i = 0; i < graph.adjacencyMatrix.size(); ++i) {
                if (graph.adjacencyMatrix[currentVertex][i] && !visited[i]) {
                    q.push(i);
                    visited[i] = true;
                }
            }
        }

        for (bool v : visited) {
            if (!v) {
                return false;
            }
        }

        return true;
    }


    /**
     * @brief Finds the shortest path between two vertices using the Bellman-Ford algorithm.
     *
     * This function computes the shortest path from the start vertex to the end vertex.
     * If a negative cycle is detected, it returns an error message.
     *
     * @param graph The graph object containing the adjacency matrix.
     * @param start The starting vertex.
     * @param end The destination vertex.
     * @return A string representing the shortest path or an error message.
     */
    std::string Algorithms::shortestPath(const Graph& graph, size_t start, size_t end) {
        size_t numVertices = graph.getNumOfVertices();
        size_t fakeVer = graph.getNumOfVertices()+2; // a flag of vertice that doesnt exist, like -1

        // Define distances to all vertices as max
        std::vector<int> distance(numVertices, INT_MAX);
        // Deifne parent array to keep track of the shortest path
        std::vector<size_t> parent(numVertices, fakeVer);

        // Distance to the start vertex is 0
        distance[start] = 0;

        // Bellman-Ford algorithm to find shortest paths
        for (size_t i = 0; i < numVertices - 1; ++i) {
            for (size_t u = 0; u < numVertices; ++u) {
                for (size_t v = 0; v < numVertices; ++v) {
                    if (graph.adjacencyMatrix[u][v] != 0 && distance[u] != INT_MAX && distance[u] + graph.adjacencyMatrix[u][v] < distance[v]) {
                        distance[v] = distance[u] + graph.adjacencyMatrix[u][v];
                        parent[v] = u;
                    }
                }
            }
        }

        // Check for negative cycles
        if (negativeCycle(graph)) {
            return "Negative cycle detected. Shortest paths not well-defined.";
        }

        // Construct the shortest path string
        if (distance[end] == INT_MAX) {
            return "No path from start to end vertex.";
        }

        std::stringstream ss;
        ss << end;
        for (size_t v = parent[end]; v != fakeVer; v = parent[v]) {
            ss << ">-" << v;
        }


        std::string shortestPath = ss.str();
        std::reverse(shortestPath.begin(), shortestPath.end()); // Reverse the string
        return shortestPath;
    }

    /**
 * @brief Checks if the graph contains a cycle.
 *
 * This function uses DFS to detect cycles in the graph. If a cycle is found,
 * it returns the cycle as a string. If no cycle is found, it returns "0".
 *
 * @param graph The graph object containing the adjacency matrix.
 * @return A string representing the cycle or "0" if no cycle is found.
 */
    std::string Algorithms::isContainsCycle(const Graph& graph) {
        std::vector<int> color(graph.adjacencyMatrix.size(), 0);
        std::vector<size_t> parent(graph.adjacencyMatrix.size(), static_cast<size_t>(-1)); // Change to size_t
        size_t cycleStart = static_cast<size_t>(-1);

        for (size_t i = 0; i < graph.adjacencyMatrix.size(); ++i) {
            if (color[i] == 0 && hasCycleDFS(graph, i, color, parent, cycleStart)) {
                std::stringstream ss;
                ss << "The cycle is: " << cycleStart;
                for (size_t v = parent[cycleStart]; v != cycleStart; v = parent[v]) {
                    ss << "->" << v;
                }
                ss << "->" << cycleStart;
                return ss.str();
            }
        }
        return "0"; // No cycle found
    }

    /**
 * @brief Helper function for cycle detection using DFS.
 *
 * This function is used internally by `isContainsCycle` to perform the DFS traversal
 * and detect cycles.
 *
 * @param graph The graph object containing the adjacency matrix.
 * @param vertex The current vertex being visited.
 * @param color A vector tracking the visitation state of each vertex.
 * @param parent A vector tracking the parent of each vertex in the DFS tree.
 * @param cycleStart The start vertex of a detected cycle.
 * @return True if a cycle is detected; otherwise, false.
 */
    bool Algorithms::hasCycleDFS(const Graph& graph, size_t vertex, std::vector<int>& color, std::vector<size_t>& parent, size_t& cycleStart) {
        color[vertex] = 1; // Mark as visiting
        for (size_t i = 0; i < graph.adjacencyMatrix.size(); ++i) {
            if (graph.adjacencyMatrix[vertex][i]) {
                if (color[i] == 1) {
                    cycleStart = i; // Found a back edge, cycle detected
                    parent[cycleStart] = vertex;
                    return true;
                } else if (color[i] == 0) {
                    parent[i] = vertex;
                    if (hasCycleDFS(graph, i, color, parent, cycleStart)) {
                        return true;
                    }
                }
            }
        }
        color[vertex] = 2; // Mark as visited
        return false;
    }

    /**
     * @brief Checks if the graph is bipartite.
     *
     * This function uses BFS to check if the graph can be colored using two colors,
     * ensuring that no two adjacent vertices share the same color. If it is bipartite,
     * the function returns the partitions. Otherwise, it returns "0".
     *
     * @param graph The graph object containing the adjacency matrix.
     * @return A string describing the partitions or "0" if the graph is not bipartite.
     */
    std::string Algorithms::isBipartite(const Graph& graph) {

            std::vector<int> color(graph.adjacencyMatrix.size(), -1);
            std::queue<size_t> q;
            std::vector<std::unordered_set<size_t>> partitions(2);

            for (size_t startVertex = 0; startVertex < graph.adjacencyMatrix.size(); ++startVertex) {
                // If the vertex is not colored, it means we are in a new component
                if (color[startVertex] == -1) {
                    // Start BFS from this vertex
                    q.push(startVertex);
                    color[startVertex] = 0; // Start coloring with 0
                    partitions[0].insert(startVertex);

                    while (!q.empty()) {
                        size_t currentVertex = q.front();
                        q.pop();

                        int currentColor = color[currentVertex];
                        size_t nextColor = 0;
                        if(currentColor==0){
                            nextColor=1;
                        }
                        if(currentColor==1){
                            nextColor=0;
                        }

                        for (size_t i = 0; i < graph.adjacencyMatrix.size(); ++i) {
                            if (graph.adjacencyMatrix[currentVertex][i]) {
                                if (color[i] == -1) {
                                    // Color the uncolored vertex
                                    color[i] = nextColor;
                                    q.push(i);
                                    partitions[nextColor].insert(i);
                                } else if (color[i] == currentColor) {
                                    // If the adjacent vertex has the same color, it's not bipartite
                                    return "0";
                                }
                            }
                        }
                    }
                }
            }

            // Construct the output for partitions
            std::stringstream ss;
            ss << "The graph is bipartite: A={";
            if (!partitions[0].empty()) {
                for (size_t v : partitions[0]) {
                    ss << v << ", ";
                }
                ss.seekp(-2, std::ios_base::end); // Remove last comma
            }
            ss << "}, B={";
            if (!partitions[1].empty()) {
                for (size_t v : partitions[1]) {
                    ss << v << ", ";
                }
                ss.seekp(-2, std::ios_base::end); // Remove last comma
            }
            ss << "}";

            return ss.str();
        }


    /**
     * @brief Detects if there is a negative cycle in the graph.
     *
     * This function uses the Bellman-Ford algorithm to detect negative cycles in the graph.
     *
     * @param graph The graph object containing the adjacency matrix.
     * @return True if a negative cycle is detected; otherwise, false.
     */
    bool Algorithms::negativeCycle(const Graph& graph) {
        std::vector<int> distance(graph.adjacencyMatrix.size(), INT_MAX);
        distance[0] = 0;

        for (size_t i = 0; i < graph.adjacencyMatrix.size() - 1; ++i) {
            for (size_t u = 0; u < graph.adjacencyMatrix.size(); ++u) {
                for (size_t v = 0; v < graph.adjacencyMatrix.size(); ++v) {
                    if (graph.adjacencyMatrix[u][v] && distance[u] != INT_MAX && distance[u] + graph.adjacencyMatrix[u][v] < distance[v]) {
                        distance[v] = distance[u] + graph.adjacencyMatrix[u][v];
                    }
                }
            }
        }

        for (size_t u = 0; u < graph.adjacencyMatrix.size(); ++u) {
            for (size_t v = 0; v < graph.adjacencyMatrix.size(); ++v) {
                if (graph.adjacencyMatrix[u][v] && distance[u] != INT_MAX && distance[u] + graph.adjacencyMatrix[u][v] < distance[v]) {
                    return true;
                }
            }
        }

        return false;
    }

} // namespace ariel
