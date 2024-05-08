/** Implementation of the Algorithm class*/
#include "Algorithms.hpp"

using namespace std;
/**
 * @brief A util function that checks if the graph contains a cycle
 * The function uses a modified version of the Depth First Search algorithm to find a cycle in the graph
 * The function uses the visited and parent vectors to keep track of the visited vertices and the parent of each vertex
 * The function goes through all the vertices, if there is an edge between the current vertex and the vertex i, and we haven't visited i yet, mark it as visited, update the parent vector, and recursively call the function
 * @param g the graph
 * @param v the current vertex to run the DFS from
 * @param visited the visited vector, that keeps track of the visited vertices
 * @param parent the parent vector, that keeps track of the parent of each vertex
 * @return the cycle if exists, otherwise return "No cycle detected"
 */
static int isContainsCycleUtil(ariel::Graph g, int v, vector<bool> &visited, vector<int> &parent)
{

    visited[(size_t)v] = true; // marking the current vertex as visited
    vector<vector<int>> adjMatrix = g.getAdjMatrix();
    for (size_t i = 0; i < adjMatrix.size(); i++)
    { // go through all the vertices
        if (adjMatrix[(size_t)v][i] && !visited[i])
        {                  // if there is an edge between the current vertex and the vertex i, and we haven't visited i yet
            parent[i] = v; // update the parent of i to be v and recursively call the function
            int res = isContainsCycleUtil(g, i, visited, parent);
            if (res != -1)
            {
                return res;
            }
        }

        else if (adjMatrix[(size_t)v][i] && visited[i] && !g.isDirected() && parent[(size_t)v] != i)
        { // if there exists an edge between the current vertex and i, and we have visited i, and the edge we came from is a diffrent edge, then there is a cycle
            return v;
        }
        else if (adjMatrix[(size_t)v][i] && visited[i] && g.isDirected())
        { // if the graph is directed, we can go back to the parent
            size_t pre = (size_t)v;
            while(parent[pre]!=-1) pre = (size_t)parent[pre];// make sure that v and i are actually at the same cycle, and that i is not just visited before, but with no link to v
            if (pre==i)
            return v;
        }
    }
    return -1;
}
/**
 * @brief A function that transposes the graph
 * The function goes through the adjacency matrix of the graph, and swaps the values of the i-th row and j-th column with the j-th row and i-th column
 * @param g the graph to transpose
 * @return the transposed graph
 * */
static ariel::Graph transpose(ariel::Graph g)
{
    vector<vector<int>> adjMatrix = g.getAdjMatrix();
    for (size_t i = 0; i < adjMatrix.size(); i++)
    {
        for (size_t j = 0; j < i; j++)
        {
            int temp = adjMatrix[i][j];
            adjMatrix[i][j] = adjMatrix[j][i];
            adjMatrix[j][i] = temp;
        }
    }
    g.loadGraph(adjMatrix);
    return g;
}
/**
 * @brief A function that runs the Depth First Search algorithm on the graph
 * The function uses the adjacency matrix of the graph, and the visited vector to keep track of the visited vertices
 * The function goes through all the vertices, if there is an edge between the start vertex and the current vertex, and the current vertex wasn't visited yet, mark it as visited and recursively call the function
 * @param g the graph
 * @param start the start vertex to run the DFS from
 * @param visited the visited vector, that keeps track of the visited vertices
 * */
static void DFS(ariel::Graph g, int start, vector<bool> &visited)
{
    visited[(size_t)start] = true;
    vector<vector<int>> adjMatrix = g.getAdjMatrix();
    for (size_t i = 0; i < adjMatrix.size(); i++)
    {
        if (adjMatrix[(size_t)start][i] && !visited[i])
        {
            DFS(g, i, visited);
        }
    }
}
/**
 * @brief A function that runs the Breadth First Search algorithm on the graph in order to find the shortest path between two vertices
 * The function uses the adjacency matrix of the graph, and the visited, distance, and parent vectors to keep track of the visited vertices, the distance from the start vertex, and the parent of each vertex
 * The function uses a queue to keep track of the vertices that we need to visit
 * The function goes through all the vertices, if there is an edge between the front vertex and the current vertex, and the current vertex wasn't visited yet, mark it as visited, update its distance and parent vectors, and push it to the queue
 * If we reached the end vertex, and the end vertex already been visited, create the path by going through the parent vector, and return it
 * @param g the graph
 * @param start the start vertex
 * @param end the end vertex
 * @return the path between the start and end vertices
 * */
