/** Implementation of class Graph*/

#include "Graph.hpp"
using namespace ariel;

void Graph::loadGraph(vector<vector<int>> adjMatrix) {
    if(adjMatrix.empty()){
        throw invalid_argument("The matrix is empty");
    }
    if ( adjMatrix.size()!=adjMatrix[0].size())
    {
        throw invalid_argument("Not a valid graph!");
    }
    
    this->adjMatrix = adjMatrix; //loading the actual matrix
    this->numVertices = adjMatrix.size(); //Initializing all flags for later use
    this->numEdges = 0;
    this->directed = false;
    this->weighted = false;
    this->sameWeight = true;
    this->negative = false;
    bool firstEdge = true;
    int firstEdgeVal = 0;
    for(size_t i = 0; i < numVertices; i++){
        for(size_t j = 0; j < numVertices; j++){
            if(adjMatrix[i][j] != 0){
                if (i==j)
                {
                    throw invalid_argument("Not a valid graph!");
                }
                
                numEdges++;   //counting each edge
                if (adjMatrix[i][j]<0) negative =true; //updates negative if there is a negative edge
                if (adjMatrix[i][j]!=adjMatrix[j][i]) directed = true; //updates directed if the graph is directed
                if (adjMatrix[i][j]!=0&&adjMatrix[i][j]!=1) weighted = true; //updates weighted if the graph is weighted
                if (firstEdge){ //checks if all the edges have the same weight, uses a flag to check the first valid edge, and then compares all the other edges to it
                    firstEdgeVal = adjMatrix[i][j];
                    firstEdge = false;
                }
                else if (adjMatrix[i][j]!=firstEdgeVal) sameWeight = false;
            }
        }
    }
    if (!directed) numEdges/=2;
    loaded = true;
}
 const void Graph::printGraph()  { //prints the graph according to the flags
     if(!loaded){
            throw invalid_argument("The graph is not loaded");
        }
    if (!directed&&!weighted){
        cout<<"This is a undirected and unweighted graph with " << numVertices << " vertices and " << numEdges <<" edges"<<endl;
    }
    if (!directed&&weighted&&!negative){
        cout<<"This is a undirected weighted graph with non-negative weights, " << numVertices << " vertices and " << numEdges <<" edges"<<endl;
    }
    if (!directed&&weighted&&negative){
        cout<<"This is a undirected weighted graph with negative weights, " << numVertices << " vertices and " << numEdges <<" edges"<<endl;
    }
    if (directed&&!weighted){
        cout<<"This is a directed and unweighted graph with " << numVertices << " vertices and " << numEdges <<" edges"<<endl;
    }
    if (directed&&weighted&&!negative){
        cout<<"This is a directed weighted graph with non-negative weights, " << numVertices << " vertices and " << numEdges <<" edges"<<endl;
    }
    if (directed&&weighted&&negative){
        cout<<"This is a directed weighted graph with negative weights, " << numVertices << " vertices and " << numEdges <<" edges"<<endl;
    }
}
/**
 @brief  A utill function that checks if a matrix contains another matrix
 @param matrixA - the matrix to check if it contains matrixB
 @param matrixB - the matrix to check if it is contained in matrixA
 @return true if matrixA contains matrixB, false otherwise
*/
static bool contains(const vector<vector<int>> &matrixA, const vector<vector<int>> &matrixB)
{
    int n = matrixA.size();
    int m = matrixB.size();
    if (n < m)
        return false;
    for (size_t i = 0; i <= n - m; ++i) //checks of each possible starting point of the matrix
    {
        for (size_t j = 0; j <= n - m; ++j)
        {
            bool match = true;
            for (size_t x = 0; x < m; ++x) //checks if the submatrix of matrixA is equal to matrixB
            {
                for (size_t y = 0; y < m; ++y)
                {
                    if (matrixA[i + x][j + y] != matrixB[x][y])
                    {
                        match = false;
                        break;
                    }
                }
                if (!match)
                    break;
            }
            if (match)
            {
                return true;
            }
        }
    }

    return false;
}




