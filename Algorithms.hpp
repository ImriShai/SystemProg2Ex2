/** A header file for the Algorithms */
#include <string>
#include <vector>
#include <queue>
#include <limits.h>
#include "Graph.hpp"
namespace ariel{
class Algorithms{
    public:
      static bool isConnected(const Graph& g);
     static string shortestPath(const Graph& g, int start, int end);
     static string isContainsCycle(const Graph& g);
    static string isBipartite(const Graph& g);
     static string negativeCycle(const Graph& g);
};
}