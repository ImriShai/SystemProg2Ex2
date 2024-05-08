/** Implementation of class Graph*/

#include "Graph.hpp"
using namespace ariel;

void Graph::loadGraph(vector<vector<int>> adjMatrix)
{
    if (adjMatrix.empty())
    {
        throw invalid_argument("The matrix is empty");
    }
    if (adjMatrix.size() != adjMatrix[0].size())
    {
        throw invalid_argument("Not a valid graph!");
    }

    this->adjMatrix = adjMatrix;          // loading the actual matrix
    this->numVertices = adjMatrix.size(); // Initializing all flags for later use
    this->numEdges = 0;
    this->directed = false;
    this->weighted = false;
    this->sameWeight = true;
    this->negative = false;
    bool firstEdge = true;
    int firstEdgeVal = 0;
    for (size_t i = 0; i < numVertices; i++)
    {
        for (size_t j = 0; j < numVertices; j++)
        {
            if (adjMatrix[i][j] != 0)
            {
                if (i == j)
                {
                    throw invalid_argument("Not a valid graph!");
                }

                numEdges++; // counting each edge
                if (adjMatrix[i][j] < 0)
                    negative = true; // updates negative if there is a negative edge
                if (adjMatrix[i][j] != adjMatrix[j][i])
                    directed = true; // updates directed if the graph is directed
                if (adjMatrix[i][j] != 0 && adjMatrix[i][j] != 1)
                    weighted = true; // updates weighted if the graph is weighted
                if (firstEdge)
                { // checks if all the edges have the same weight, uses a flag to check the first valid edge, and then compares all the other edges to it
                    firstEdgeVal = adjMatrix[i][j];
                    firstEdge = false;
                }
                else if (adjMatrix[i][j] != firstEdgeVal)
                    sameWeight = false;
            }
        }
    }
    if (!directed)
        numEdges /= 2;
    loaded = true;
}
void Graph::printGraph()
{ // prints the graph according to the flags
    if (!loaded)
    {
        throw invalid_argument("The graph is not loaded");
    }
    if (!directed && !weighted)
    {
        cout << "This is a undirected and unweighted graph with " << numVertices << " vertices and " << numEdges << " edges" << endl;
    }
    if (!directed && weighted && !negative)
    {
        cout << "This is a undirected weighted graph with non-negative weights, " << numVertices << " vertices and " << numEdges << " edges" << endl;
    }
    if (!directed && weighted && negative)
    {
        cout << "This is a undirected weighted graph with negative weights, " << numVertices << " vertices and " << numEdges << " edges" << endl;
    }
    if (directed && !weighted)
    {
        cout << "This is a directed and unweighted graph with " << numVertices << " vertices and " << numEdges << " edges" << endl;
    }
    if (directed && weighted && !negative)
    {
        cout << "This is a directed weighted graph with non-negative weights, " << numVertices << " vertices and " << numEdges << " edges" << endl;
    }
    if (directed && weighted && negative)
    {
        cout << "This is a directed weighted graph with negative weights, " << numVertices << " vertices and " << numEdges << " edges" << endl;
    }
}
/**
 @brief overloading the + operator
  @param other - the graph to add to the current graph
  @return the new graph after the addition
    @throw invalid_argument if one of the graphs is not loaded or if the graphs have different number of vertices

*/
Graph Graph::operator+(const Graph &other)
{
    if (!loaded || !other.loaded)
    {
        throw invalid_argument("One of the graphs is not loaded");
    }
    if (numVertices != other.numVertices)
    {
        throw invalid_argument("The graphs have different number of vertices");
    }
    vector<vector<int>> newMatrix(numVertices, vector<int>(numVertices, 0));
    for (size_t i = 0; i < numVertices; i++)
    {
        for (size_t j = 0; j < numVertices; j++)
        {
            newMatrix[i][j] = adjMatrix[i][j] + other.adjMatrix[i][j];
        }
    }
    Graph newGraph;
    newGraph.loadGraph(newMatrix);
    return newGraph;
}

/**
     @brief overloading the - operator
     @param other - the graph to subtract from the current graph
     @return the new graph after the subtraction
     @throw invalid_argument if one of the graphs is not loaded or if the graphs have different number of vertices
*/
Graph Graph::operator-(const Graph &other)
{
    if (!loaded || !other.loaded)
    {
        throw invalid_argument("One of the graphs is not loaded");
    }
    if (numVertices != other.numVertices)
    {
        throw invalid_argument("The graphs have different number of vertices");
    }
    vector<vector<int>> newMatrix(numVertices, vector<int>(numVertices, 0));
    for (size_t i = 0; i < numVertices; i++)
    {
        for (size_t j = 0; j < numVertices; j++)
        {
            newMatrix[i][j] = adjMatrix[i][j] - other.adjMatrix[i][j];
        }
    }
    Graph newGraph;
    newGraph.loadGraph(newMatrix);
    return newGraph;
}

