/*
Given an m x n 2D binary grid which represents a map of '1's (land) and '0's
(water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands
horizontally or vertically. You may assume all four edges of the grid are all
surrounded by water.

Example 1:

Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1
Example 2:

Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 300
grid[i][j] is '0' or '1'.
*/

#include <array>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

size_t dfs(std::vector<std::vector<char>> &grid, std::set<std::pair<int, int>> &visited, int row, int col)
{
  auto const rows = grid.size();
  auto const cols = grid.front().size();

  if (row >= rows or col >= cols)
  {
    return 0;
  }

  if (row < 0 or col < 0)
  {
    return 0;
  }

  if (grid.at(row).at(col) == '0' or visited.count({row, col}))
  {
    return 0;
  }
  visited.insert({row, col});
  // grid.at(row).at(col) = '0';

  std::array<std::pair<int, int>, 4> moves = {
    std::pair{1, 0},
    std::pair{0, 1},
    std::pair{-1, 0},
    std::pair{0, -1},
  };
  for (auto const &move : moves)
  {
    std::ignore = dfs(grid, visited, row + move.first, col + move.second);
  }

  return 1;
}

size_t solution(std::vector<std::vector<char>> &grid)
{
  auto const rows = grid.size();
  auto const cols = grid.front().size();

  size_t islands{0};
  std::set<std::pair<int, int>> visited;
  for (size_t i{0}; i < rows; i++)
  {
    for (size_t j{0}; j < cols; j++)
    {
      islands += dfs(grid, visited, i, j);
    }
  }

  return islands;
}

int main()
{
  { // Example 1
    std::vector<std::vector<char>> grid = {
      {'1', '1', '1', '1', '0'},
      {'1', '1', '0', '1', '0'},
      {'1', '1', '0', '0', '0'},
      {'0', '0', '0', '0', '0'},
    };

    std::cout << "Example 1: " << solution(grid) << '\n';
  }
  { // Example 2
    std::vector<std::vector<char>> grid = {
      {'1', '1', '0', '0', '0'},
      {'1', '1', '0', '0', '0'},
      {'0', '0', '1', '0', '0'},
      {'0', '0', '0', '1', '1'},
    };

    std::cout << "Example 2: " << solution(grid) << '\n';
  }
}
