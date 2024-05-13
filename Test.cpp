#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <sstream> // for ostringstream, to check << operator

/**
 * @brief Test cases for the Graph class and the Algorithms class
 */

using namespace std;

TEST_CASE("Test without loading")
{
    ariel ::Graph g;
    CHECK_THROWS(g.printGraph());
    CHECK_THROWS(g.isDirected());
    CHECK_THROWS(g.isNegative());
    CHECK_THROWS(g.isWeighted());
    CHECK_THROWS(g.isSameWeight());
    CHECK(g.isLoaded() == false);
    CHECK_THROWS(ariel::Algorithms::isConnected(g));
    CHECK_THROWS(ariel::Algorithms::isBipartite(g));
    CHECK_THROWS(ariel::Algorithms::isContainsCycle(g));
    CHECK_THROWS(ariel::Algorithms::negativeCycle(g));
    CHECK_THROWS(ariel::Algorithms::shortestPath(g, 0, 1));
}

TEST_CASE("Test isConnected")
{
    ariel::Graph g;

    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);

    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph1 = {
        {0, -1},
        {1, 0}};
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph4 = {
        {0, 1},
        {0, 0}}; // only connected. not strongly connected
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    vector<vector<int>> graph3 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}

TEST_CASE("Test shortestPath for BFS and BF")
{
    ariel::Graph g;
    vector<vector<int>> graph = {// BFS on undirected
                                 {0, 1, 0},
                                 {1, 0, 1},
                                 {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph6 = {// BFS on direced
                                  {0, 1, 0},
                                  {0, 0, 1},
                                  {0, 1, 0}};
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "There is no path between vertex 0 and vertex 4");
    CHECK(ariel::Algorithms::shortestPath(g, -1, 4) == "Start or End vertices are invalid!");
    CHECK(ariel::Algorithms::shortestPath(g, 0, 8) == "Start or End vertices are invalid!");
    CHECK(ariel::Algorithms::shortestPath(g, 8, 0) == "Start or End vertices are invalid!");
    CHECK(ariel::Algorithms::shortestPath(g, 0, 0) == "A path from a vertex to itself isn't defined!");

    vector<vector<int>> graph3 = {
        {0, 8, -1},
        {8, 0, -5},
        {-1, -5, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->2");
    CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "0->2->1");
    CHECK(ariel::Algorithms::shortestPath(g, 1, 2) == "1->2");
    CHECK(ariel::Algorithms::shortestPath(g, 1, 0) == "1->2->0");

    vector<vector<int>> graph4 = {
        {0, 3, -1},
        {3, 0, -5},
        {-1, -5, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "Negative cycle detected");

    vector<vector<int>> graph5 = {
        {0, 8, -2},
        {8, 0, -5},
        {-1, -5, 0}};
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "Negative cycle detected");

    vector<vector<int>> graph7 = {
        {0, 0, 0, 0},
        {4, 0, -6, 0},
        {0, 0, 0, 5},
        {0, -2, 0, 0}};
    g.loadGraph(graph7);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "There is no path between vertex 0 and vertex 3");

    vector<vector<int>> graph8 =
        {{0, 10, -1, 1, 0},
         {10, 0, 10, 0, 0},
         {-1, 10, 0, 0, 2},
         {1, 0, 0, 0, 0},
         {0, 0, 2, 0, 0}};
    g.loadGraph(graph8);
    CHECK(ariel::Algorithms::shortestPath(g, 1, 2) == "1->0->2");
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->2");
    CHECK(ariel::Algorithms::shortestPath(g, 1, 0) == "1->2->0");

    vector<vector<int>> graph9 = {{0, 4, 2, 0, 0, 0},
                                  {4, 0, -5, -5, 0, -7},
                                  {2, -5, 0, 0, -1, 0},
                                  {0, -5, 0, 0, 0, 0},
                                  {0, 0, -1, 0, 0, 0},
                                  {0, -7, 0, 0, 0, 0}};
    g.loadGraph(graph9);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 5) == "0->2->1->5");
}
TEST_CASE("Test shortest path Dijkstra")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 2, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph2 = {
        {0, 6, 10, 0, 0, 0, 0, 0, 0, 0},
        {6, 0, 12, 11, 14, 0, 0, 0, 0, 0},
        {10, 12, 0, 12, 0, 0, 8, 16, 0, 0},
        {0, 11, 12, 0, 0, 6, 3, 0, 0, 0},
        {0, 14, 0, 0, 0, 4, 0, 0, 6, 0},
        {0, 0, 0, 6, 4, 0, 0, 0, 12, 0},
        {0, 0, 8, 3, 0, 0, 0, 0, 16, 6},
        {0, 0, 16, 0, 0, 0, 0, 0, 0, 8},
        {0, 0, 0, 0, 6, 12, 16, 0, 0, 13},
        {0, 0, 0, 0, 0, 0, 6, 8, 13, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 9) == "0->2->6->9");
    CHECK(ariel::Algorithms::shortestPath(g, 0, 8) == "0->1->4->8");
    CHECK(ariel::Algorithms::shortestPath(g, 3, 7) == "3->6->9->7");
    CHECK(ariel::Algorithms::shortestPath(g, 7, 5) == "7->9->6->3->5");

    vector<vector<int>> graph3 = {
        {0, 7, 5, 0, 0, 0},
        {7, 0, 0, 11, 0, 0},
        {5, 0, 0, 0, 0, 0},
        {0, 11, 1, 0, 1, 0},
        {0, 0, 0, 1, 0, 1},
        {0, 0, 0, 5, 0, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 5) == "0->1->3->4->5");
    CHECK(ariel::Algorithms::shortestPath(g, 5, 0) == "5->3->2->0");
}