/**
     @brief overloading the -= operator
     @param other - the graph to subtract from the current graph
     @return the current graph after the subtraction
     @throw invalid_argument if one of the graphs is not loaded or if the graphs have different number of vertices
*/
Graph Graph::operator-=(const Graph &other)
{
    if (!loaded || !other.loaded)
    {
        throw invalid_argument("One of the graphs is not loaded");
    }
    if (numVertices != other.numVertices)
    {
        throw invalid_argument("The graphs have different number of vertices");
    }
    for (size_t i = 0; i < numVertices; i++)
    {
        for (size_t j = 0; j < numVertices; j++)
        {
            adjMatrix[i][j] = adjMatrix[i][j] + other.adjMatrix[i][j];
        }
    }
    this->loadGraph(adjMatrix);
    return *this;
}

/**
     @brief overloading the + unary operator. Actually does nothing, just returns the current graph
     @return the current graph
     @throw invalid_argument if the graph is not loaded
*/
Graph Graph::operator+(){
    if (!loaded)
    {
        throw invalid_argument("The graph is not loaded");
    }
    Graph newGraph;
    newGraph.loadGraph(adjMatrix);
    return newGraph;

}
/**
     @brief overloading the - unary operator. Negates all the values in the matrix
     @return the new graph after the negation
     @throw invalid_argument if the graph is not loaded
*/
Graph Graph::operator-(){
    if (!loaded)
    {
        throw invalid_argument("The graph is not loaded");
    }
    Graph newGraph;
    vector<vector<int>> newMatrix(numVertices, vector<int>(numVertices, 0));
    for (size_t i = 0; i < numVertices; i++)
    {
        for (size_t j = 0; j < numVertices; j++)
        {
            newMatrix[i][j] = -adjMatrix[i][j];
        }
    }
    newGraph.loadGraph(newMatrix);
    return newGraph;
}
/**
 * @brief overloading the * operator, multiplies the current graph by the other graph, matrix multiplication
 * @param other - the graph to multiply with the current graph
 * @return the new graph after the multiplication
 * @throw invalid_argument if one of the graphs is not loaded or if the graphs have different number of vertices
*/
Graph Graph::operator*(const Graph &other){
    if (!loaded || !other.loaded)
    {
        throw invalid_argument("One of the graphs is not loaded");
    }
    if (numVertices != other.numVertices)
    {
        throw invalid_argument("The graphs have different number of vertices");
    }
    vector<vector<int>> newMatrix(numVertices, vector<int>(numVertices, 0));
    for (size_t i = 0; i < numVertices; i++) //Matrix multiplication
    {
        for (size_t j = 0; j < numVertices; j++)
        {
            for (size_t k = 0; k < numVertices; k++)
            {
                newMatrix[i][j] += adjMatrix[i][k] * other.adjMatrix[k][j];
            }
        }
    }
    for(size_t i = 0; i < numVertices;i++){ //After the multiplication, the diagonal might not be 0, so we need to set it to 0
        if(newMatrix[i][i] != 0){
            newMatrix[i][i] = 0;
        }
    }
    Graph newGraph;
    newGraph.loadGraph(newMatrix);
    return newGraph;
}            
/**
     @brief overloading the += operator
     @param other - the graph to add from the current graph
     @return the current graph after the addition
     @throw invalid_argument if one of the graphs is not loaded or if the graphs have different number of vertices
*/
Graph Graph::operator+=(const Graph &other)
{
    if (!loaded || !other.loaded)
    {
        throw invalid_argument("One of the graphs is not loaded");
    }
    if (numVertices != other.numVertices)
    {
        throw invalid_argument("The graphs have different number of vertices");
    }
    for (size_t i = 0; i < numVertices; i++)
    {
        for (size_t j = 0; j < numVertices; j++)
        {
            adjMatrix[i][j] = adjMatrix[i][j] - other.adjMatrix[i][j];
        }
    }
    this->loadGraph(adjMatrix); // updates the graph
    return *this;
}

