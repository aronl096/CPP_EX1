
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <vector>
#include <iostream>
#include "Graph.hpp"

using namespace std;

namespace ariel{
    
    class Algorithms {
        public:
            static int isConnected(const Graph &g);

            static string shortestPath(const Graph &g, size_t start, size_t end);
            
            static int isContainsCycle(const Graph &g);
            
            static string isBipartite(const Graph &g);
            
            static string negativeCycle(const Graph &g);
    };
    
}
#endif //ALGORITHMS_HPP