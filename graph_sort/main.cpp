/*
Just different ways to sort a graph:

- Topological sort (topo):
*/

#include <iostream>
#include <stack>
#include <utility>
#include <vector>

using Relations = std::vector<std::pair<size_t, size_t>>;
using Graph     = std::vector<std::vector<size_t>>;

Graph make_graph(Relations const &relations, size_t n_nodes)
{
  Graph graph(n_nodes);

  for (auto const &relation : relations)
  {
    graph.at(relation.first - 1).push_back(relation.second - 1);
  }

  return graph;
}

void dfs(Graph const &graph, std::vector<bool> &visited, std::stack<size_t> &sorted, size_t node)
{
  if (visited.at(node))
  {
    return;
  }
  visited.at(node) = true;

  for (auto const &dst : graph.at(node))
  {
    dfs(graph, visited, sorted, dst);
  }

  sorted.push(node);
}

std::vector<size_t> toposort(Graph const &graph)
{
  std::vector<bool> visited(graph.size(), false);
  std::stack<size_t> sorted{};

  for (size_t i{0}; i < graph.size(); i++)
  {
    dfs(graph, visited, sorted, i);
  }

  std::vector<size_t> sorted_vec;
  sorted_vec.reserve(graph.size());
  while (not sorted.empty())
  {
    sorted_vec.push_back(sorted.top());
    sorted.pop();
  }

  return sorted_vec;
}

int main()
{
  { // Example 1
    Relations relations{
      {1, 2},
      {1, 3},
      {1, 5},
      {2, 4},
      {3, 5},
    };
    size_t n_nodes{5};

    auto const graph  = make_graph(relations, n_nodes);
    auto const sorted = toposort(graph);

    std::cout << "Example 1: [";
    for (auto const &elem : sorted)
    {
      std::cout << elem + 1 << ", ";
    }
    std::cout << "]\n";
  }
}