Graph Graph::operator*=(const Graph &other){
    if (!loaded || !other.loaded)
    {
        throw invalid_argument("One of the graphs is not loaded");
    }
    if (numVertices != other.numVertices)
    {
        throw invalid_argument("The graphs have different number of vertices");
    }
    vector<vector<int>> newMatrix(numVertices, vector<int>(numVertices, 0));
    for (size_t i = 0; i < numVertices; i++) //Matrix multiplication
    {
        for (size_t j = 0; j < numVertices; j++)
        {
            for (size_t k = 0; k < numVertices; k++)
            {
                newMatrix[i][j] += adjMatrix[i][k] * other.adjMatrix[k][j];
            }
        }
    }
    for(size_t i = 0; i < numVertices;i++){ //After the multiplication, the diagonal might not be 0, so we need to set it to 0
        if(newMatrix[i][i] != 0){
            newMatrix[i][i] = 0;
        }
    }
    this->loadGraph(newMatrix);
    return *this;
}
 bool Graph::operator==(const Graph& other); //overloading the == operator
    bool Graph::operator!=(const Graph& other); //overloading the != operator
    bool Graph::operator<(const Graph& other); //overloading the < operator
    bool Graph::operator>(const Graph& other); //overloading the > operator
    bool Graph::operator<=(const Graph& other); //overloading the <= operator
    bool Graph::operator>=(const Graph& other); //overloading the >= operator
    /**
     @brief overloading the ++X operator. Increments all the edges in the graph by 1. (Only the edges that exists)
     @return the current graph after the increment
     @throw invalid_argument if the graph is not loaded
*/
Graph Graph::operator++(){
    if (!loaded)
    {
        throw invalid_argument("The graph is not loaded");
    }
    
    
    for (size_t i = 0; i < numVertices; i++)
    {
        for (size_t j = 0; j < numVertices; j++)
        {
            if (adjMatrix[i][j] != 0)
            {
            adjMatrix[i][j] = adjMatrix[i][j] + 1;
            }
        }
    }
    this->loadGraph(adjMatrix);
    return *this;
}     
/**
     @brief overloading the --X operator. Decrements all the edges in the graph by 1. (Only the edges that exists)
     @return the current graph after the decrement
     @throw invalid_argument if the graph is not loaded
*/                             
Graph Graph::operator--(){
     if (!loaded)
    {
        throw invalid_argument("The graph is not loaded");
    }
    
    
    for (size_t i = 0; i < numVertices; i++)
    {
        for (size_t j = 0; j < numVertices; j++)
        {
            if (adjMatrix[i][j] != 0)
            {
            adjMatrix[i][j] = adjMatrix[i][j] - 1;
            }
        }
    }
    this->loadGraph(adjMatrix);
    return *this;
}                                  
/**
     @brief overloading the X++ operator. Increments all the edges in the graph by 1. (Only the edges that exists)
     @return the current graph before the increment
     @throw invalid_argument if the graph is not loaded
*/
Graph Graph::operator++(int){
     if (!loaded)
    {
        throw invalid_argument("The graph is not loaded");
    }
    
    Graph newGraph;
    vector<vector<int>> newMatrix(numVertices, vector<int>(numVertices, 0));
    for (size_t i = 0; i < numVertices; i++)
    {
        for (size_t j = 0; j < numVertices; j++)
        {
            if (adjMatrix[i][j] != 0)
            {
            newMatrix[i][j] = adjMatrix[i][j] + 1;
            }
        }
    }
    newGraph.loadGraph(newMatrix);
    return newGraph;
}                                  
/**
     @brief overloading the X-- operator. Decrements all the edges in the graph by 1. (Only the edges that exists)
     @return the current graph before the decrement
     @throw invalid_argument if the graph is not loaded
*/
Graph Graph::operator--(int){
      if (!loaded)
    {
        throw invalid_argument("The graph is not loaded");
    }
    
    Graph newGraph;
    vector<vector<int>> newMatrix(numVertices, vector<int>(numVertices, 0));
    for (size_t i = 0; i < numVertices; i++)
    {
        for (size_t j = 0; j < numVertices; j++)
        {
            if (adjMatrix[i][j] != 0)
            {
            newMatrix[i][j] = adjMatrix[i][j] - 1;
            }
        }
    }
    newGraph.loadGraph(newMatrix);
    return newGraph;
}
/**
     @brief overloading the * operator, multiplies the graph by a scalar
     @param x - the scalar to multiply the graph by
     @return the new graph after the multiplication
     @throw invalid_argument if the graph is not loaded
*/
Graph Graph::operator*(int x){
      if (!loaded)
    {
        throw invalid_argument("The graph is not loaded");
    }
    
    Graph newGraph;
    vector<vector<int>> newMatrix(numVertices, vector<int>(numVertices, 0));
    for (size_t i = 0; i < numVertices; i++)
    {
        for (size_t j = 0; j < numVertices; j++)
        {
            newMatrix[i][j] = adjMatrix[i][j]*x;
        }
    }
    newGraph.loadGraph(newMatrix);
    return newGraph;
}
/**
     @brief overloading the *= operator, multiplies the graph by a scalar
     @param x - the scalar to multiply the graph by
     @return the current graph after the multiplication
     @throw invalid_argument if the graph is not loaded
*/
Graph Graph::operator*=(int x){
      if (!loaded)
    {
        throw invalid_argument("The graph is not loaded");
    }

    for (size_t i = 0; i < numVertices; i++)
    {
        for (size_t j = 0; j < numVertices; j++)
        {
           
            adjMatrix[i][j] = adjMatrix[i][j]*x;
           
        }
    }
    this->loadGraph(adjMatrix);
    return *this;
}
friend ostream &operator<<(ostream &output, const Graph &g); // overloading the << operator
