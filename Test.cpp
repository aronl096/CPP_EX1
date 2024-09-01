#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;
using namespace ariel;


TEST_CASE("Test isConnected")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isConnected(g) == true);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(Algorithms::isConnected(g) == false);
}

TEST_CASE("Test shortestPath")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(Algorithms::shortestPath(g, 0, 4) == "-1");
}
TEST_CASE("Test isContainsCycle")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isContainsCycle(g) == false);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(Algorithms::isContainsCycle(g) == true);
}
TEST_CASE("Test isBipartite")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(Algorithms::isBipartite(g) == "0");

}
TEST_CASE("Test invalid graph")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));
}


TEST_CASE("Test isConnected with graph") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isConnected(g) == true);
}

TEST_CASE("Test isConnected with disconnected graph") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isConnected(g) == false);
}

TEST_CASE("Test shortestPath with direct path") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::shortestPath(g, 0, 2) == "0->1->2");
}

TEST_CASE("Test shortestPath with no path") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::shortestPath(g, 0, 2) == "-1");
}

TEST_CASE("Test isContainsCycle with no cycle") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isContainsCycle(g) == false);
}

TEST_CASE("Test isContainsCycle with cycle") {
    Graph g;

    vector<vector<int>> graph = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isContainsCycle(g) == 1); 
}

TEST_CASE("Test isBipartite with bipartite graph") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");
}

TEST_CASE("Test isBipartite with non-bipartite graph") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isBipartite(g) == "0");
}

TEST_CASE("Test addition of two graphs") {
    Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    g1.loadGraph(graph1);

    Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(graph2);

    Graph result = g1 + g2;
    vector<vector<int>> expected = {
        {0, 2, 3},
        {2, 0, 5},
        {3, 5, 0}};
    CHECK(result.getMatrix() == expected);
}

TEST_CASE("Test subtraction of two graphs") {
    Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2, 3},
        {2, 0, 5},
        {3, 5, 0}};
    g1.loadGraph(graph1);

    Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(graph2);

    Graph result = g1 - g2;
    vector<vector<int>> expected = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    CHECK(result.getMatrix() == expected);
}

TEST_CASE("Test multiplication of two graphs") {
    Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1},
        {1, 0}};
    g1.loadGraph(graph1);

    Graph g2;
    vector<vector<int>> graph2 = {
        {0, 2},
        {2, 0}};
    g2.loadGraph(graph2);

    Graph result = g1 * g2;
    vector<vector<int>> expected = {
        {0, 0},
        {0, 0}}; // Ensure this is the correct expected result

    auto resultMatrix = result.getMatrix();
    auto expectedMatrix = expected;

    for (size_t i = 0; i < resultMatrix.size(); ++i) {
        for (size_t j = 0; j < resultMatrix[i].size(); ++j) {
            CHECK(resultMatrix[i][j] == expectedMatrix[i][j]);
        }
    }
}

TEST_CASE("Test scalar multiplication") {
    Graph g;
    vector<vector<int>> graph = {
        {1, 2},
        {3, 4}};
    g.loadGraph(graph);

    Graph result = g * 2;
    vector<vector<int>> expected = {
        {2, 4},
        {6, 8}};
    CHECK(result.getMatrix() == expected);
}

TEST_CASE("Test scalar division") {
    Graph g;
    vector<vector<int>> graph = {
        {2, 4},
        {6, 8}};
    g.loadGraph(graph);

    Graph result = g /= 2;
    vector<vector<int>> expected = {
        {1, 2},
        {3, 4}};
    CHECK(result.getMatrix() == expected);
}

TEST_CASE("Test increment operator") {
    Graph g;
    vector<vector<int>> graph = {
        {1, 2},
        {3, 4}};
    g.loadGraph(graph);

    ++g;
    vector<vector<int>> expected = {
        {2, 3},
        {4, 5}};
    CHECK(g.getMatrix() == expected);
}

TEST_CASE("Test decrement operator") {
    Graph g;
    vector<vector<int>> graph = {
        {2, 3},
        {4, 5}};
    g.loadGraph(graph);

    --g;
    vector<vector<int>> expected = {
        {1, 2},
        {3, 4}};
    CHECK(g.getMatrix() == expected);
}

TEST_CASE("Test equality operator") {
    Graph g1;
    vector<vector<int>> graph1 = {
        {1, 2},
        {3, 4}};
    g1.loadGraph(graph1);

    Graph g2;
    vector<vector<int>> graph2 = {
        {1, 2},
        {3, 4}};
    g2.loadGraph(graph2);

    CHECK(g1 == g2);
}

TEST_CASE("Test inequality operator") {
    Graph g1;
    vector<vector<int>> graph1 = {
        {1, 2},
        {3, 4}};
    g1.loadGraph(graph1);

    Graph g2;
    vector<vector<int>> graph2 = {
        {1, 2},
        {3, 5}};
    g2.loadGraph(graph2);

    CHECK(g1 != g2);
}

TEST_CASE("Test less than operator") {
    Graph g1;
    vector<vector<int>> graph1 = {
        {1, 2},
        {3, 4}};
    g1.loadGraph(graph1);

    Graph g2;
    vector<vector<int>> graph2 = {
        {2, 3},
        {4, 5}};
    g2.loadGraph(graph2);

    CHECK(g1 < g2);
}

TEST_CASE("Test greater than operator") {
    Graph g1;
    vector<vector<int>> graph1 = {
        {2, 3},
        {4, 5}};
    g1.loadGraph(graph1);

    Graph g2;
    vector<vector<int>> graph2 = {
        {1, 2},
        {3, 4}};
    g2.loadGraph(graph2);

    CHECK(g1 > g2);
}

TEST_CASE("Test less than or equal to operator") {
    Graph g1;
    vector<vector<int>> graph1 = {
        {1, 2},
        {3, 4}};
    g1.loadGraph(graph1);

    Graph g2;
    vector<vector<int>> graph2 = {
        {1, 2},
        {3, 4}};
    g2.loadGraph(graph2);

    CHECK(g1 <= g2);
}

TEST_CASE("Test greater than or equal to operator") {
    Graph g1;
    vector<vector<int>> graph1 = {
        {2, 3},
        {4, 5}};
    g1.loadGraph(graph1);

    Graph g2;
    vector<vector<int>> graph2 = {
        {1, 2},
        {3, 4}};
    g2.loadGraph(graph2);

    CHECK(g1 >= g2);
}

TEST_CASE("Test invalid graph with non-square matrix") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1},
        {1, 0},
        {0, 1}};
    CHECK_THROWS(g.loadGraph(graph));
}