TEST_CASE("Test isContainsCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    vector<vector<int>> graph3 = {
        {0, 2, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0->1->0");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);

    CHECK(ariel::Algorithms::isContainsCycle(g) == "0->1->2->0");

    vector<vector<int>> graph4 = {
        {0, 8, -2},
        {8, 0, -5},
        {-1, -5, 0}};
    g.loadGraph(graph4);
    CHECK((ariel::Algorithms::isContainsCycle(g) == "0->2->0" || ariel::Algorithms::negativeCycle(g) == "2->0->2")); // there is more than 1 cycle

    vector<vector<int>> graph5 = {
        {0, 8, -1},
        {8, 0, -4},
        {-1, -5, 0}};
    g.loadGraph(graph5);
    CHECK((ariel::Algorithms::isContainsCycle(g) == "0->2->0" || ariel::Algorithms::negativeCycle(g) == "2->0->2")); // there is more than 1 cycle

    vector<vector<int>> graph6 = {
        {0, 3, 7},
        {0, 0, 0},
        {7, 1, 0}

    };
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0->2->0");
    graph6[1][2] = 6;
    g.loadGraph(graph6);
    CHECK((ariel::Algorithms::isContainsCycle(g) == "2->0->1" || ariel::Algorithms::isContainsCycle(g) == "0->1->2->0")); // directed is by graph, or by edge?

    vector<vector<int>> graph7 = {
        {0, 0, 0, 0},
        {4, 0, -6, 0},
        {0, 0, 0, 5},
        {0, -2, 0, 0}};
    g.loadGraph(graph7);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "1->2->3->1");
}
TEST_CASE("Test isBipartite")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == "There is no valid bipartite partition of the graph");

    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 0},
        {1, 0, 3, 0, 0},
        {0, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2, 4}, B={1, 3}");

    vector<vector<int>> graph4 = {
        {0, -1, 0, 0, 0},
        {1, 0, 2, 0, 0},
        {0, 3, 0, 4, 0},
        {0, 0, -9, 0, 7},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2, 4}, B={1, 3}");

    vector<vector<int>> graph5 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 1, 2}, B={}");

    vector<vector<int>> graph6 = {
        {0, 0},
        {1, 0}};
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0}, B={1}");

    vector<vector<int>> graph7 = {
        {0}};
    g.loadGraph(graph7);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0}, B={}");

    vector<vector<int>> graph8 = {
        {0, 0, 0, 0},
        {4, 0, -6, 0},
        {0, 0, 0, 5},
        {0, -2, 0, 0}};
    g.loadGraph(graph8);
    CHECK(ariel::Algorithms::isBipartite(g) == "There is no valid bipartite partition of the graph");

    vector<vector<int>> graph9 = {
        {0, 0, 0},
        {0, 0, 0},
        {1, 1, 0}};
    g.loadGraph(graph9);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 1}, B={2}");

    vector<vector<int>> graph10 = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 1, 0}};
    g.loadGraph(graph10);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1, 3}");

    vector<vector<int>> graph11 = {
        {0, 1, 0, 0},
        {0, 0, 0, 1},
        {1, 0, 0, 1},
        {0, 0, 0, 0}};
    g.loadGraph(graph11);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 3}, B={1, 2}");

    vector<vector<int>> graph12 = {
        {0, 3, 7},
        {0, 0, 0},
        {7, 1, 0}};
    g.loadGraph(graph12);
    CHECK(ariel::Algorithms::isBipartite(g) == "There is no valid bipartite partition of the graph");
}
TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));

    vector<vector<int>> graph1 = {
        {}};
    CHECK_THROWS(g.loadGraph(graph));

    vector<vector<int>> graph2 = {// empty graph, 1 vertex and 0 edges
                                  {0}};
    CHECK_NOTHROW(g.loadGraph(graph2));
    vector<vector<int>> graph3 = {
        {1}};
    CHECK_THROWS(g.loadGraph(graph3));

    vector<vector<int>> graph4 = {
        {1, 3, 4},
        {0, 0, 0},
        {0, 0, 0}};
    CHECK_THROWS(g.loadGraph(graph4));
}
TEST_CASE("Test negative cycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 0, 0, 0},
        {4, 0, -6, 0},
        {0, 0, 0, 5},
        {0, -2, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::negativeCycle(g) == "1->2->3->1");

    vector<vector<int>> graph3 = {
        {0, 8, -1},
        {8, 0, -5},
        {-1, -5, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::negativeCycle(g) == "There is no negative cycle in the graph");

    vector<vector<int>> graph4 = {
        {0, 8, -2},
        {8, 0, -5},
        {-1, -5, 0}};
    g.loadGraph(graph4);
    CHECK((ariel::Algorithms::negativeCycle(g) == "0->2->0" || ariel::Algorithms::negativeCycle(g) == "2->0->2"));

    vector<vector<int>> graph5 = {
        {0, 8, -1},
        {8, 0, -4},
        {-1, -5, 0}};
    g.loadGraph(graph5);
    CHECK((ariel::Algorithms::negativeCycle(g) == "0->2->0" || ariel::Algorithms::negativeCycle(g) == "2->0->2"));

    vector<vector<int>> graph8 = {
        {0, 0, 0, 0},
        {4, 0, -6, 0},
        {0, 0, 0, 5},
        {0, -2, 0, 0}};
    g.loadGraph(graph8);
    CHECK(ariel::Algorithms::negativeCycle(g) == "1->2->3->1");
}

TEST_CASE("Empty graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {};
    CHECK_THROWS(g.loadGraph(graph));

    vector<vector<int>> graph1 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::isConnected(g) == false);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "No cycle detected");
    CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "There is no path between vertex 0 and vertex 1");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 1, 2}, B={}");
    CHECK(ariel::Algorithms::negativeCycle(g) == "There is no negative cycle in the graph");
}

