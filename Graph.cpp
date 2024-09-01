#include "Graph.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <ostream>
#include <string>

namespace ariel {

// Default constructor
Graph::Graph() {}

// Constructor initializing graph from adjacency matrix
Graph::Graph(const std::vector<std::vector<int>> &matrix) {
    this->loadGraph(matrix);
}

// Load graph data from an adjacency matrix
void Graph::loadGraph(const std::vector<std::vector<int>> &adjMatrix) {
    size_t size = adjMatrix.size();
    for (const auto &row : adjMatrix) {
        if (row.size() != size) {
            throw std::invalid_argument("Invalid graph: The matrix is not square.");
        }
    }
    this->matrix = adjMatrix;
}

// Print the graph information
void Graph::printGraph() const {
    size_t size = graphSize();
    size_t edges = countEdges();
    std::cout << "Graph with " << size << " vertices and " << edges << " edges." << std::endl;
}

// Get the adjacency matrix of the graph
const std::vector<std::vector<int>> &Graph::getMatrix() const {
    return this->matrix;
}

// Get the number of vertices in the graph
size_t Graph::graphSize() const {
    return this->matrix.size();
}

// Count the number of edges in the graph
size_t Graph::countEdges() const {
    size_t count = 0;
    size_t size = this->graphSize();

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            if (this->matrix[i][j] != 0) {
                count++;
            }
        }
    }
    return count;
}

// Check if two graphs are compatible in size
bool Graph::checkValid(const Graph &secGraph) const {
    if (this->matrix.size() != secGraph.getMatrix().size()) {
        throw std::invalid_argument("Graphs must have the same dimensions.");
    }
    return true;
}

// Initialize a result matrix with zeros
std::vector<std::vector<int>> initializeResultMatrix(size_t size) {
    return std::vector<std::vector<int>>(size, std::vector<int>(size, 0));
}

// Unary plus operator (returns a copy of the graph)
Graph Graph::operator+() const {
    return *this;
}

// Addition operator for combining two graphs
Graph Graph::operator+(const Graph &secGraph) const {
    checkValid(secGraph);

    std::vector<std::vector<int>> result = initializeResultMatrix(this->matrix.size());

    for (size_t i = 0; i < this->matrix.size(); ++i) {
        for (size_t j = 0; j < this->matrix.size(); ++j) {
            result[i][j] = this->matrix[i][j] + secGraph.matrix[i][j];
        }
    }

    Graph newGraph;
    newGraph.loadGraph(result);
    return newGraph;
}

// Prefix increment operator (increments all elements by 1)
Graph &Graph::operator++() {
    size_t size = this->graphSize();
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            this->matrix[i][j]++;
        }
    }
    return *this;
}

// Postfix increment operator (increments all elements by 1, returns the old value)
Graph Graph::operator++(int) {
    Graph oldGraph = *this;
    ++(*this);
    return oldGraph;
}

// Addition assignment operator for combining two graphs
Graph Graph::operator+=(const Graph &secGraph) {
    checkValid(secGraph);

    size_t size = this->matrix.size();
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            this->matrix[i][j] += secGraph.matrix[i][j];
        }
    }
    return *this;
}

// Addition assignment operator for a graph and a scalar
Graph &Graph::operator+=(int scalar) {
    size_t size = this->graphSize();
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            this->matrix[i][j] += scalar;
        }
    }
    return *this;
}

// Unary minus operator (returns a graph with all elements negated)
Graph Graph::operator-() const {
    return *this * (-1);
}

// Subtraction operator for subtracting one graph from another
Graph Graph::operator-(const Graph &secGraph) const {
    checkValid(secGraph);

    std::vector<std::vector<int>> result = initializeResultMatrix(this->matrix.size());

    for (size_t i = 0; i < this->matrix.size(); ++i) {
        for (size_t j = 0; j < this->matrix.size(); ++j) {
            result[i][j] = this->matrix[i][j] - secGraph.matrix[i][j];
        }
    }

    Graph newGraph;
    newGraph.loadGraph(result);
    return newGraph;
}

