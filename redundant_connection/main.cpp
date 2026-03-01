/*
In this problem, a tree is an undirected graph that is connected and has no
cycles.

You are given a graph that started as a tree with n nodes labeled from 1 to n,
with one additional edge added. The added edge has two different vertices chosen
from 1 to n, and was not an edge that already existed. The graph is represented
as an array edges of length n where edges[i] = [ai, bi] indicates that there is
an edge between nodes ai and bi in the graph.

Return an edge that can be removed so that the resulting graph is a tree of n
nodes. If there are multiple answers, return the answer that occurs last in the
input.

Example 1:

Input: edges = [[1,2],[1,3],[2,3]]
Output: [2,3]

Example 2:

Input: edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
Output: [1,4]

Constraints:

n == edges.length
3 <= n <= 1000
edges[i].length == 2
1 <= ai < bi <= edges.length
ai != bi
There are no repeated edges.
The given graph is connected.
*/

#include <iostream>
#include <vector>

[[nodiscard]] std::vector<int> make_parent(size_t const size)
{
  std::vector<int> parent{};
  parent.reserve(size);
  for (size_t i{0}; i < size; i++)
  {
    parent.push_back(i);
  }

  return parent;
}

[[nodiscard]] int find(std::vector<int> &parent, int const node)
{
  if (node != parent.at(node))
  {
    parent.at(node) = find(parent, parent.at(node));
  }

  return parent.at(node);
}

std::pair<int, int> find_cycle(std::vector<std::pair<int, int>> const &edges)
{
  auto const size = edges.size();
  auto parent     = make_parent(size);
  std::vector<int> rank(size, 0);

  for (auto const &edge : edges)
  {
    auto const a = edge.first - 1;
    auto const b = edge.second - 1;

    auto const pa = find(parent, a);
    auto const pb = find(parent, b);

    if (pa == pb)
    {
      return edge;
    }

    auto const rpa = rank.at(pa);
    auto const rpb = rank.at(pb);
    if (rpa < rpb)
    {
      parent.at(pa) = pb;
    }
    else if (rpb < rpa)
    {
      parent.at(pb) = pa;
    }
    else if (rpa == rpb)
    {
      parent.at(pb) = pa;
      rank.at(pa)++;
    }
  }

  return {-1, -1};
}

int main()
{
  { // Example 1
    std::vector<std::pair<int, int>> edges = {
      std::pair{1, 2},
      std::pair{1, 3},
      std::pair{2, 3},
    };
    auto const cycle = find_cycle(edges);
    std::cout << "Example 1: (" << cycle.first << ", " << cycle.second << ")\n";
  }
  { // Example 2
    std::vector<std::pair<int, int>> edges = {
      std::pair{1, 2},
      std::pair{2, 3},
      std::pair{3, 4},
      std::pair{1, 4},
      std::pair{1, 5},
    };
    auto const cycle = find_cycle(edges);
    std::cout << "Example 2: (" << cycle.first << ", " << cycle.second << ")\n";
  }
}
