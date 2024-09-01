# Graph Algorithms (Classes and Namespaces)

This project provides a C++ implementation of a `Graph` class and various algorithms for graph analysis. The `Graph` class represents a graph using an adjacency matrix, and the algorithms perform different operations such as connectivity checks, shortest path calculations, and cycle detection.

## Files

### `Graph.cpp`

Contains the implementation of the `Graph` class, which includes:

- **`Graph()`**: Default constructor.
- **`Graph(const std::vector<std::vector<int>> &matrix)`**: Constructor that initializes the graph with an adjacency matrix.
- **`void loadGraph(const std::vector<std::vector<int>> &adjMatrix)`**: Loads an adjacency matrix into the graph.
- **`void printGraph() const`**: Prints the graph in a readable format.
- **`const std::vector<std::vector<int>> &getMatrix() const`**: Returns the adjacency matrix of the graph.
- **`size_t graphSize() const`**: Returns the size (number of vertices) of the graph.
- **`size_t countEdges() const`**: Returns the number of edges in the graph.
- **`bool checkValid(const Graph &secGraph) const`**: Checks if another graph has the same size.
- **`Graph operator+(const Graph &secGraph) const`**: Adds two graphs.
- **`Graph operator-(const Graph &secGraph) const`**: Subtracts one graph from another.
- **`Graph operator*(const Graph &secGraph) const`**: Multiplies two graphs.
- **`Graph operator*(int scalar) const`**: Multiplies the graph by a scalar.
- **`bool operator==(const Graph &secGraph) const`**: Compares two graphs for equality.
- **`bool operator!=(const Graph &secGraph) const`**: Compares two graphs for inequality.
- **`bool operator<(const Graph &secGraph) const`**: Compares two graphs based on the number of edges.
- **`bool operator>(const Graph &secGraph) const`**: Compares two graphs based on the number of edges.
- **`std::ostream &operator<<(std::ostream &out, const Graph &g)`**: Outputs the graph to a stream.

### `Algorithms.cpp`

Contains the implementation of various graph algorithms:

- **`int isConnected(const Graph &g)`**: Checks if the graph is connected and returns `1` if true, `0` otherwise.
- **`std::string shortestPath(const Graph &g, int start, int end)`**: Finds the shortest path between two vertices.
- **`int isContainsCycle(const Graph &g)`**: Checks if the graph contains a cycle and prints any cycle found.
- **`int isBipartite(const Graph &g)`**: Checks if the graph is bipartite and returns the bipartite division if possible.
- **`void negativeCycle(const Graph &g)`**: Finds a negative cycle in the graph, if one exists.

### `Demo.cpp`

Provides examples of how to use the `Graph` class and the algorithms. It includes sample input matrices and demonstrates the functionality of various methods and algorithms.

## Code Example

Here is a small example demonstrating how to use the `Graph` class and the provided algorithms:

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

    return 0;
}