/**
 @brief overloading the + operator
  @param other - the graph to add to the current graph
  @return the new graph after the addition
    @throw invalid_argument if one of the graphs is not loaded or if the graphs have different number of vertices

*/
Graph Graph::operator+(const Graph &other) const
{
    if (!loaded || !other.loaded)
    {
        throw invalid_argument("One of the graphs is not loaded");
    }
    if (numVertices != other.numVertices)
    {
        throw invalid_argument("The graphs have different number of vertices");
    }
    vector<vector<int>> newMatrix((size_t)numVertices, vector<int>((size_t)numVertices, 0));
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
Graph Graph::operator-(const Graph &other) const
{
    if (!loaded || !other.loaded)
    {
        throw invalid_argument("One of the graphs is not loaded");
    }
    if (numVertices != other.numVertices)
    {
        throw invalid_argument("The graphs have different number of vertices");
    }
    vector<vector<int>> newMatrix((size_t)numVertices, vector<int>((size_t)numVertices, 0));
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
            adjMatrix[i][j] = adjMatrix[i][j] - other.adjMatrix[i][j];
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
Graph Graph::operator+()
{
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
Graph Graph::operator-()
{
    if (!loaded)
    {
        throw invalid_argument("The graph is not loaded");
    }
    Graph newGraph;
    vector<vector<int>> newMatrix((size_t)numVertices, vector<int>((size_t)numVertices, 0));
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
Graph Graph::operator*(const Graph &other) const 
{
    if (!loaded || !other.loaded)
    {
        throw invalid_argument("One of the graphs is not loaded");
    }
    if (numVertices != other.numVertices)
    {
        throw invalid_argument("The graphs have different number of vertices");
    }
    vector<vector<int>> newMatrix((size_t)numVertices, vector<int>((size_t)numVertices, 0));
    for (size_t i = 0; i < numVertices; i++) // Matrix multiplication
    {
        for (size_t j = 0; j < numVertices; j++)
        {
            for (size_t k = 0; k < numVertices; k++)
            {
                newMatrix[i][j] += adjMatrix[i][k] * other.adjMatrix[k][j];
            }
        }
    }
    for (size_t i = 0; i < numVertices; i++)
    { // After the multiplication, the diagonal might not be 0, so we need to set it to 0
        if (newMatrix[i][i] != 0)
        {
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
            adjMatrix[i][j] = adjMatrix[i][j] + other.adjMatrix[i][j];
        }
    }
    this->loadGraph(adjMatrix); // updates the graph
    return *this;
}

/**
     @brief overloading the *= operator
     @param other - the graph to multiply with the current graph
     @return the current graph after the multiplication
     @throw invalid_argument if one of the graphs is not loaded or if the graphs have different number of vertices
*/
Graph Graph::operator*=(const Graph &other)
{
    if (!loaded || !other.loaded)
    {
        throw invalid_argument("One of the graphs is not loaded");
    }
    if (numVertices != other.numVertices)
    {
        throw invalid_argument("The graphs have different number of vertices");
    }
    vector<vector<int>> newMatrix((size_t)numVertices, vector<int>((size_t)numVertices, 0));
    for (size_t i = 0; i < numVertices; i++) // Matrix multiplication
    {
        for (size_t j = 0; j < numVertices; j++)
        {
            for (size_t k = 0; k < numVertices; k++)
            {
                newMatrix[i][j] += adjMatrix[i][k] * other.adjMatrix[k][j];
            }
        }
    }
    for (size_t i = 0; i < numVertices; i++)
    { // After the multiplication, the diagonal might not be 0, so we need to set it to 0
        if (newMatrix[i][i] != 0)
        {
            newMatrix[i][i] = 0;
        }
    }
    this->loadGraph(newMatrix);
    return *this;
}
/**
     @brief overloading the == operator. Checks if the graphs are equal. The graphs are equal if they have the same number of vertices and the same edges, or if none contains the other
     @param other - the graph to compare with
     @return true if the graphs are equal, false otherwise
     @throw invalid_argument if one of the graphs is not loaded
*/
bool Graph::operator==(const Graph &other) const
{

    if (!(*this).loaded || !other.loaded)
    {
       
        throw invalid_argument("One of the graph isn't loaded");
    }
    bool eq = true;                                  //If the graphs have the same number of vertices and the same edges, go through the matrix and check if they are equal
    if (this->numVertices == other.numVertices)
    {
        for (size_t i = 0; i < numVertices; i++)
        {
            for (size_t j = 0; j < numVertices; j++)
            {
                if (adjMatrix[i][j] != other.adjMatrix[i][j])
                {
                    eq = false;
                    break;
                }
            }
        }
        if (eq) //If the graphs are equal, return true
            return true;
    }
    if (!((*this) > other) && !((*this) < other)) //If the graphs are not equal, check if one contains the other, if so, they are not equal, otherwise they are
        return true;
    return false;
}
/**
     @brief overloading the != operator. Checks if the graphs are not equal. 
     @param other - the graph to compare with
     @return true if the graphs are not equal, false otherwise
     @throw invalid_argument if one of the graphs is not loaded
*/
bool Graph::operator!=(const Graph &other) const
{
    return !(*this == other);
}
/**
     @brief overloading the > operator. Checks if the current graph is greater than the other graph. The current graph is greater than the other graph if it contains the other graph, or if it has more edges and the other graph dosent contain it, or if it has more vertices.If all equal, the graphs are equal
     @param other - the graph to compare with
     @return true if the current graph is greater than the other graph, false otherwise
     @throw invalid_argument if one of the graphs is not loaded
*/
bool Graph::operator>(const Graph &other) const
{
    if (!loaded || !other.loaded)
    {
        throw invalid_argument("One of the graph isn't loaded");
    }

    if (this->numVertices == other.numVertices)  //If the graphs have the same number of vertices and the same edges, go through the matrix and check if they are equal. if they are, return false
    {
        bool eq = true;
        for (size_t i = 0; i < numVertices; i++)
        {
            for (size_t j = 0; j < numVertices; j++)
            {
                if (this->adjMatrix[i][j] != other.adjMatrix[i][j])
                {
                    eq = false;
                    break;
                }
            }
            if (!eq)
                break;
        }
        if (eq)
            return false;
    }
    bool g1Cg2 = contains(this->adjMatrix, other.adjMatrix);//checks if the current graph contains the other graph
    bool g2Cg1 = contains(other.adjMatrix, this->adjMatrix);//checks if the other graph contains the current graph

    if (g1Cg2)//if the current graph contains the other graph, return true
        return true; 
    else if (g2Cg1)//if the other graph contains the current graph, return false
        return false;
    if (this->numEdges != other.numEdges)//else, if the current graph has more edges, return true
        return this->numEdges > other.numEdges;
    return this->numVertices > other.numVertices;//if they have the same number of edges, return true if the current graph has more vertices
}
/**
     @brief overloading the < operator. Checks if the current graph is less than the other graph. 
     @param other - the graph to compare with
     @return true if the current graph is less than the other graph, false otherwise
     @throw invalid_argument if one of the graphs is not loaded
*/
bool Graph::operator<(const Graph &other) const
{
    if (!loaded || !other.loaded)
    {
        throw invalid_argument("One of the graph isn't loaded");
    }
    Graph g;
    g.loadGraph(other.adjMatrix);
    return ( g > (*this));
}
/**
     @brief overloading the < operator. Checks if the current graph is less than or equal to the other graph. 
     @param other - the graph to compare with
     @return true if the current graph is less than or equal to the other graph, false otherwise
     @throw invalid_argument if one of the graphs is not loaded
*/ 
bool Graph::operator<=(const Graph &other) const

{
     if (!loaded || !other.loaded)
    {
        throw invalid_argument("One of the graph isn't loaded");
    }
    return ((*this) == other) || ((*this) < other);
}
/**
     @brief overloading the > operator. Checks if the current graph is greater than or equal to the other graph. 
     @param other - the graph to compare with
     @return true if the current graph is greater than or equal to the other graph, false otherwise
     @throw invalid_argument if one of the graphs is not loaded
*/
bool Graph::operator>=(const Graph &other) const
{
     if (!loaded || !other.loaded)
    {
        throw invalid_argument("One of the graph isn't loaded");
    }
    return ((*this) == other) || ((*this) > other);
}
/**
 @brief overloading the ++X operator. Increments all the edges in the graph by 1. (Only the edges that exists)
 @return the current graph after the increment
 @throw invalid_argument if the graph is not loaded
*/
Graph Graph::operator++()
{
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
Graph Graph::operator--()
{
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
Graph Graph::operator++(int)
{
    if (!loaded)
    {
        throw invalid_argument("The graph is not loaded");
    }

 
    Graph newGraph = *this;
    vector<vector<int>> newMatrix((size_t)numVertices, vector<int>((size_t)numVertices, 0));
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
    
    (*this).loadGraph(adjMatrix);
    return newGraph;
}
/**
     @brief overloading the X-- operator. Decrements all the edges in the graph by 1. (Only the edges that exists)
     @return the current graph before the decrement
     @throw invalid_argument if the graph is not loaded
*/
Graph Graph::operator--(int)
{
    if (!loaded)
    {
        throw invalid_argument("The graph is not loaded");
    }

    Graph newGraph = *this;
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
    (*this).loadGraph(adjMatrix);
    return newGraph;
}
/**
     @brief overloading the * operator, multiplies the graph by a scalar
     @param x - the scalar to multiply the graph by
     @return the new graph after the multiplication
     @throw invalid_argument if the graph is not loaded
*/
Graph Graph::operator*(int x) const
{
    if (!loaded)
    {
        throw invalid_argument("The graph is not loaded");
    }

    Graph newGraph;
    vector<vector<int>> newMatrix((size_t)numVertices, vector<int>((size_t)numVertices, 0));
    for (size_t i = 0; i < numVertices; i++)
    {
        for (size_t j = 0; j < numVertices; j++)
        {
            newMatrix[i][j] = adjMatrix[i][j] * x;
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
Graph Graph::operator*=(int x)
{
    if (!loaded)
    {
        throw invalid_argument("The graph is not loaded");
    }

    for (size_t i = 0; i < numVertices; i++)
    {
        for (size_t j = 0; j < numVertices; j++)
        {

            adjMatrix[i][j] = adjMatrix[i][j] * x;
        }
    }
    this->loadGraph(adjMatrix);
    return *this;
}
/**
 * @brief overloading the << operator, prints the matrix of the graph
 * @param output - the output stream
 * @param g - the graph to print
 * @return the output stream
 * @throw invalid_argument if the graph is not loaded
*/
 ostream& ariel::operator<<(ostream &output, const Graph &g){
    if (!g.isLoaded())
    {
        throw invalid_argument("The graph isn't loaded");
    }
    vector<vector<int>> adjMatrix = g.getAdjMatrix();
    output<<"The matrix of the graph is:\n";
    for (size_t i = 0; i < adjMatrix.size(); i++)
    {
        output << "[";
        for (size_t j = 0; j < adjMatrix.size() - 1;j++)
        {
            output << adjMatrix[i][j] << ", ";
        }
        output << adjMatrix[i][adjMatrix.size() - 1] << "]"<<endl;
    }
    return output;
}

/**
 * @brief overloading the / operator, divides the graph by a scalar
 * @param x - the scalar to divide the graph by
 * @return the new graph after the division
 * @throw invalid_argument if the graph is not loaded or if x is 0
*/
 Graph Graph::operator/(int x) const { 
    if (!loaded)
    {
        throw invalid_argument("The graph is not loaded");
    }
    if (x==0)
    {
        throw invalid_argument("Cannot divide by 0");
    }
    

    Graph newGraph;
    vector<vector<int>> newMatrix((size_t)numVertices, vector<int>((size_t)numVertices, 0));
    for (size_t i = 0; i < numVertices; i++)
    {
        for (size_t j = 0; j < numVertices; j++)
        {
            newMatrix[i][j] = adjMatrix[i][j] / x;
        }
    }
    newGraph.loadGraph(newMatrix);
    return newGraph;


 }
/**
 * @brief overloading the /= operator, divides the graph by a scalar
 *  @param x - the scalar to divide the graph by
 * @return the current graph after the division
 * @throw invalid_argument if the graph is not loaded or if x is 0
*/
 Graph Graph::operator/=(int x)
{
    if (!loaded)
    {
        throw invalid_argument("The graph is not loaded");
    }
    if (x==0)
    {
        throw invalid_argument("Cannot divide by 0");
    }   
    
    

    for (size_t i = 0; i < numVertices; i++)
    {
        for (size_t j = 0; j < numVertices; j++)
        {

            adjMatrix[i][j] = adjMatrix[i][j] / x;
        }
    }
    this->loadGraph(adjMatrix);
    return *this;
}
