/*
Just an example of how to detect cycles in directed/undirected graphs.
*/

#include <iostream>
#include <utility>
#include <vector>

using Relation = std::pair<int, int>;
using Graph    = std::vector<std::vector<int>>;

Graph make_graph(std::vector<Relation> const &edges, size_t const size, bool const undirected)
{
  Graph graph(size);

  for (auto const &edge : edges)
  {
    auto const [from, to] = edge;

    graph.at(from).push_back(to);
    if (undirected)
    {
      graph.at(to).push_back(from);
    }
  }

  return graph;
}

bool dfs_directed(Graph const &graph, std::vector<bool> &visited, std::vector<bool> &rec_stack, int const node)
{
  visited.at(node)   = true;
  rec_stack.at(node) = true;

  for (auto const &neighbor : graph.at(node))
  {
    if (not visited.at(neighbor))
    {
      if (dfs_directed(graph, visited, rec_stack, neighbor))
      {
        return true;
      }
    }
    else if (rec_stack.at(neighbor))
    {
      return true;
    }
  }

  rec_stack.at(node) = false;
  return false;
}

bool has_cycle_directed(Graph const &graph)
{
  auto const size = static_cast<int>(graph.size());
  std::vector<bool> visited(size, false);
  std::vector<bool> rec_stack(size, false);

  for (int i{0}; i < size; i++)
  {
    if (not visited.at(i))
    {
      if (dfs_directed(graph, visited, rec_stack, i))
      {
        return true;
      }
    }
  }

  return false;
}

bool dfs_undirected(Graph const &graph, std::vector<bool> &visited, int const node, int const parent)
{
  visited.at(node) = true;

  for (auto const &neighbor : graph.at(node))
  {
    if (not visited.at(neighbor))
    {
      if (dfs_undirected(graph, visited, neighbor, node))
      {
        return true;
      }
    }
    else if (parent != neighbor)
    {
      return true;
    }
  }

  return false;
}

bool has_cycle_undirected(Graph const &graph)
{
  auto const size = static_cast<int>(graph.size());
  std::vector<bool> visited(size, false);

  for (int i{0}; i < size; i++)
  {
    if (not visited.at(i))
    {
      if (dfs_undirected(graph, visited, i, -1))
      {
        return true;
      }
    }
  }

  return false;
}

int main()
{
  { // Example 1
    std::vector<Relation> edges = {
      Relation{0, 1},
      Relation{1, 2},
      Relation{2, 3},
      Relation{0, 3},
      Relation{0, 4},
    };
    constexpr size_t size{5};

    auto const directed_graph   = make_graph(edges, size, false);
    auto const undirected_graph = make_graph(edges, size, true);

    std::cout << "Example 1 (directed): " << (has_cycle_directed(directed_graph) ? "true" : "false") << '\n';
    std::cout
      << "Example 1 (undirected): " << (has_cycle_undirected(undirected_graph) ? "true" : "false") << '\n';
  }
  { // Example 2
    std::vector<Relation> edges = {
      Relation{0, 1},
      Relation{1, 2},
      Relation{2, 3},
      Relation{3, 0},
      Relation{0, 4},
    };
    constexpr size_t size{5};

    auto const directed_graph   = make_graph(edges, size, false);
    auto const undirected_graph = make_graph(edges, size, true);

    std::cout << "Example 2 (directed): " << (has_cycle_directed(directed_graph) ? "true" : "false") << '\n';
    std::cout
      << "Example 2 (undirected): " << (has_cycle_undirected(undirected_graph) ? "true" : "false") << '\n';
  }
}
