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
    const vector<vector<int>>& getAdjMatrix() const{
        return adjMatrix;
    }
    const void printGraph();

    const bool isDirected() const{
         if(!loaded){
            throw invalid_argument("The graph is not loaded");
        }
        return directed;
    }
   const  bool isNegative() const{
         if(!loaded){
            throw invalid_argument("The graph is not loaded");
        }
        return negative;
    }
   const  bool isWeighted() const{
         if(!loaded){
            throw invalid_argument("The graph is not loaded");
        }
        return weighted;

    }
  const  bool isSameWeight() const{
        if(!loaded){
            throw invalid_argument("The graph is not loaded");
        }
        return sameWeight;
    }
   const bool isLoaded() const{
        return loaded;
    }

    void loadGraph(vector<vector<int>> adjMatrix);




    Graph operator+(const Graph& other); //overloading the + operator
    Graph operator-(const Graph& other); //overloading the - operator
    Graph operator-=(const Graph& other); //overloading the -= operator
    Graph operator+(); //overloading the + unary operator
    Graph operator-(); //overloading the - unary operator
    Graph operator*(const Graph& other); //overloading the * operator
    Graph operator+=(const Graph& other); //overloading the += operator
    Graph operator*=(const Graph& other); //overloading the *= operator
    bool  operator==(const Graph& other); //overloading the == operator
    bool operator!=(const Graph& other); //overloading the != operator
    bool operator<(const Graph& other); //overloading the < operator
    bool operator>(const Graph& other); //overloading the > operator
    bool operator<=(const Graph& other); //overloading the <= operator
    bool operator>=(const Graph& other); //overloading the >= operator
    Graph operator++(); //overloading the X++ operator
    Graph operator--(); //overloading the X-- operator
    Graph operator++(int); //overloading the ++X operator
    Graph operator--(int); //overloading the --X operator
    Graph operator*(int x); //overloading the * operator, multiplying the graph by a scalar
    Graph operator*=(int x); //overloading the *= operator, multiplying the graph by a scalar
    friend ostream& operator<<(ostream& output, const Graph& g); //overloading the << operator 

};

}