static string BFS(ariel::Graph g, int start, int end)
{
    vector<vector<int>> adjMatrix = g.getAdjMatrix(); // get the adjacency matrix of the graph, and initialize the visited, distance, and parent vectors
    vector<bool> visited(adjMatrix.size(), false);
    vector<int> distance(adjMatrix.size(), INT_MAX);
    vector<int> parent(adjMatrix.size(), -1);
    queue<int> q;
    q.push(start); // push the start vertex to the queue, mark it as visited and set its distance to 0
    visited[(size_t)start] = true;
    distance[(size_t)start] = 0;

    while (!q.empty())
    { // while the queue isn't empty, pop the front vertex, and go through all the vertices, if there is an edge between the front vertex and the current vertex, and the current vertex wasn't visited yet, mark it as visited, update its distance and parent vectors, and push it to the queue
        int u = q.front();
        q.pop();
        for (size_t i = 0; i < adjMatrix.size(); i++)
        {
            if (adjMatrix[(size_t)u][i] && !visited[i])
            {
                visited[(size_t)i] = true;
                distance[(size_t)i] = distance[(size_t)u] + 1;
                parent[(size_t)i] = u;
                q.push(i);
            }
            if (i == end && parent[(size_t)end] != -1)
            { // if we reached the end vertex, and the end vertex already been visited, create the path by going through the parent vector, and return it
                string path = "";
                while (parent[(size_t)i] != -1)
                {
                    path = to_string(i) + "->" + path;
                    i = (size_t)parent[(size_t)i];
                }
                path = to_string(start) + "->" + path;
                path.pop_back();
                path.pop_back();
                return path;
            }
        }
    }
    return "There is no path between vertex " + to_string(start) + " and vertex " + to_string(end);
    ;
}
/**
 * @brief A function that runs the Dijkstra algorithm on the graph
 * The function uses the adjacency matrix of the graph, and the visited, distance, and parent vectors to keep track of the visited vertices, the distance from the start vertex, and the parent of each vertex
 * The function uses a priority queue to keep track of the vertices that we need to visit
 * The function goes through all the vertices, if there is an edge between the front vertex and the current vertex, and the current vertex wasn't visited yet, mark it as visited, update its distance and parent vectors, and push it to the priority queue
 * If we reached the end vertex, and the end vertex already been visited, create the path by going through the parent vector, and return it
 * @param g the graph
 * @param start the start vertex
 * @param end the end vertex
 * @return the path between the start and end vertices
 * */
static string dijkstra(ariel::Graph g, int start, int end)
{
    vector<vector<int>> adjMatrix = g.getAdjMatrix();
    size_t V = (size_t)adjMatrix.size(); // Number of vertices in the graph
    vector<int> dist(V, INT_MAX);        // Initialize distances to all vertices as infinite
    vector<bool> visited(V, false);      // Track visited vertices
    vector<int> prev(V, -1);             // To store the path

    // Create a priority queue to store vertices that are being preprocessed. used geekforgeeks for the priority queue usage
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Distance of source vertex from itself is always 0
    dist[(size_t)start] = 0;
    pq.push(make_pair(0, start));

    while (!pq.empty())
    {
        // The first vertex in pair is the minimum distance vertex, extract it from priority queue
        int u = pq.top().second;
        pq.pop();

        // Mark the picked vertex as visited
        visited[(size_t)u] = true;

        // Update dist value of the adjacent vertices of the picked vertex
        for (size_t v = 0; v < V; ++v)
        {
            // Update dist[v] only if it is not in visited, there is an edge from u to v,
            // and total weight of path from start to v through u is smaller than current value of dist[v]
            if (!visited[v] && adjMatrix[(size_t)u][v] && dist[(size_t)u] != INT_MAX && dist[(size_t)u] + adjMatrix[(size_t)u][v] < dist[v])
            {
                dist[v] = dist[(size_t)u] + adjMatrix[(size_t)u][v];
                pq.push(make_pair(dist[v], v));
                prev[v] = u;
            }
        }
    }

    // If there is no path between start and end
    if (dist[(size_t)end] == INT_MAX)
    {
        return "There is no path between vertex " + to_string(start) + " and vertex " + to_string(end);
    }

    // Store the shortest path
    string path = "";
    for (int v = end; v != -1; v = prev[(size_t)v])
    {
        path = to_string(v) + "->" + path;
    }

    // Remove the trailing "->"
    path = path.substr(0, path.length() - 2);

    return path;
}
/**
 * @brief A function that runs the Bellman-Ford algorithm on the graph
 * The function uses the adjacency matrix of the graph, and the distance and parent vectors to keep track of the distance from the start vertex, and the parent of each vertex
 * The function goes through all the vertices, if there is an edge between the current vertex and the vertex i, and the distance of the current vertex is not infinity, and the parent of the current vertex is not i, and the distance of the current vertex + the weight of the edge between the current vertex and i is smaller than the distance of i, update the distance of i and the parent of i
 * If we can still relax one of the edges, then there is a negative cycle, return "Negative cycle detected"
 * If there is no path between the start and end vertices, return "There is no path between vertex " + start + " and vertex " + end
 * If there is a path between the start and end vertices, create the path by going through the parent vector, and return it
 * @param g the graph
 * @param start the start vertex
 * @param end the end vertex
 * @return the path between the start and end vertices
 * */
