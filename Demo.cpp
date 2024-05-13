/*
 * Demo program for Exercise 2.
 * Author: Benjamin Saldman.
 */
#include "Graph.hpp"
#include "Algorithms.hpp"

using ariel::Algorithms;

#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

int main()
{

ariel::Graph g;
    // 3x3 matrix that represents a connected graph.
    vector<vector<int>> graph =
        {{0, 1, 0},
         {1, 0, 1},
         {0, 1, 0}};
    g.loadGraph(graph); // Load the graph to the object.
    g++;
    cout<<g;

    g.printGraph();                                    // Should print: "This is a undirected and unweighted graph with 3 vertices and 2 edges"
    cout << Algorithms::isConnected(g) << endl;        // Should print: "1" (true).
    cout << Algorithms::shortestPath(g, 0, 1) << endl; // Should print: 0->1.
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "No cycle detected" (false)
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "The graph is bipartite: A={0, 2}, B={1}."
    cout << ariel::Algorithms::negativeCycle(g) << endl; //Should print: "There is no negative cycle in the graph" (false).

    // 5x5 matrix that represents a non-connected graph with a cycle.
    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};

    g.loadGraph(graph2); // Load the graph to the object.

    g.printGraph();                                    // Should print: "This is a undirected and unweighted graph with 5 vertices and 4 edges"
    cout << Algorithms::isConnected(g) << endl;        // Should print: "0" (false).
    cout << Algorithms::shortestPath(g, 0, 4) << endl; // Should print: "There is no path between vertex 0 and vertex 4" (false).
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "0->1->2->0" (The actual cycle)
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "There is no valid bipartite partition of the graph" (false).
    cout << ariel::Algorithms::negativeCycle(g) << endl; //Should print: "Should print: "There is no negative cycle in the graph" (false).

    // 5x5 matrix that reprsents a connected weighted graph.
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 0},
        {1, 0, 3, 0, 0},
        {0, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3); // Load the graph to the object.

    g.printGraph();                                    // Should print: "This is a undirected weighted graph with non-negative weights, 5 vertices and 4 edges"
    cout << Algorithms::isConnected(g) << endl;        // Should print: "1" (true).
    cout << Algorithms::shortestPath(g, 0, 4) << endl; // Should print: 0->1->2->3->4.
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "No cycle detected" (false).
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "The graph is bipartite: A={0, 2, 4}, B={1, 3}."
    cout << ariel::Algorithms::negativeCycle(g) << endl; //Should print: "Should print: "There is no negative cycle in the graph" (false).

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
        cout << e.what() << endl; // Should print: "Not a valid graph!"
    }

    vector<vector<int>> graph5 = {
            {0, 0, 0, 0},
            {4, 0, -6, 0},
            {0, 0, 0, 5},
            {0, -2, 0, 0}};
    g.loadGraph(graph5);
    g.printGraph();                                    // Should print: "This is a directed weighted graph with negative weights, 4 vertices and 4 edges"
    cout << Algorithms::isConnected(g) << endl;        // Should print: "0" (false).
    cout << Algorithms::shortestPath(g, 0, 3) << endl; // Should print: "There is no path between vertex 0 and vertex 3" (false). Notice that because there is no edge from vertex 0 to any other vertex, the negative cycle wasn't encountered, so it returns no path
    cout << Algorithms::shortestPath(g, 3, 0) << endl; // Should print: "Negative cycle detected" (So no shoretest path is possible)
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "There is no valid bipartite partition of the graph"
    cout << ariel::Algorithms::negativeCycle(g) << endl; //Should print: "1->2->3->1" (The negative cycle);

     vector<vector<int>> Graph6 = {
           {0, 0, 0},
           {0, 0, 0},
           {0, 0, 0}};
        g.loadGraph(Graph6); // Load the graph to the object.

    g.printGraph();                                    // Should print: "This is a undirected and unweighted graph with 3 vertices and 0 edges"
    cout << Algorithms::isConnected(g) << endl;        // Should print: "0" (false).
    cout << Algorithms::shortestPath(g, 0,4) << endl; // Should print: "Start or End vertices are invalid!"
    cout << Algorithms::shortestPath(g, 0,2) << endl; // Should print: "There is no path between vertex 0 and vertex 2"  
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "No cycle detected" (false)
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "The graph is bipartite: A={0, 1, 2}, B={}"
    cout << ariel::Algorithms::negativeCycle(g) << endl; //Should print: "There is no negative cycle in the graph" (false).;


    //EX2 Demo parts
     ariel::Graph g1;
    // 3x3 matrix that represents a connected graph.
    vector<vector<int>> graph21 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph21); // Load the graph to the object.

    cout<<g1; // Should print the matrix of the graph: [0, 1, 0], [1, 0, 1], [0, 1, 0]

    // 3x3 matrix that represents a weighted connected graph.
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    ariel::Graph g2;
    g2.loadGraph(weightedGraph); // Load the graph to the object.

    ariel::Graph g3 = g1 + g2; // Add the two graphs together.
    cout<<g3;           // Should print the matrix of the graph: [0, 2, 1], [2, 0, 3], [1, 3, 0]

    g1 *= -2;        // Multiply the graph by -2.
    cout<<g1; // Should print the matrix of the graph: [0, -2, 0], [-2, 0, -2], [0, -2, 0]

    g1 /= -2;
    ariel::Graph g4 = g1 * g2; // Multiply the two graphs together.
    cout<<g4;           // Should print the multiplication of the matrices of g1 and g2: [0, 0, 2], [1, 0, 1], [1, 0, 0]

    // 5x5 matrix that represents a connected graph.
    vector<vector<int>> graph22 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    ariel::Graph g5;
    g5.loadGraph(graph22); // Load the graph to the object.
    try
    {
        ariel::Graph g6 = g5 * g1; // Multiply the two graphs together.
    }
    catch (const std::invalid_argument &e)
    {
        cout << e.what() << endl; // Should print "The number of columns in the first matrix must be equal to the number of rows in the second matrix."
    }
}