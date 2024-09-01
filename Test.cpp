
//roei.biton33@gmail.com
//206400426

#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <iostream>



using namespace std;

TEST_CASE("Test isConnected")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}

TEST_CASE("Test shortestPath")
{
    ariel::Graph g;
    vector<vector<int>> graph3 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph4 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "No path from start to end vertex.");
}
TEST_CASE("Test isContainsCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph5 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->0");

    vector<vector<int>> graph6 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->0");
}
TEST_CASE("Test isBipartite")
{
    ariel::Graph g;
    vector<vector<int>> graph7 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph7);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={2, 0}, B={1} ");

    vector<vector<int>> graph8 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph8);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph9 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph9);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");
}
TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph10 = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph10));
}



TEST_CASE("Test invalid graph with edge from vertice to itself")
{
    ariel::Graph g;
    vector<vector<int>> graph11 = {
            {0, 1, 2, 0},
            {1, 2, 3, 0},
            {2, 3, 0, 4},
            {0, 0, 4, 0}};
    CHECK_THROWS(g.loadGraph(graph11));
}

TEST_CASE("Example of shortest path that going through negative edges")
{
    ariel::Graph g;
    vector<vector<int>> graph12 = {
            {0, 1, 0, 0,  9},
            {0, 0, 0, -2, 0},
            {0, 3, 0, 4,  0},
            {0, 0, 4, 0,  5},
            {0, 0, 0, 5,  0}};
    g.loadGraph(graph12);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "0->1->3->4");
}

TEST_CASE("Example of negative cycle")
{
    ariel::Graph g;
    vector<vector<int>> graph13 = {
            {0, 1, 0, 0,  9},
            {0, 0, 0, -2, 0},
            {0, 3, 0, 4,  0},
            {0, 1, 4, 0,  5},
            {0, 0, 0, 5,  0}};
    g.loadGraph(graph13); // Load the graph to the object.
    CHECK(ariel::Algorithms::negativeCycle(g) == true);
}

TEST_CASE("Test Graph Operators +")
{
    ariel::Graph g1, g2, expected_graph;

    vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
            {0, 2, 1},
            {2, 0, 2},
            {1, 2, 0}};
    g2.loadGraph(graph2);

// Test Addition (+)
    ariel::Graph g_sum = g1 + g2;
    vector<vector<int>> expected_sum = {
            {0, 3, 1},
            {3, 0, 3},
            {1, 3, 0}};
    expected_graph.loadGraph(expected_sum);
    CHECK(g_sum == expected_graph);
}
TEST_CASE("Test Graph Operators +=")
{
    ariel::Graph g1, g2, expected_graph;

    vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
            {0, 2, 1},
            {2, 0, 2},
            {1, 2, 0}};
    g2.loadGraph(graph2);
    vector<vector<int>> expected_sum = {
            {0, 3, 1},
            {3, 0, 3},
            {1, 3, 0}};
    expected_graph.loadGraph(expected_sum);
// Test Addition Assignment (+=)
    g1 += g2;
    CHECK(g1 == expected_graph);
}
TEST_CASE("Test Graph Operators unary +")
{
    ariel::Graph g1, g2, expected_graph;

    vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
            {0, 2, 1},
            {2, 0, 2},
            {1, 2, 0}};
    g2.loadGraph(graph2);

// Test Unary Plus (+)
    ariel::Graph g_unary_plus = +g1;
    CHECK(g_unary_plus == g1);
}
TEST_CASE("Test Graph Operators -")
{
    ariel::Graph g1, g2, expected_graph;

    vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
            {0, 2, 1},
            {2, 0, 2},
            {1, 2, 0}};
    g2.loadGraph(graph2);

// Test Subtraction (-)

    ariel::Graph g_diff = g1 - g2;
    vector<vector<int>> expected_diff = {
            {0,  -1, -1},
            {-1, 0,  -1},
            {-1, -1, 0}};
    expected_graph.loadGraph(expected_diff);
    CHECK(g_diff == expected_graph);
}

TEST_CASE("Test Graph Operators -=")
{
    ariel::Graph g1, g2, expected_graph;

    vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
            {0, 2, 1},
            {2, 0, 2},
            {1, 2, 0}};
    g2.loadGraph(graph2);
    vector<vector<int>> expected_diff = {
            {0,  -1, -1},
            {-1, 0,  -1},
            {-1, -1, 0}};
    expected_graph.loadGraph(expected_diff);
// Test Subtraction Assignment (-=)
    g1 -= g2;
    CHECK(g1 == expected_graph);
}

