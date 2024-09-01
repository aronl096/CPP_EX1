#include "Algorithms.hpp"
#include <list>

#define true 1
#define false 0
#define INT_MAX 999

using namespace std;
using namespace ariel;

/* 
 *  Determines if a graph is connected using BFS (Breadth-First Search).
 *  The BFS algorithm explores the graph starting from a specific vertex and ensures 
 *  all vertices are reachable from this starting point. A connected graph means all 
 *  vertices are reachable from any other vertex.
 * 
 *  @param g The graph to be checked.
 *  @return 1 if the graph is connected, otherwise returns 0.
 */
int Algorithms::isConnected(const Graph &g) {
    size_t numVertices = g.graphSize();
    vector<int> visited(numVertices, 0);
    vector<vector<int>> adjacencyMatrix = g.getMatrix();

    list<size_t> queue;
    queue.push_back(0);  
    
    while (!queue.empty()) {
        size_t currentNode = queue.front();  
        queue.pop_front();  
        
        if (!visited[currentNode]) {
            visited[currentNode] = 1;  
            
            for (size_t i = 0; i < numVertices; ++i) {
                if (adjacencyMatrix[currentNode][i] != 0 && !visited[i]) {
                    queue.push_back(i);  
                }
            }
        }
    }
    
    for (int vertex : visited) {
        if (vertex == 0) {
            return false;  
        }
    }
    
    return true;  
}

/*
 *  Finds the shortest path between two nodes in a graph using BFS.
 *  This method tracks the shortest path and distance from the start node to the end node.
 *  It uses a BFS approach to explore the graph and determine the shortest path.
 *  
 *  @param g The graph to be processed.
 *  @param start The starting node.
 *  @param end The target node.
 *  @return A string representation of the shortest path if found, otherwise returns "-1".
 */
string Algorithms::shortestPath(const Graph &g, size_t start, size_t end) {
    size_t numVertices = g.graphSize();
    vector<size_t> previousNode(numVertices, (size_t)-1);
    vector<vector<int>> adjacencyMatrix = g.getMatrix();

    vector<int> shortestDistance(numVertices, -1);
    shortestDistance[start] = 0;

    list<size_t> queue;
    queue.push_front(start);

    while (!queue.empty()) {
        size_t currentNode = queue.front();
        queue.pop_front();

        for (size_t i = 0; i < numVertices; i++) {
            if (adjacencyMatrix[currentNode][i] != 0) {
                if (shortestDistance[i] == -1) {
                    shortestDistance[i] = shortestDistance[currentNode] + 1;
                    previousNode[i] = currentNode;
                    queue.push_front(i);
                }
            }
        }
    }

    string pathString;
    size_t current = end;

    if (previousNode[current] == (size_t)-1) {
        return "-1";
    }

    pathString = to_string(current);
    current = previousNode[current];

    while (current != (size_t)-1) {
        pathString = to_string(current) + "->" + pathString;
        current = previousNode[current];
    }

    return pathString;
}

/**
 *  Detects if there is a cycle in the graph using DFS (Depth-First Search).
 *  This function traverses the graph using DFS and checks for cycles by examining if
 *  a visited node is reached again through an edge that is not its direct parent.
 * 
 *  @param g The graph to be checked.
 *  @return 1 if a cycle is found, otherwise returns 0.
 */
int Algorithms::isContainsCycle(const Graph &g) { 
    size_t numVertices = g.graphSize();
    vector<vector<int>> adjacencyMatrix = g.getMatrix();

    vector<bool> visited(numVertices, false); 
    vector<size_t> parent(numVertices, (size_t)-1); 

    for (size_t i = 0; i < numVertices; ++i) {
        if (!visited[i]) {
            list<size_t> stack;
            stack.push_back(i);
            
            while (!stack.empty()) {
                size_t currentNode = stack.back();
                stack.pop_back();

                if (!visited[currentNode]) {
                    visited[currentNode] = true;
                    for (size_t j = 0; j < numVertices; ++j) {
                        if (adjacencyMatrix[currentNode][j] != 0) { 
                            if (!visited[j]) {
                                stack.push_back(j);
                                parent[j] = currentNode;
                            } else if (parent[currentNode] != j) {
                                return true; 
                            }
                        }
                    }
                }
            }
        }
    }

    return false; 
}

/**
 *  Determines if a graph is bipartite using BFS.
 *  The function attempts to color the graph using two colors in such a way that 
 *  no two adjacent nodes have the same color. It uses BFS to attempt this coloring.
 * 
 *  @param g The graph to be checked.
 *  @return A string indicating if the graph is bipartite and listing the two sets of nodes.
 *  Returns "0" if the graph is not bipartite.
 */
string Algorithms::isBipartite(const Graph &g) {
    size_t numVertices = g.graphSize();
    vector<vector<int>> adjacencyMatrix = g.getMatrix();
    
    vector<int> color(numVertices, -1);
    color[0] = 0; 

    list<size_t> queue;
    queue.push_back(0);

    while (!queue.empty()) {
        size_t currentNode = queue.front();
        queue.pop_front();

        for (size_t i = 0; i < numVertices; ++i) {
            if (adjacencyMatrix[currentNode][i] != 0) { 
                if (color[i] == -1) { 
                    color[i] = 1 - color[currentNode];
                    queue.push_back(i);
                } else if (color[i] == color[currentNode]) {
                    return "0"; 
                }
            }
        }
    }

    vector<int> group1, group2;

    for (size_t i = 0; i < numVertices; ++i) {
        if (color[i] == 0) {
            group1.push_back(i);
        } else {
            group2.push_back(i);
        }
    }

    string result = "The graph is bipartite: A={";

    for (size_t i = 0; i < group1.size(); ++i) {
        result += to_string(group1[i]);
        if (i != group1.size() - 1) {
            result += ", ";
        }
    }

    result += "}, B={";

    for (size_t i = 0; i < group2.size(); ++i) {
        result += to_string(group2[i]);
        if (i != group2.size() - 1) {
            result += ", ";
        }
    }

    result += "}";
    return result;
}

/**
 *  Detects the presence of a negative weight cycle using the Bellman-Ford algorithm.
 *  This function first checks for any cycle in the graph using isContainsCycle, 
 *  and then applies the Bellman-Ford algorithm to detect negative weight cycles.
 * 
 *  @param g The graph to be checked.
 *  @return A string indicating the presence of a negative weight cycle, or "0" if no cycle is found.
 */
string Algorithms::negativeCycle(const Graph &g) {
    if (!isContainsCycle(g)) {
        return "0";
    }

    size_t numVertices = g.graphSize();
    vector<vector<int>> adjacencyMatrix = g.getMatrix();

    vector<int> distance(numVertices, -1); 
    distance[0] = 0; 

    for (size_t i = 0; i < numVertices - 1; ++i) {
        for (size_t j = 0; j < numVertices; ++j) {
            for (size_t k = 0; k < numVertices; ++k) {
                if (adjacencyMatrix[j][k] != 0) {
                    if (distance[j] != -1 && distance[j] + adjacencyMatrix[j][k] < distance[k]) {
                        distance[k] = distance[j] + adjacencyMatrix[j][k];
                    }
                }
            }
        }
    }

    for (size_t j = 0; j < numVertices; ++j) {
        for (size_t k = 0; k < numVertices; ++k) {
            if (adjacencyMatrix[j][k] != 0) {
                if (distance[j] != -1 && distance[j] + adjacencyMatrix[j][k] < distance[k]) {
                    return "Negative cycle: " + to_string(distance[j]);
                }
            }
        }
    }

    return "0"; 
}