// Tests for EX2
TEST_CASE("Test graph addition")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    ostringstream oss;
    oss << g3;
    CHECK_EQ(oss.str(), "The matrix of the graph is:\n[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]\n");
    g2 += g1;
    CHECK((g2 == g3) == true);
    ariel::Graph g4;
    vector<vector<int>> graph2 = {
        {0, -2, 4},
        {2, 0, 1},
        {4, 1, 0}};
    g4.loadGraph(graph2);
    ariel::Graph g5 = g1 + g4;
    g4 += g1;
    oss.str("");
    oss << g5;
    CHECK_EQ(oss.str(), "The matrix of the graph is:\n[0, -1, 4]\n[3, 0, 2]\n[4, 2, 0]\n");
    CHECK((g4 == g5) == true);
}

TEST_CASE("Test graph subtraction")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g2 - g1;
    ostringstream oss;
    oss << g3;
    CHECK_EQ(oss.str(), "The matrix of the graph is:\n[0, 0, 1]\n[0, 0, 1]\n[1, 1, 0]\n");
    g2 -= g1;
    CHECK((g2 == g3) == true);
    ariel::Graph g4;
    vector<vector<int>> graph2 = {
        {0, -2, 4},
        {2, 0, 1},
        {4, 1, 0}};
    g4.loadGraph(graph2);
    ariel::Graph g5 = g4 - g1;
    g4 -= g1;
    oss.str("");
    oss << g5;
    CHECK_EQ(oss.str(), "The matrix of the graph is:\n[0, -3, 4]\n[1, 0, 0]\n[4, 0, 0]\n");
    CHECK((g4 == g5) == true);
}

TEST_CASE("Check Unarys")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 2, 0, -6},
        {1, 0, 1, 4},
        {2, 1, 0, -8},
        {0, 0, 0, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = -g1;
    ostringstream oss;
    oss << g2;
    CHECK_EQ(oss.str(), "The matrix of the graph is:\n[0, -2, 0, 6]\n[-1, 0, -1, -4]\n[-2, -1, 0, 8]\n[0, 0, 0, 0]\n");
    ariel::Graph g3 = +g1;
    CHECK((g3 == g1) == true);
}

