/*
Given an m x n grid of characters board and a string word, return true if word
exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where
adjacent cells are horizontally or vertically neighboring. The same letter cell
may not be used more than once.



Example 1:

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word =
"ABCCED" Output: true

Example 2:

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word =
"SEE" Output: true

Example 3:

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word =
"ABCB" Output: false

Constraints:

m == board.length
n = board[i].length
1 <= m, n <= 6
1 <= word.length <= 15
board and word consists of only lowercase and uppercase English letters.

Follow up: Could you use search pruning to make your solution faster with a
larger board?
*/

#include <array>
#include <iostream>
#include <utility>
#include <vector>

std::array<std::pair<int, int>, 4> moves = {
  std::pair{1, 0},
  std::pair{0, 1},
  std::pair{-1, 0},
  std::pair{0, -1},
};

bool dfs(
  std::vector<std::vector<char>> &board, int const row, int const col, std::string const &word, int const idx
)
{
  if (word.at(idx) != board.at(row).at(col))
  {
    return false;
  }
  if (idx == static_cast<int>(word.size() - 1))
  {
    return true;
  }

  auto const rows       = static_cast<int>(board.size());
  auto const cols       = static_cast<int>(board.front().size());
  auto const prev       = board.at(row).at(col);
  board.at(row).at(col) = '*';

  for (auto const &move : moves)
  {
    auto const next_row = row + move.first;
    auto const next_col = col + move.second;
    if (next_row < 0 or next_row >= rows or next_col < 0 or next_col >= cols)
    {
      continue;
    }
    if (dfs(board, next_row, next_col, word, idx + 1))
    {
      return true;
    }
  }

  board.at(row).at(col) = prev;
  return false;
}

bool find(std::vector<std::vector<char>> &board, std::string const &word)
{
  auto const rows = static_cast<int>(board.size());
  auto const cols = static_cast<int>(board.front().size());
  for (int row{0}; row < rows; row++)
  {
    for (int col{0}; col < cols; col++)
    {
      if (dfs(board, row, col, word, 0))
      {
        return true;
      }
    }
  }
  return false;
}

int main()
{
  {
    // Example 1
    std::vector<std::vector<char>> board = {
      {'A', 'B', 'C', 'E'},
      {'S', 'F', 'C', 'S'},
      {'A', 'D', 'E', 'E'},
    };
    std::string const word{"ABCCE"};
    std::cout << "Example 1: " << (find(board, word) ? "true" : "false") << '\n';
  }
  { // Example 2
    std::vector<std::vector<char>> board = {
      {'A', 'B', 'C', 'E'},
      {'S', 'F', 'C', 'S'},
      {'A', 'D', 'E', 'E'},
    };
    std::string const word{"SEE"};
    std::cout << "Example 2: " << (find(board, word) ? "true" : "false") << '\n';
  }
  { // Example 3
    std::vector<std::vector<char>> board = {
      {'A', 'B', 'C', 'E'},
      {'S', 'F', 'C', 'S'},
      {'A', 'D', 'E', 'E'},
    };
    std::string const word{"ABCB"};
    std::cout << "Example 3: " << (find(board, word) ? "true" : "false") << '\n';
  }
}