// Prefix decrement operator (decrements all elements by 1)
Graph &Graph::operator--() {
    size_t size = this->graphSize();
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            this->matrix[i][j]--;
        }
    }
    return *this;
}

// Postfix decrement operator (decrements all elements by 1, returns the old value)
Graph Graph::operator--(int) {
    Graph oldGraph = *this;
    --(*this);
    return oldGraph;
}

// Subtraction assignment operator for subtracting one graph from another
Graph Graph::operator-=(const Graph &secGraph) {
    checkValid(secGraph);

    size_t size = this->matrix.size();
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            this->matrix[i][j] -= secGraph.matrix[i][j];
        }
    }
    return *this;
}

// Subtraction assignment operator for a graph and a scalar
Graph &Graph::operator-=(int scalar) {
    size_t size = this->graphSize();
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            this->matrix[i][j] -= scalar;
        }
    }
    return *this;
}

// Element-wise multiplication of two graphs
Graph Graph::operator*(const Graph &secGraph) const {
    if (this->graphSize() != secGraph.graphSize()) {
        throw std::invalid_argument("Incompatible dimensions for matrix multiplication.");
    }

    size_t size = this->graphSize();
    std::vector<std::vector<int>> result(size, std::vector<int>(size, 0));

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            for (size_t k = 0; k < size; ++k) {
                result[i][j] += this->matrix[i][k] * secGraph.matrix[k][j];
            }
        }
    }

    // Set diagonal elements to zero
    for (size_t i = 0; i < size; ++i) {
        result[i][i] = 0;
    }

    Graph newGraph;
    newGraph.loadGraph(result);
    return newGraph;
}

// Scalar multiplication of the graph
Graph Graph::operator*(int scalar) const {
    size_t size = this->graphSize();
    std::vector<std::vector<int>> result = initializeResultMatrix(size);

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            result[i][j] = this->matrix[i][j] * scalar;
        }
    }

    Graph newGraph;
    newGraph.loadGraph(result);
    return newGraph;
}

// Scalar multiplication assignment operator
Graph &Graph::operator*=(int scalar) {
    size_t size = this->graphSize();
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            this->matrix[i][j] *= scalar;
        }
    }
    return *this;
}

// Scalar division assignment operator
Graph &Graph::operator/=(int scalar) {
    if (scalar == 0) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }

    size_t size = this->graphSize();
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            this->matrix[i][j] /= scalar;
        }
    }
    return *this;
}

// Equality comparison operator
bool Graph::operator==(const Graph &secGraph) const {
    return this->matrix == secGraph.matrix;
}

// Inequality comparison operator
bool Graph::operator!=(const Graph &secGraph) const {
    return !(*this == secGraph);
}

// Less than operator based on edge count
bool Graph::operator<(const Graph &secGraph) const {
    return this->countEdges() < secGraph.countEdges();
}

// Greater than operator based on edge count
bool Graph::operator>(const Graph &secGraph) const {
    return secGraph < *this;
}

// Less than or equal operator based on edge count
bool Graph::operator<=(const Graph &secGraph) const {
    return !(*this > secGraph);
}

// Greater than or equal operator based on edge count
bool Graph::operator>=(const Graph &secGraph) const {
    return !(*this < secGraph);
}

// Stream insertion operator for displaying graph
std::ostream &operator<<(std::ostream &out, const Graph &g) {
    const auto &matrix = g.getMatrix();
    size_t size = matrix.size();

    for (size_t i = 0; i < size; ++i) {
        out << "[";
        for (size_t j = 0; j < size; ++j) {
            out << matrix[i][j];
            if (j < size - 1) {
                out << ", ";
            }
        }
        out << "]";
        if (i < size - 1) {
            out << ", ";
        }
    }
    out << std::endl;
    return out;
}

} // namespace ariel