TEST_CASE("Test graph multiplication by scalar")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 2, 0, -6},
        {1, 0, 1, 4},
        {2, 1, 0, -8},
        {0, 0, 0, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = g1 * -2;
    ostringstream oss;
    oss << g2;
    CHECK_EQ(oss.str(), "The matrix of the graph is:\n[0, -4, 0, 12]\n[-2, 0, -2, -8]\n[-4, -2, 0, 16]\n[0, 0, 0, 0]\n");
    g1 *= -2;
    CHECK((g1 == g2) == true);
    ariel::Graph g3 = g1 * 0;
    oss.str("");
    oss << g3;
    CHECK_EQ(oss.str(), "The matrix of the graph is:\n[0, 0, 0, 0]\n[0, 0, 0, 0]\n[0, 0, 0, 0]\n[0, 0, 0, 0]\n");
}

TEST_CASE("Test graph division by scalar")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 2, 0, -6},
        {1, 0, 1, 4},
        {2, 1, 0, -8},
        {0, 0, 0, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = g1 / 2;
    ostringstream oss;
    oss << g2;
    CHECK_EQ(oss.str(), "The matrix of the graph is:\n[0, 1, 0, -3]\n[0, 0, 0, 2]\n[1, 0, 0, -4]\n[0, 0, 0, 0]\n"); //rounding down
    g1 /= 2;
    CHECK((g1 == g2) == true);
    ariel::Graph g3 = g1 / 1;
    oss.str("");
    oss << g3;
    CHECK_EQ(oss.str(), "The matrix of the graph is:\n[0, 1, 0, -3]\n[0, 0, 0, 2]\n[1, 0, 0, -4]\n[0, 0, 0, 0]\n");
    CHECK((g1 == g3) == true);
    
}



TEST_CASE("Test graph multiplication")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {0, 0, 2},
        {1, 0, 1},
        {1, 0, 0}};
    ostringstream oss;
    oss << g4;
    CHECK_EQ(oss.str(), "The matrix of the graph is:\n[0, 0, 2]\n[1, 0, 1]\n[1, 0, 0]\n");
    g1 *= g2;
    CHECK((g1 == g4) == true);
}

TEST_CASE("Test plus postfix and prefix"){
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 2, 0, -6},
        {1, 0, 1, 4},
        {2, 1, 0, -8},
        {0, 0, 0, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = g1++;
    ostringstream oss;
    oss << g2;
    CHECK_EQ(oss.str(), "The matrix of the graph is:\n[0, 2, 0, -6]\n[1, 0, 1, 4]\n[2, 1, 0, -8]\n[0, 0, 0, 0]\n");
    oss.str("");
    oss << g1;
    CHECK_EQ(oss.str(), "The matrix of the graph is:\n[0, 4, 0, -12]\n[2, 0, 2, 8]\n[4, 2, 0, -16]\n[0, 0, 0, 0]\n");
    ariel::Graph g3 = ++g1;
    oss.str("");
    oss << g3;
    CHECK_EQ(oss.str(), "The matrix of the graph is:\n[0, 8, 0, -24]\n[4, 0, 4, 16]\n[8, 4, 0, -32]\n[0, 0, 0, 0]\n");
    
}



TEST_CASE("Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 2},
        {1, 2, 0, 3},
        {1, 2, 3, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g5 * g1);
    CHECK_THROWS(g1 * g2);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);
    CHECK_THROWS(g6 / 0);
    CHECK_THROWS(g6 /= 0);
    ariel::Graph g7;
    CHECK_THROWS((g7 + g6));
    CHECK_THROWS((g7 - g6));
    CHECK_THROWS((g7 * g6));
    CHECK_THROWS((g7--));
    CHECK_THROWS((g7++));
    CHECK_THROWS((++g7));
    CHECK_THROWS(-g7);
    CHECK_THROWS(+g7);
    CHECK_THROWS(--g7);
    CHECK_THROWS(g7 / 2);
    CHECK_THROWS(cout << g7);
    CHECK_THROWS(g7 *= g6);
    CHECK_THROWS(g7 /= 4);
    CHECK_THROWS(g7 *= 4);
    CHECK_THROWS(g7 * 4);
    CHECK_THROWS(g7 += g6);

    CHECK_THROWS(g7 *= -2);
    CHECK_THROWS(g7 -= g6);
    // CHECK((g7 == g6)); // there is a problem with doctest when trying to check throw on boolean expression, but it does throw
    // CHECK(g7 <= g6);
    // CHECK(g7 != g6);
    // CHECK(g7 < g6);
    // CHECK(g7 > g6);
    // CHECK(g7  >= g6);
}