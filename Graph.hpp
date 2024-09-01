#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <ostream>
#include <iostream>
#include <vector>
#include <string>

namespace ariel {

    class Graph {
        private:
            std::vector<std::vector<int>> matrix;
            bool checkValid(const Graph &secGraph) const;

        public:
            Graph();  // Default constructor
            Graph(const std::vector<std::vector<int>> &matrix); 
            ~Graph() = default;
            void loadGraph(const std::vector<std::vector<int>> &matrix);
            void printGraph() const;

            const std::vector<std::vector<int>>& getMatrix() const;

            size_t graphSize() const;
            size_t countEdges() const;

            // Operator overloads
            Graph operator+() const;
            Graph operator+(const Graph &secGraph) const;

            Graph &operator++();
            Graph operator++(int);

            Graph operator+=(const Graph &secGraph);
            Graph &operator+=(int scalar);

            Graph operator-() const;
            Graph operator-(const Graph &secGraph) const;

            Graph &operator--();
            Graph operator--(int);

            Graph operator-=(const Graph &secGraph);
            Graph &operator-=(int scalar);

            Graph operator*(const Graph &secGraph) const;
            Graph operator*(int scalar) const;

            Graph &operator*=(int scalar); 
            Graph &operator/=(int scalar); 

            bool operator==(const Graph &secGraph) const;
            bool operator!=(const Graph &secGraph) const;

            bool operator<(const Graph &secGraph) const;
            bool operator>(const Graph &secGraph) const;
            
            bool operator<=(const Graph &secGraph) const;
            bool operator>=(const Graph &secGraph) const;

            // Friend function for the stream insertion operator
            friend std::ostream& operator<<(std::ostream &out, const Graph &g);
    };
}

#endif // GRAPH_HPP
