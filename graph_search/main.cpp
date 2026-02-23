/*
Just different ways to traverse a graph:

- Depth-First-Search Recursive (dfs_recursive): recursion-based traversal with O(V+E) complexity
- Depth-First-Search (dfs): stack-based traversal with O(V+E) complexity
- Breadth-First-Search (bfs): queue-based traversal with O(V+E) complexity
- Dijkstra (dij): minimum distance between two nodes in a weighted graph with O(E+V*log(V))
complexity
*/

#include <array>
#include <cstddef>
#include <iostream>
#include <machine/limits.h>
#include <queue>
#include <stack>
#include <vector>

struct Edge
{
  size_t dst;
  size_t cost;
};

struct Node
{
  size_t id;
  bool discovered;

  void found()
  {
    this->discovered = true;
    std::cout << this->id;
  }
};

using priority_queue = std::priority_queue<
  std::pair<size_t, size_t>,
  std::vector<std::pair<size_t, size_t>>,
  std::greater<std::pair<size_t, size_t>>>;
using triplet        = std::array<size_t, 3>;
using Nodes          = std::vector<Node>;
using AdjacencyEdges = std::vector<Edge>;
using Graph          = std::vector<AdjacencyEdges>;

template <typename T>
void print_vec(std::vector<T> const &vec)
{
  std::cout << "[";
  for (auto const &elem : vec)
  {
    std::cout << elem << ", ";
  }
  std::cout << "]\n";
}

Graph make_graph(std::vector<triplet> const &relations, size_t n_nodes)
{
  Graph graph(n_nodes);
  for (auto const &relation : relations)
  {
    graph.at(relation.at(0) - 1).push_back({.dst = relation.at(1) - 1, .cost = relation.at(2)});
  }

  return graph;
}

Nodes make_nodes(size_t n_nodes)
{
  Nodes nodes{};
  for (size_t i{1}; i <= n_nodes; i++)
  {
    nodes.push_back({i, false});
  }
  return nodes;
}

void dfs_recursive(Graph const &graph, Nodes &nodes, size_t node)
{
  if (nodes.at(node).discovered)
  {
    return;
  }
  nodes.at(node).found();

  for (auto const &edge : graph.at(node))
  {
    dfs_recursive(graph, nodes, edge.dst);
  }
}

void dfs(Graph const &graph, Nodes &nodes, size_t node)
{
  std::stack<size_t> stack{};

  stack.push(node);
  while (not stack.empty())
  {
    size_t const id = stack.top();
    stack.pop();

    if (nodes.at(id).discovered)
    {
      continue;
    }
    nodes.at(id).found();

    for (auto const &edge : graph.at(id))
    {
      stack.push(edge.dst);
    }
  }
}

void bfs(Graph const &graph, Nodes &nodes, size_t node)
{
  std::queue<size_t> queue{};

  queue.push(node);
  nodes.at(node).found();
  while (not queue.empty())
  {
    size_t const id = queue.front();
    queue.pop();

    for (auto const &edge : graph.at(id))
    {
      auto const dst = edge.dst;
      if (not nodes.at(dst).discovered)
      {
        nodes.at(dst).found();
        queue.push(dst);
      }
    }
  }
}

void dij(Graph const &graph, Nodes &nodes, size_t node)
{
  priority_queue queue{};
  std::vector<size_t> dist(nodes.size(), SIZE_T_MAX);

  dist.at(node) = 0;
  queue.push({0, node});
  while (not queue.empty())
  {
    auto const [cost, id] = queue.top();
    queue.pop();

    if (nodes.at(id).discovered)
    {
      continue;
    }
    nodes.at(id).found();

    for (auto const &edge : graph.at(id))
    {
      auto const alt = cost + edge.cost;
      if (alt < dist.at(edge.dst))
      {
        dist.at(edge.dst) = alt;
        queue.push({alt, edge.dst});
      }
    }
  }

  std::cout << "\ndist: ";
  print_vec(dist);
}

int main()
{
  std::vector<triplet> relations = {
    {2, 1, 1},
    {2, 3, 1},
    {3, 4, 1},
    {1, 5, 1},
    {4, 1, 1},
    {4, 3, 1},
  };
  size_t const n_nodes{5};
  size_t const start_node{1};

  auto const graph = make_graph(relations, n_nodes);

  {
    auto nodes = make_nodes(n_nodes);
    std::cout << "Depth-First-Search Recursive:\n";
    dfs_recursive(graph, nodes, start_node);
    std::cout << '\n';
  }
  {
    auto nodes = make_nodes(n_nodes);
    std::cout << "Depth-First-Search:\n";
    dfs(graph, nodes, start_node);
    std::cout << '\n';
  }
  {
    auto nodes = make_nodes(n_nodes);
    std::cout << "Breadth-First-Search:\n";
    bfs(graph, nodes, start_node);
    std::cout << '\n';
  }
  {
    auto nodes = make_nodes(n_nodes);
    std::cout << "Dijkstra:\n";
    dij(graph, nodes, start_node);
    std::cout << '\n';
  }
}
