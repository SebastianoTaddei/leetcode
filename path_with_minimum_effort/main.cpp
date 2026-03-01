/*
You are a hiker preparing for an upcoming hike. You are given heights, a 2D
array of size rows x columns, where heights[row][col] represents the height of
cell (row, col). You are situated in the top-left cell, (0, 0), and you hope to
travel to the bottom-right cell, (rows-1, columns-1) (i.e., 0-indexed). You can
move up, down, left, or right, and you wish to find a route that requires the
minimum effort.

A route's effort is the maximum absolute difference in heights between two
consecutive cells of the route.

Return the minimum effort required to travel from the top-left cell to the
bottom-right cell.

Example 1:

Input: heights = [[1,2,2],[3,8,2],[5,3,5]]
Output: 2
Explanation: The route of [1,3,5,3,5] has a maximum absolute difference of 2 in
consecutive cells. This is better than the route of [1,2,2,2,5], where the
maximum absolute difference is 3.

Example 2:

Input: heights = [[1,2,3],[3,8,4],[5,3,5]]
Output: 1
Explanation: The route of [1,2,3,4,5] has a maximum absolute difference of 1 in
consecutive cells, which is better than route [1,3,5,3,5].

Example 3:

Input: heights = [[1,2,1,1,1],[1,2,1,2,1],[1,2,1,2,1],[1,2,1,2,1],[1,1,1,2,1]]
Output: 0
Explanation: This route does not require any effort.

Constraints:

rows == heights.length
columns == heights[i].length
1 <= rows, columns <= 100
1 <= heights[i][j] <= 106
*/

#include <array>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using Grid  = std::vector<std::vector<int>>;
using Point = std::pair<int, int>;
using Item  = std::pair<int, Point>;
using Queue = std::priority_queue<Item, std::vector<Item>, std::greater<Item>>;

int minimum_effort(Grid const &grid)
{
  auto const rows = static_cast<int>(grid.size());
  auto const cols = static_cast<int>(grid.front().size());

  Queue queue{};
  std::vector<std::vector<int>> costs(rows, std::vector<int>(cols, INT_MAX));

  Point const start{0, 0};
  Point const goal{rows - 1, cols - 1};

  queue.emplace(0, start);
  costs.at(start.first).at(start.second) = 0;

  std::array<std::pair<int, int>, 4> moves = {
    std::pair{1, 0},
    std::pair{0, 1},
    std::pair{-1, 0},
    std::pair{0, -1},
  };

  while (not queue.empty())
  {
    auto const item = queue.top();
    queue.pop();

    auto const cost       = item.first;
    auto const point      = item.second;
    auto const [row, col] = point;

    if (point == goal)
    {
      return cost;
    }

    for (auto const &move : moves)
    {
      auto const next_row = row + move.first;
      auto const next_col = col + move.second;

      if (next_row < 0 or next_row >= rows or next_col < 0 or next_col >= cols)
      {
        continue;
      }

      auto const effort    = std::abs(grid.at(row).at(col) - grid.at(next_row).at(next_col));
      auto const next_cost = std::max(cost, effort);
      if (next_cost < costs.at(next_row).at(next_col))
      {
        costs.at(next_row).at(next_col) = next_cost;
        queue.emplace(next_cost, Point{next_row, next_col});
      }
    }
  }

  return -1;
}

int main()
{
  { // Example 1
    Grid const grid = {
      {1, 2, 2},
      {3, 8, 2},
      {5, 3, 5},
    };
    std::cout << "Example 1: " << minimum_effort(grid) << '\n';
  }
  { // Example 2
    Grid const grid = {
      {1, 2, 3},
      {3, 8, 4},
      {5, 3, 5},
    };
    std::cout << "Example 2: " << minimum_effort(grid) << '\n';
  }
  { // Example 3
    Grid const grid = {
      {1, 2, 1, 1, 1}, {1, 2, 1, 2, 1}, {1, 2, 1, 2, 1}, {1, 2, 1, 2, 1}, {1, 1, 1, 2, 1}
    };
    std::cout << "Example 3: " << minimum_effort(grid) << '\n';
  }
}