static string bellmanFord(ariel::Graph g, int start, int end)
{

    vector<vector<int>> adjMatrix = g.getAdjMatrix();
    for (size_t i = 0; i < adjMatrix.size(); i++)
    {
        for (size_t j = 0; j < adjMatrix.size(); j++)
        {
            if (adjMatrix[i][j] == 0)
                adjMatrix[i][j] = INT_MAX;
        }
    }

    vector<int> distance(adjMatrix.size(), INT_MAX); // initialize the distance vector with infinity
    vector<int> parent(adjMatrix.size(), -1);        // initialize the parent vector with -1
    distance[(size_t)start] = 0;                     // set the distance of the start vertex to 0
    for (size_t i = 0; i <= adjMatrix.size() - 2; i++)
    { // run the loop n-1 times, where n is the number of vertices, each time relax all the edges
        for (size_t j = 0; j < adjMatrix.size(); j++)
        {
            for (size_t k = 0; k < adjMatrix.size(); k++)
            {
                if (!g.isDirected())
                {
                    if (adjMatrix[j][k] != INT_MAX && distance[(size_t)j] != INT_MAX && parent[j] != k && distance[(size_t)j] + adjMatrix[(size_t)j][(size_t)k] < distance[(size_t)k])
                    { // if the graph isn't directed, we cannot go back to the parent
                        distance[(size_t)k] = distance[(size_t)j] + adjMatrix[(size_t)j][(size_t)k];
                        parent[(size_t)k] = j;
                    }
                }
                if (g.isDirected())
                {
                    if (adjMatrix[j][k] != INT_MAX && distance[(size_t)j] != INT_MAX && distance[(size_t)j] + adjMatrix[(size_t)j][(size_t)k] < distance[(size_t)k])
                    { // else, we allow going back to the parent
                        distance[(size_t)k] = distance[(size_t)j] + adjMatrix[(size_t)j][(size_t)k];
                        parent[(size_t)k] = j;
                    }
                }
            }
        }
    }
    for (size_t j = 0; j < adjMatrix.size(); j++)
    { // run the loop one more time, if we can still relax one of the edges, then there is a negative cycle
        for (size_t k = 0; k < adjMatrix.size(); k++)
        {

            if (!g.isDirected() && adjMatrix[j][k] != INT_MAX && distance[(size_t)j] != INT_MAX && parent[j] != k && distance[(size_t)j] + adjMatrix[(size_t)j][(size_t)k] < distance[(size_t)k])
            { // if the graph isn't directed, we cannot go back to the parent
                return "Negative cycle detected";
            }

            else if (g.isDirected() && adjMatrix[j][k] != INT_MAX && distance[(size_t)j] != INT_MAX && distance[(size_t)j] + adjMatrix[(size_t)j][(size_t)k] < distance[(size_t)k])
            { // else, we allow going back to the parent
                return "Negative cycle detected";
            }
        }
    }

    if (distance[(size_t)end] == INT_MAX)
        return "There is no path between vertex " + to_string(start) + " and vertex " + to_string(end);
    string path = "";
    for (int v = end; v != -1; v = parent[(size_t)v])
    { // create the path by going through the parent vector
        path = to_string(v) + "->" + path;
    }
    path = path.substr(0, path.length() - 2); // remove the last "->"
    return path;
}

