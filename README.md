# Graph Algorithms (Classes and Namespaces)

This project involves creating a class representing a graph and implementing various algorithms on the graphs.

### Graph.cpp

Contains the `Graph` class that represents a graph. The class includes the following methods:

- `loadGraph`: Accepts an adjacency matrix and loads it into the graph.
- `printGraph`: Prints the graph representation (format of your choice).

### Algorithms.cpp

Contains implementations of graph algorithms. The algorithms include:

- `isConnected(g)`: Receives a graph and returns `1` if the graph is connected (otherwise returns `0`).
- `shortestPath(g, start, end)`: Receives a graph, a start vertex, and an end vertex, and returns the shortest path between the two vertices. If there is no such path, returns `-1`.
- `isContainsCycle(g)`: Receives a graph and prints any cycle found. If no cycle exists, returns `0`.
- `isBipartite(g)`: Receives a graph and returns the bipartite division of the graph. If the graph cannot be divided, returns `0`.
- `negativeCycle(g)`: Receives a graph and finds a negative cycle (i.e., a cycle with a negative sum of edge weights). If no such cycle exists, prints that no negative cycle exists.

### Demo.cpp

Contains examples of inputs and outputs.

### Code Example

Here is a small example of how to use the classes and algorithms:

```cpp
#include "Graph.hpp"
#include "Algorithms.hpp"
#include <iostream>

int main() {
    ariel::Graph graph;
    std::vector<std::vector<int>> matrix = {
        {0, 1, 0, 0, 0},
        {1, 0, 1, 1, 0},
        {0, 1, 0, 1, 1},
        {0, 1, 1, 0, 1},
        {0, 0, 1, 1, 0}
    };

    graph.loadGraph(matrix);
    graph.printGraph();

    if (ariel::Algorithms::isConnected(graph)) {
        std::cout << "The graph is connected." << std::endl;
    } else {
        std::cout << "The graph is not connected." << std::endl;
    }

    std::string path = ariel::Algorithms::shortestPath(graph, 0, 4);
    std::cout << "Shortest path from 0 to 4: " << path << std::endl;

    if (ariel::Algorithms::isContainsCycle(graph)) {
        std::cout << "The graph contains a cycle." << std::endl;
    } else {
        std::cout << "The graph does not contain a cycle." << std::endl;
    }

    std::string bipartite = ariel::Algorithms::isBipartite(graph);
    std::cout << "Bipartite sets: " << bipartite << std::endl;

    ariel::Algorithms::negativeCycle(graph);

    return 0;
}