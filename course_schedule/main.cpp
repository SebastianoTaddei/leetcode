/*
There are a total of numCourses courses you have to take, labeled from 0 to
numCourses - 1. You are given an array prerequisites where prerequisites[i] =
[ai, bi] indicates that you must take course bi first if you want to take
course ai.

For example, the pair [0, 1], indicates that to take course 0 you have to first
take course 1. Return true if you can finish all courses. Otherwise, return
false.

Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take. To take course 1 you
should have finished course 0. So it is possible.

Example 2:

Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take.
To take course 1 you should have finished course 0, and to take course 0 you
should also have finished course 1. So it is impossible.

Constraints:

1 <= numCourses <= 2000
0 <= prerequisites.length <= 5000
prerequisites[i].length == 2
0 <= ai, bi < numCourses
All the pairs prerequisites[i] are unique.
*/

#include <iostream>
#include <stack>
#include <vector>

using Graph = std::vector<std::vector<int>>;

Graph make_graph(std::vector<std::vector<int>> const &prerequisites, int num_courses)
{
  Graph graph(num_courses);

  for (auto const &prerequisite : prerequisites)
  {
    graph.at(prerequisite.at(1)).push_back(prerequisite.at(0));
  }

  return graph;
}

void dfs(Graph const &graph, std::vector<bool> &visited, std::stack<int> &sort_stack, int node)
{
  if (visited.at(node))
  {
    return;
  }
  visited.at(node) = true;

  for (auto const &neighbor : graph.at(node))
  {
    dfs(graph, visited, sort_stack, neighbor);
  }

  sort_stack.push(node);
}

std::vector<int> toposort(Graph const &graph)
{
  std::vector<bool> visited(graph.size(), false);
  std::stack<int> sort_stack;

  for (int i{0}; i < graph.size(); i++)
  {
    dfs(graph, visited, sort_stack, i);
  }

  std::vector<int> sort;
  sort.reserve(graph.size());
  while (not sort_stack.empty())
  {
    sort.push_back(sort_stack.top());
    sort_stack.pop();
  }

  return sort;
}

bool check(std::vector<int> const &sort, std::vector<std::vector<int>> const &edges)
{
  std::vector<int> order(sort.size());
  for (int i{0}; i < sort.size(); i++)
  {
    order.at(sort.at(i)) = i;
  }

  for (auto const &edge : edges)
  {
    auto const u = edge.at(1);
    auto const v = edge.at(0);

    if (order.at(u) >= order.at(v))
    {
      return false;
    }
  }

  return true;
}

int main()
{
  { // Example 1
    std::vector<std::vector<int>> prerequisites = {
      {1, 0},
    };

    int num_courses{2};

    auto const graph = make_graph(prerequisites, num_courses);
    auto const sort  = toposort(graph);
    auto const valid = check(sort, prerequisites);
    std::cout << "Example 1: " << (valid ? "true" : "false") << '\n';
  }
  { // Example 2
    std::vector<std::vector<int>> prerequisites = {
      {1, 0},
      {0, 1},
    };

    int num_courses{2};

    auto const graph = make_graph(prerequisites, num_courses);
    auto const sort  = toposort(graph);
    auto const valid = check(sort, prerequisites);
    std::cout << "Example 2: " << (valid ? "true" : "false") << '\n';
  }
  { // Example 3
    std::vector<std::vector<int>> prerequisites = {
      {1, 0},
      {2, 0},
      {3, 1},
      {3, 2},
    };

    int num_courses{4};

    auto const graph = make_graph(prerequisites, num_courses);
    auto const sort  = toposort(graph);
    auto const valid = check(sort, prerequisites);
    std::cout << "Example 3: " << (valid ? "true" : "false") << '\n';
  }
  { // Example 4
    std::vector<std::vector<int>> prerequisites = {
      {1, 0},
      {2, 0},
      {3, 1},
      {3, 2},
      {0, 3},
    };

    int num_courses{4};

    auto const graph = make_graph(prerequisites, num_courses);
    auto const sort  = toposort(graph);
    auto const valid = check(sort, prerequisites);
    std::cout << "Example 4: " << (valid ? "true" : "false") << '\n';
  }
  { // Example 5
    std::vector<std::vector<int>> prerequisites = {
      {1, 0},
      {2, 0},
      {3, 1},
      {3, 2},
      {1, 3},
    };

    int num_courses{4};

    auto const graph = make_graph(prerequisites, num_courses);
    auto const sort  = toposort(graph);
    auto const valid = check(sort, prerequisites);
    std::cout << "Example 5: " << (valid ? "true" : "false") << '\n';
  }
}