/**
 * @brief A function that checks if the graph is connected (stongly connected)
 * The function run DFS from some vertex, if we cant reach all the vertices, then the graph is not connected.
 * if we can reach all the vertices, then we transpose the graph and run DFS from the same vertex, if we can reach all the vertices, then the graph is strongly connected
 * @param g the graph
 * @return true if the graph is connected, otherwise return false
 * */
bool ariel::Algorithms::isConnected(ariel::Graph g)
{
     if(!g.isLoaded()){
            throw invalid_argument("The graph is not loaded");
        }
    vector<bool> visited(g.getAdjMatrix().size(), false);
    DFS(g, 0, visited); // running DFS from the first vertex
    for (size_t i = 0; i < visited.size(); i++)
    {
        if (!visited[i])
        {
            return false; // if there is a vertex that wasn't visited, the graph is not connected
        }
        visited[i] = false;
    }
    if (!g.isDirected())
        return true;

    // if we got here, then we can get to any vertex from the first vertex
    // then we will transpose the graph and run DFS from the first vertex again, if we visit every vertex, then we can reach from every vertex to the first vertex, so the graph is connected
    ariel::Graph gT;
    gT = transpose(g);
    DFS(gT, 0, visited);
    for (size_t i = 0; i < visited.size(); i++)
    {
        if (!visited[i])
        {
            return false;
        }
    }
    return true;
}

string ariel::Algorithms::isContainsCycle(ariel::Graph g)
{ // running a version of DSF that will return the actual cycle
 if(!g.isLoaded()){
            throw invalid_argument("The graph is not loaded");
        }
    vector<vector<int>> adjMatrix = g.getAdjMatrix();
    vector<bool> visited(adjMatrix.size(), false);
    vector<int> parent(adjMatrix.size(), -1);
    int start;
    for (size_t i = 0; i < adjMatrix.size(); i++)
    {
        if (!visited[i])
        { // if we haven't visited the vertex yet, call the helper function, that updates the parent vector, and returns true if there is a cycle
            start = isContainsCycleUtil(g, i, visited, parent);
            if (start != -1)
            {
                string cycle; // if there is a cycle, we will return the cycle, by going through the parent vector
                while (parent[(size_t)start] != -1)
                {
                    cycle = to_string(start) + "->" + cycle;
                    start = parent[(size_t)start];
                }
                cycle += to_string(i);
                cycle = to_string(i) + "->" + cycle;
                return cycle;
            }
        }
    }
    return "No cycle detected";
}


/**
 * @brief This function checks if the graph is bipartite
 * The function uses the BFS algorithm to check if the graph is bipartite, for every vertex in the graph, if the vertex is not colored yet, check if its connected to a vertex thats already colored, if so color it with the opposite color
 * then check all of its neighbors, if they are not colored yet, add them to the queue. If there is and edge between two colord vertices with the same color, then the graph is not bipartite.
 * @param g the graph
 * @return the two sets of the bipartite graph, or an error message if the graph is not bipartite
 */
