
//roei.biton33@gmail.com
//206400426

#include "Graph.hpp"
#include "Algorithms.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

using ariel::Algorithms;
using namespace std;

int main()
{
    ariel::Graph g;
    ariel::Graph g2;
    // 3x3 matrix that represents a connected graph.
    vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g.loadGraph(graph); // Load the graph to the object.

    g.printGraphDetails();                                    // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::isConnected(g) << endl;        // Should print: "1" (true).
    cout << Algorithms::shortestPath(g, 0, 2) << endl; // Should print: 0->1->2.
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "The cycle is: 0->1->0".
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "The graph is bipartite: A={2, 0}, B={1}."
    cout << endl;

    // 5x5 matrix that represents a non-connected graph with a cycle.
    vector<vector<int>> graph2 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};

    g.loadGraph(graph2); // Load the graph to the object.

    g.printGraphDetails();                                    // Should print: "Graph with 5 vertices and 8 edges."
    cout << Algorithms::isConnected(g) << endl;        // Should print: "0" (false).
    cout << Algorithms::shortestPath(g, 0, 4) << endl; // Should print: "No path from start to end vertex.".
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "The cycle is: 0->1->0".
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "0" (false).
    cout << endl;

    // 5x5 matrix that reprsents a connected weighted graph.
    vector<vector<int>> graph3 = {
            {0, 1, 0, 0, 0},
            {1, 0, 3, 0, 0},
            {0, 3, 0, 4, 0},
            {0, 0, 4, 0, 5},
            {0, 0, 0, 5, 0}};
    g.loadGraph(graph3); // Load the graph to the object.

    g.printGraphDetails();                                    // Should print: "Graph with 5 vertices and 8 edges."
    cout << Algorithms::isConnected(g) << endl;        // Should print: "1" (true).
    cout << Algorithms::shortestPath(g, 0, 4) << endl; // Should print: "0->1->2->3->4".
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "The cycle is: 0->1->0".
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "The graph is bipartite: A={4, 2, 0}, B={3, 1}"
    cout << endl;

    // 5x4 matrix that reprsents invalid graph.
    vector<vector<int>> graph4 = {
            {0, 1, 2, 0},
            {1, 0, 3, 0},
            {2, 3, 0, 4},
            {0, 0, 4, 0},
            {0, 0, 0, 5}};
    try
    {
        g.loadGraph(graph4); // Load the graph to the object.
    }
    catch (const std::invalid_argument &e)
    {
        cout << e.what() << endl; // Should print: "Invalid graph: The graph is not a square matrix."
        cout << endl;
    }

    // 4x4 matrix that reprsents invalid graph (Example of edge from vertice to itself, the diagonal line is not 0).
    cout << "Example of edge from vertice to itself, the diagonal line is not 0" <<endl;
    vector<vector<int>> graph5 = {
            {0, 1, 2, 0},
            {1, 2, 3, 0},
            {2, 3, 0, 4},
            {0, 0, 4, 0}};
    try
    {
        g.loadGraph(graph5); // Load the graph to the object.
    }
    catch (const std::invalid_argument &e)
    {
        cout << e.what() << endl; // Should print: "Invalid graph: Diagonal elements must be zero."
        cout << endl;
    }

    // 5x5 matrix that reprsents a connected weighted graph.
    cout << "Example of shortest path that going through negative edges" <<endl;

    vector<vector<int>> graph6 = {
            {0, 1, 0, 0, 9},
            {0, 0, 0, -2, 0},
            {0, 3, 0, 4, 0},
            {0, 0, 4, 0, 5},
            {0, 0, 0, 5, 0}};
    g.loadGraph(graph6); // Load the graph to the object.

    g.printGraphDetails();                                    // Should print: "Graph with 5 vertices and 8 edges."
    cout << Algorithms::shortestPath(g, 0, 4) << endl; // Should print: "0->1->3->4".
    cout << endl;

    // 5x5 matrix that reprsents a connected weighted graph.
    cout << "Example of negative cycle check and shortest path fail because of negative cycle" <<endl;

    vector<vector<int>> graph7 = {
            {0, 1, 0, 0, 9},
            {0, 0, 0, -2, 0},
            {0, 3, 0, 4, 0},
            {0, 1, 4, 0, 5},
            {0, 0, 0, 5, 0}};
    g.loadGraph(graph7); // Load the graph to the object.

    g.printGraphDetails();                                    // Should print: "Graph with 5 vertices and 9 edges."
    cout << Algorithms::negativeCycle(g) << endl;      // Should print: "1"
    cout << Algorithms::shortestPath(g, 0, 4) << endl; // Should print: "Negative cycle detected. Shortest paths not well-defined.".
    cout << endl;

    // 5x5 matrix that reprsents a connected weighted graph.
    cout << "Example of negative cycle check and printing the cycle" <<endl;

    vector<vector<int>> graph8 = {
            {0, 1, 0, 0, 9},
            {0, 0, 0, -2, 0},
            {0, 3, 0, 4, 0},
            {0, 1, 4, 0, 5},
            {0, 0, 0, 5, 0}};
    g.loadGraph(graph8); // Load the graph to the object.

    g.printGraphDetails();                                     // Should print: "Graph with 5 vertices and 9 edges."
    cout << Algorithms::negativeCycle(g) << endl;       // Should print: "1"
    cout << Algorithms::isContainsCycle(g) << endl;     // Should print: "The cycle is: 1->3->1".
    cout << endl;


    // 4x4 matrix that reprsents a connected weighted graph.
    cout << "Example of graph that is non connected" <<endl;

    vector<vector<int>> graph9 = {
            {0, 1, 0, 0},
            {1, 0, 2, 0},
            {0, 3, 0, 0},
            {0, 0, 0, 0}};
    g.loadGraph(graph9); // Load the graph to the object.

    g.printGraphDetails();                                     // Should print: "Graph with 4 vertices and 4 edges."
    cout << Algorithms::isConnected(g) << endl;       // Should print: "0"
    cout << endl;

    cout << "Example of unary + operator" <<endl;
    vector<vector<int>> graph10 = {
            {0, 1, 0, 0},
            {1, 0, 2, 0},
            {0, 3, 0, 0},
            {0, 0, 0, 0}};
    g.loadGraph(graph10); // Load the graph to the object
    cout << "Original Graph" << g << endl ;
    g= +g;
    cout << "Result of +g" << g << endl;
    cout << "The Graph needs to stay the same\n" << endl;


    cout << "Example of unary - operator" <<endl;
    vector<vector<int>> graph11 = {
            {0, 1, 0, 0},
            {1, 0, 1, 0},
            {0, 1, 0, -1},
            {0, 0, -1, 0}};
    g.loadGraph(graph11); // Load the graph to the object
    cout << "Original Graph" << g << endl ;
    g= -g;
    cout << "Result of -g" << g << endl;
    cout << "The Graph sign needs to be the opposite\n" << endl;


    cout << "Example of + operator" <<endl;
    vector<vector<int>> graph12 = {
            {0, 1, 2},
            {1, 0, 1},
            {2, 1, 0}};
    g.loadGraph(graph12); // Load the graph to the object
    cout << "Original Graph" << g << endl ;
    g= g+g;
    cout << "Result of g = g+g " << g << endl;
    cout << "The Graph edges value should be doubled (because of g+g)\n" << endl;


    cout << "Example of += operator" <<endl;
    cout << "Original Graph" << g << endl ;
    g += g;
    cout << "Result of g += g " << g << endl;
    cout << "The Graph edges value should be doubled (because of g+g)\n" << endl;


    cout << "Example of - operator" <<endl;
    vector<vector<int>> graph13 = {
            {0, 10, 0},
            {5, 0, 5},
            {0, 10, 0}};
    g.loadGraph(graph13); // Load the graph to the object
    vector<vector<int>> graph14 = {
            {0, 3, 0},
            {-2, 0, -5},
            {0, 4, 0}};
    g2.loadGraph(graph14); // Load the graph to the object
    cout << "Original Graph g" << g << endl ;
    cout << "Original Graph g2" << g2 << endl ;
    cout << "Result of g = g-g2 " << g-g2 << endl;
    cout << "The Graph edges value should be g-g2 for each egde\n" << endl;


    cout << "Example of -= operator" <<endl;
    cout << "Original Graph g" << g << endl ;
    cout << "Original Graph g2" << g2 << endl ;
    g-=g2;
    cout << "Result of g-=g2 " << g << endl;
    cout << "The Graph edges value should be g-g2 for each egde\n" << endl;

    cout << "End of + - += -= and unary + and unary - Operators\n" <<endl;



    cout << "Example of == operator" <<endl;
    vector<vector<int>> graph15 = {
            {0, 10, 0},
            {5, 0, 5},
            {0, 10, 0}};
    g.loadGraph(graph15); // Load the graph to the object
    vector<vector<int>> graph16 = {
            {0, 10, 0},
            {5, 0, 5},
            {0, 10, 0}};
    g2.loadGraph(graph16); // Load the graph to the object
    cout << "Original Graph g" << g << endl ;
    cout << "Original Graph g2" << g2 << endl ;
    bool ans = g==g2;
    cout << "Result of g == g2  is " << ans << endl;
    cout << "The graphs should be even, (1)\n" << endl;

    cout << "Example of != operator" <<endl;
    vector<vector<int>> graph17 = {
            {0, 10, 0},
            {5, 0, 0},
            {0, 10, 0}};
    g.loadGraph(graph17); // Load the graph to the object
    vector<vector<int>> graph18 = {
            {0, 10, 0},
            {5, 0, 5},
            {0, 10, 0}};
    g2.loadGraph(graph18); // Load the graph to the object
    cout << "Original Graph g" << g << endl ;
    cout << "Original Graph g2" << g2 << endl ;
    ans = g!=g2;
    cout << "Result of g != g2 is " << ans << endl;
    cout << "The Graphs are not equal (0)\n" << endl;


    cout << "Example of < operator" <<endl;
    vector<vector<int>> graph19 = {
            {0, 10, 0},
            {5, 0, 5},
            {0, 10, 0}};
    g.loadGraph(graph19); // Load the graph to the object
    vector<vector<int>> graph20 = {
            {0, 10, 0},
            {5, 0, 5},
            {5, 10, 0}};
    g2.loadGraph(graph20); // Load the graph to the object
    cout << "Original Graph g" << g << endl ;
    cout << "Original Graph g2" << g2 << endl ;
    ans = g<g2;
    cout << "Result of g < g2 is " << ans << endl;
    cout << "The Graph g is smaller than g2 (1) \n" << endl;

    cout << "Example of > operator" <<endl;
    cout << "Original Graph g" << g << endl ;
    cout << "Original Graph g2" << g2 << endl ;
    ans = g>g2;
    cout << "Result of g > g2 is " << ans << endl;
    cout << "The Graph g is not greater than g2 (0) \n" << endl;

    cout << "Example of <= operator" <<endl;
    cout << "Original Graph g" << g << endl ;
    cout << "Original Graph g2" << g2 << endl ;
    ans = g<=g2;
    cout << "Result of g <= g2 is " << ans << endl;
    cout << "The Graph g is smaller/equal than g2 (1) \n" << endl;

    cout << "Example of >= operator" <<endl;
    vector<vector<int>> graph21 = {
            {0, 10, 0},
            {5, 0, 5},
            {5, 10, 0}};
    g.loadGraph(graph21); // Load the graph to the object
    cout << "Original Graph g" << g << endl ;
    cout << "Original Graph g2" << g2 << endl ;
    ans = g>=g2;
    cout << "Result of g >= g2 is " << ans << endl;
    cout << "The Graph g is greater/equal than g2 (1) \n" << endl;

    cout << "End of == != <= >= < > Operators\n" <<endl;


    cout << "Example of ++ operator" <<endl;
    cout << "Original Graph g" << g << endl ;
    ++g;
    cout << "Result of ++g " << g << endl;
    cout << "The Graph edges should be increament by 1\n" << endl;


    cout << "Example of -- operator" <<endl;
    cout << "Original Graph g" << g << endl ;
    --g;
    cout << "Result of --g " << g << endl;
    cout << "The Graph edges shuold be decreased by 1 \n" << endl;

    cout << "Example of * with scalar operator" <<endl;
    cout << "Original Graph g" << g << endl ;
    g= g*3;
    cout << "Result of g= g*3 " << g << endl;
    cout << "The Graph edges shuold be multiply by 3 \n" << endl;

    cout << "Example of * between graohs operator" <<endl;
    vector<vector<int>> graph22 = {
            {0, 2, 2},
            {2, 0, 2},
            {2, 2, 0}};
    g2.loadGraph(graph22); // Load the graph to the object
    cout << "Original Graph g" << g << endl ;
    cout << "Original Graph g2" << g2 << endl ;
    g= g*g2;
    cout << "Result of g= g*g2 " << g << endl;
    cout << "The Graph edges should be a result of matrix multiply of g and g2  \n" << endl;

    cout << "Example of *= with scalar operator" <<endl;
    cout << "Original Graph g" << g << endl ;
    g*=2;
    cout << "Result of g*=2 " << g << endl;
    cout << "The Graph edges should be multiply by 2 \n" << endl;


    cout << "Example of *= with graph operator" <<endl;
    vector<vector<int>> graph23 = {
            {0, 2, 2},
            {2, 0, 2},
            {2, 2, 0}};
    g.loadGraph(graph23); // Load the graph to the object
    cout << "Original Graph g" << g << endl ;
    cout << "Original Graph g2" << g << endl ;
    g*=g2;
    cout << "Result of g*=g2 " << g << endl;
    cout << "The Graph edges should be a result of matrix multiply of g and g2  \n" << endl;

    cout << "Example of << output operator" <<endl;
    cout <<  g << endl ;
    cout << "Result of << g" << endl;


return 0;


}