TEST_CASE("Test Graph Operators unary -")
{
    ariel::Graph g1, g2, expected_graph;

    vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
            {0, 2, 1},
            {2, 0, 2},
            {1, 2, 0}};
    g2.loadGraph(graph2);
// Test Unary Minus (-)

    ariel::Graph g_unary_minus = -g2;
    vector<vector<int>> expected_unary_minus = {
            {0,  -2, -1},
            {-2, 0,  -2},
            {-1, -2, 0}};
    expected_graph.loadGraph(expected_unary_minus);
    CHECK(g_unary_minus == expected_graph);
}
TEST_CASE("Test Graph Operators *")
{
    ariel::Graph g1, g2, expected_graph;

    vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
            {0, 2, 1},
            {2, 0, 2},
            {1, 2, 0}};
    g2.loadGraph(graph2);
// Test Multiplication with Graph (*)

    ariel::Graph g_mul = g1 * g2;
    vector<vector<int>> expected_mul = {
            {0, 0, 2},
            {1, 0, 1},
            {2, 0, 0}};
    expected_graph.loadGraph(expected_mul);
    CHECK(g_mul == expected_graph);
}

TEST_CASE("Test Graph Operators scalar *")
{
    ariel::Graph g1, g2, expected_graph;

    vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
            {0, 2, 1},
            {2, 0, 2},
            {1, 2, 0}};
    g2.loadGraph(graph2);
// Test Multiplication with Scalar (*)

    ariel::Graph g_scalar_mul = g2 * 2;
    vector<vector<int>> expected_scalar_mul = {
            {0, 4, 2},
            {4, 0, 4},
            {2, 4, 0}};
    expected_graph.loadGraph(expected_scalar_mul);
    CHECK(g_scalar_mul == expected_graph);
}

TEST_CASE("Test Graph Operators  *=")
{
    ariel::Graph g1, g2, expected_graph;

    vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
            {0, 2, 1},
            {2, 0, 2},
            {1, 2, 0}};
    g2.loadGraph(graph2);
// Test Multiplication Assignment with Graph (*=)

    vector<vector<int>> expected_mul2 = {
            {0, 2, 4},
            {2, 0, 2},
            {4, 2, 0}};
    expected_graph.loadGraph(expected_mul2);
    g1 = g2;
    g1 *= g2;
    CHECK(g1 == expected_graph);
}

TEST_CASE("Test Graph Operators scalar *=")
{
    ariel::Graph g1, g2, expected_graph;

    vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
            {0, 2, 1},
            {2, 0, 2},
            {1, 2, 0}};
    g2.loadGraph(graph2);
// Test Multiplication Assignment with Scalar (*=)

    vector<vector<int>> expected_mul_scalar2 = {
            {0, 2, 0},
            {2, 0, 2},
            {0, 2, 0}};
    expected_graph.loadGraph(expected_mul_scalar2);
    g1 *= 2;
    CHECK(g1 == expected_graph);
}

TEST_CASE("Test Graph Operators ==")
{
    ariel::Graph g1, g2, expected_graph;

    vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
            {0, 2, 1},
            {2, 0, 2},
            {1, 2, 0}};
    g2.loadGraph(graph2);
// Test Comparison Operators (==, !=, <, >, <=, >=)
    vector<vector<int>> expected_g1_copy = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    expected_graph.loadGraph(expected_g1_copy);
    CHECK(g1 == expected_graph);
}
TEST_CASE("Test Graph Operators !=")
{
    ariel::Graph g1, g2;

    vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
            {0, 2, 1},
            {2, 0, 2},
            {1, 2, 0}};
    g2.loadGraph(graph2);
    CHECK(g1 != g2);
}

TEST_CASE("Test Graph Operators <")
{
    ariel::Graph g1, g2;

    vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
            {0, 2, 1},
            {2, 0, 2},
            {1, 2, 0}};
    g2.loadGraph(graph2);
    CHECK(g1 < g2);
}

TEST_CASE("Test Graph Operators >")
{
    ariel::Graph g1, g2;

    vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
            {0, 2, 1},
            {2, 0, 2},
            {1, 2, 0}};
    g2.loadGraph(graph2);
    CHECK(g2 > g1);
}

TEST_CASE("Test Graph Operators <=")
{
    ariel::Graph g1, g2;

    vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
            {0, 2, 1},
            {2, 0, 2},
            {1, 2, 0}};
    g2.loadGraph(graph2);
    CHECK(g1 <= g2);
}

TEST_CASE("Test Graph Operators >=")
{
    ariel::Graph g1, g2;

    vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
            {0, 2, 1},
            {2, 0, 2},
            {1, 2, 0}};
    g2.loadGraph(graph2);
CHECK(g2 >= g1);

}