string ariel::Algorithms::isBipartite(ariel::Graph g)
{
     if(!g.isLoaded()){
            throw invalid_argument("The graph is not loaded");
        }
    vector<vector<int>> adjMatrix = g.getAdjMatrix();
    vector<int> color(adjMatrix.size(), -1); // initialize the color vector with -1        
    queue<int> q;
    for (size_t i = 0; i < adjMatrix.size(); i++) //for every vertex in the graph
    {
        if (color[i] == -1) { // if the vertex is not colored yet, check if its connected to a vertex thats already colored, if so color it with the opposite color
           for (size_t j = 0; j < adjMatrix.size(); j++)
           {
             if (adjMatrix[i][j] && color[j] != -1)
             {
                color[i] = 1 - color[j];
                q.push(i);
                break;
             }
           }
           
        }
        if(color[i]==-1){ // if the vertex is not connected to any other vertex, color it with 1
            color[i] = 1;
            q.push(i);
        }
       
        

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (size_t i = 0; i < adjMatrix.size(); i++)
            {
                if (adjMatrix[(size_t)u][i] && color[i] == -1)
                {                                    // if there is an edge between u and i, and i is not colored yet
                    color[i] = 1 - color[(size_t)u]; // color i with the opposite color of u
                    q.push(i);                       // push i to the queue
                }
                else if (adjMatrix[(size_t)u][i] && color[i] == color[(size_t)u])
                { // if there is an edge between u and i, and they have the same color, then the graph is not bipartite
                    return "There is no valid bipartite partition of the graph";
                }
            }
        }
    }
    string res = "The graph is bipartite: A={";
    for (size_t i = 0; i < color.size(); i++)
    { // create the string representation of the first set
        if (color[i] == 1)
        {
            res += to_string(i) + ", ";
        }
    }
    res.pop_back(); // remove the last comma
    res.pop_back(); // remove the last space
    res += "}, B={";
    size_t bSize = 0;
    for (size_t i = 0; i < color.size(); i++)
    { // create the string representation of the second set and concatenate it to the first set
        if (color[i] == 0)
        {
            res += to_string(i) + ", ";
            bSize++;
        }
    }
    if (bSize > 0)
    {
        res.pop_back();
        res.pop_back();
    }
    res += "}";
    return res;
}

/**
 * @brief This function finds the shortest path between two vertices in the graph
 * The function uses the Bellman-Ford algorithm if the graph is negative, the BFS algorithm if the graph is unweighted or has same non-negative weight, and the Dijkstra algorithm if the graph is weighted
 * @param g the graph
 * @param start the start vertex
 * @param end the end vertex
 * @return the path between the start and end vertices, or an error message if the start or end vertices are invalid, or if there is no path between the start and end vertices
 */
string ariel::Algorithms::shortestPath(ariel::Graph g, int start, int end)
{
     if(!g.isLoaded()){
            throw invalid_argument("The graph is not loaded");
        }
    if (start < 0 || end > g.getAdjMatrix().size() - 1 || end < 0 || start > g.getAdjMatrix().size() - 1)
        return "Start or End vertices are invalid!";
    if (start == end)
        return "A path from a vertex to itself isn't defined!";
    if (g.isNegative())
        return bellmanFord(g, start, end);
    if (g.isSameWeight())
        return BFS(g, start, end);
    return dijkstra(g, start, end);
}

/**
 * @brief This function finds A negative cycle in the graph if exists
 * the function uses the Bellman-Ford algorithm to find the shortest path from a source vertex to all other vertices.
 *  by adding a vertex with weight 0 to all other vertices, and then running the Bellman-Ford algorithm, we can get to any negative cycle in the graph, if exists;
 * I used the wiki page https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm to implement the algorithm
 * @param g the graph
 * @return the negative cycle if exists, otherwise return "There is no negative cycle in the graph"
 */
