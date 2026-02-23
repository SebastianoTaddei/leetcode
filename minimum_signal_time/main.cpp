/*
You are given a network of n nodes, labeled from 1 to n. You are also given
times, a list of travel times as directed edges-times [i] = (ui, vi, wi), where
ui is the source node, vi is the target node, and wi is the time it takes for a
signal to travel from source to target.

We will send a signal from a given node k. Return the minimum time it takes for
all the n nodes to receive the signal. If it is impossible for all the n nodes
to receive the signal, return -1.

Example 1:
  Input: times = [[2, 1, 1], [2, 3, 1], [3, 4, 1]], n = 4, k = 2
  Output: 2

Example 2:
  Input: times = [[1, 2, 1]], n = 2, k = 1
  Output: 1

Example 3:
Input: times = [[1, 2, 1]], n = 2, k = 2
Output: -1
*/

#include <array>
#include <functional>
#include <iostream>
#include <machine/limits.h>
#include <queue>
#include <vector>

struct Edge
{
  size_t dst;
  size_t cost;
};

using priority_queue = std::priority_queue<
  std::pair<size_t, size_t>,
  std::vector<std::pair<size_t, size_t>>,
  std::greater<std::pair<size_t, size_t>>>;
using triplet = std::array<size_t, 3>;
using Nodes   = std::vector<bool>;
using Graph   = std::vector<std::vector<Edge>>;

Graph create_graph(std::vector<triplet> const &relations, size_t n_nodes)
{
  Graph graph(n_nodes);

  for (auto const &relation : relations)
  {
    graph[relation.at(0) - 1].push_back({.dst = relation.at(1) - 1, .cost = relation.at(2)});
  }

  return graph;
}

Nodes make_nodes(size_t n_nodes) { return Nodes(n_nodes, false); }

int dijkstra(Graph const &graph, size_t root_node)
{
  root_node -= 1;

  auto const n_nodes = graph.size();
  Nodes nodes        = make_nodes(n_nodes);
  std::vector<size_t> dist(n_nodes, SIZE_T_MAX);
  priority_queue queue{};

  dist.at(root_node) = 0;
  queue.push({0, root_node});

  while (not queue.empty())
  {
    auto const [cost, node] = queue.top();
    queue.pop();

    if (nodes.at(node))
    {
      continue;
    }
    nodes.at(node) = true;

    for (auto const &edge : graph.at(node))
    {
      auto const next_cost = cost + edge.cost;
      if (next_cost < dist.at(edge.dst))
      {
        dist.at(edge.dst) = next_cost;
        queue.push({next_cost, edge.dst});
      }
    }
  }

  size_t max_dist{0};
  for (auto const &cost : dist)
  {
    max_dist = std::max(cost, max_dist);
  }

  return max_dist == SIZE_T_MAX ? -1 : max_dist;
}

int main()
{
  {
    // Example 1
    std::vector<triplet> relations = {
      {2, 1, 1},
      {2, 3, 1},
      {3, 4, 1},
    };
    size_t n = 4;
    size_t k = 2;

    auto const graph = create_graph(relations, n);

    std::cout << "Example 1: " << dijkstra(graph, k) << '\n';
  }

  {
    // Example 2
    std::vector<triplet> relations = {
      {1, 2, 1},
    };
    size_t n = 2;
    size_t k = 1;

    auto const graph = create_graph(relations, n);

    std::cout << "Example 2: " << dijkstra(graph, k) << '\n';
  }

  {
    // Example 3
    std::vector<triplet> relations = {
      {1, 2, 1},
    };
    size_t n = 2;
    size_t k = 2;

    auto const graph = create_graph(relations, n);

    std::cout << "Example 3: " << dijkstra(graph, k) << '\n';
  }
}
