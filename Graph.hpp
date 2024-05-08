/** header file of class Graph*/
#pragma once
#include <iostream>
#include <vector>
using namespace std;
namespace ariel{

/** A class representing a graph*/
class Graph{
    private:
     vector<vector<int>> adjMatrix;
    int numVertices;
    int numEdges;
    bool directed;
    bool negative;
    bool weighted;
    bool sameWeight;
    bool loaded;
    public:
    Graph():loaded(false){};
    vector<vector<int>> getAdjMatrix(){
        return adjMatrix;
    }
    void printGraph();

    bool isDirected(){
         if(!loaded){
            throw invalid_argument("The graph is not loaded");
        }
        return directed;
    }
    bool isNegative(){
         if(!loaded){
            throw invalid_argument("The graph is not loaded");
        }
        return negative;
    }
    bool isWeighted(){
         if(!loaded){
            throw invalid_argument("The graph is not loaded");
        }
        return weighted;

    }
    bool isSameWeight(){
        if(!loaded){
            throw invalid_argument("The graph is not loaded");
        }
        return sameWeight;
    }
    bool isLoaded(){
        return loaded;
    }

    void loadGraph(vector<vector<int>> adjMatrix);

};
}