string ariel::Algorithms::negativeCycle(ariel::Graph g){
 if(!g.isLoaded()){
            throw invalid_argument("The graph is not loaded");
        }

    if (!g.isNegative())
        return "There is no negative cycle in the graph";
    vector<vector<int>> adjMatrixCopy = g.getAdjMatrix();
    vector<vector<int>> adjMatrix(adjMatrixCopy.size() + 1, vector<int>(adjMatrixCopy.size() + 1, 0)); // initalize a new matrix with the same values as the original matrix, but with a source vector that connected to each vertex with weight 0
    for (size_t i = 0; i < adjMatrix.size(); i++)
    {
        adjMatrix[0][i] = 0;
        adjMatrix[i][0] = INT_MAX;
    }
    for (size_t i = 1; i < adjMatrix.size(); i++)
    {
        for (size_t j = 1; j < adjMatrix.size(); j++)
        {
            if (adjMatrixCopy[i - 1][j - 1] != 0)
                adjMatrix[i][j] = adjMatrixCopy[i - 1][j - 1];
            else
                adjMatrix[i][j] = INT_MAX;
        }
    }

    vector<int> distance(adjMatrix.size(), INT_MAX); // initialize the distance vector with infinity
    vector<int> parent(adjMatrix.size(), -1);        // initialize the parent vector with -1
    distance[0] = 0;                                 // set the distance of the source vertex to 0
    for (size_t i = 0; i <= adjMatrix.size() - 2; i++)
    { // run the loop n-1 times, where n is the number of vertices, including the new source vertex, each time relax all the edges
        for (size_t j = 0; j < adjMatrix.size(); j++)
        {
            for (size_t k = 0; k < adjMatrix.size(); k++)
            {
                if (!g.isDirected())
                {
                    if (adjMatrix[j][k] != INT_MAX && distance[(size_t)j] != INT_MAX && parent[j] != k && distance[(size_t)j] + adjMatrix[(size_t)j][(size_t)k] < distance[(size_t)k])
                    { // if the graph isn't directed, we cannot go back to the parent
                        distance[(size_t)k] = distance[(size_t)j] + adjMatrix[(size_t)j][(size_t)k];
                        parent[(size_t)k] = j;
                    }
                }
                if (g.isDirected())
                {
                    if (adjMatrix[j][k] != INT_MAX && distance[(size_t)j] != INT_MAX && distance[(size_t)j] + adjMatrix[(size_t)j][(size_t)k] < distance[(size_t)k])
                    { // else, we allow going back to the parent
                        distance[(size_t)k] = distance[(size_t)j] + adjMatrix[(size_t)j][(size_t)k];
                        parent[(size_t)k] = j;
                    }
                }
            }
        }
    }
    for (size_t j = 0; j < adjMatrix.size(); j++)
    { // run the loop one more time, if we can still relax one of the edges, then there is a negative cycle
        for (size_t k = 0; k < adjMatrix.size(); k++)
        {
            if (!g.isDirected() && parent[j] != k && adjMatrix[j][k] != INT_MAX && distance[j] != INT_MAX && distance[j] + adjMatrix[j][k] < distance[k]) //if the graph isn't directed, we cannot go back to the parent, thats the undirected case
            { // if we can relax the edge
                string cycle;
                distance[k] = distance[j] + adjMatrix[j][k]; // update the distance and the parent vectors
                parent[k] = j;
                vector<bool> visited(adjMatrixCopy.size() + 1, false); // initialize the visited vector with false
                int u = j;                                             // start from u, mark all the vertices of the cycle as visited
                visited[k] = true;
                while (!visited[(size_t)u])
                {
                    visited[(size_t)u] = true;
                    u = parent[(size_t)u];
                }
                cycle = to_string(u - 1); // create the string representation of the cycle
                int v = parent[(size_t)u];
                while (v != u)
                { // go through the parent vector and create the string representation of the cycle
                    cycle = to_string(v - 1) + "->" + cycle;
                    v = parent[(size_t)v];
                }
                cycle = to_string(u - 1) + "->" + cycle; // add the end of the cycle and return it
                return cycle;
            }

            if (g.isDirected() && adjMatrix[j][k] != INT_MAX && distance[j] != INT_MAX && distance[j] + adjMatrix[j][k] < distance[k])//else, we allow going back to the parent, thats the directed case
            { // if we can relax the edge
                string cycle;
                distance[k] = distance[j] + adjMatrix[j][k]; // update the distance and the parent vectors
                parent[k] = j;
                vector<bool> visited(adjMatrixCopy.size() + 1, false); // initialize the visited vector with false
                int u = j;                                             // start from u, mark all the vertices of the cycle as visited
                visited[k] = true;
                while (!visited[(size_t)u])
                {
                    visited[(size_t)u] = true;
                    u = parent[(size_t)u];
                }
                cycle = to_string(u - 1); // create the string representation of the cycle
                int v = parent[(size_t)u];
                while (v != u)
                { // go through the parent vector and create the string representation of the cycle
                    cycle = to_string(v - 1) + "->" + cycle;
                    v = parent[(size_t)v];
                }
                cycle = to_string(u - 1) + "->" + cycle; // add the end of the cycle and return it
                return cycle;
            }
        }
    }

    return "There is no negative cycle in the graph";
}
