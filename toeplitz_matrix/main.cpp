/*
Given an m x n matrix, return true if the matrix is Toeplitz. Otherwise, return false.

A matrix is Toeplitz if every diagonal from top-left to bottom-right has the same elements.

Input: matrix = [
  [1, 2, 3, 4],
  [5, 1, 2, 3],
  [9, 5, 1, 2]
]

Output: true

Explanation:
In the above grid, the diagonals are:
"[9]", "[5, 5]", "[1, 1, 1]", "[2, 2, 2]", "[3, 3]", "[4]".
In each diagonal all elements are the same, so the answer is True.

Input: matrix = [
  [1,2],
  [2,2]
]
Output: false

Input: matrix = [
  [1,6],
  [3,1]
]
Output: true
*/

#include <iostream>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

bool check_diagonal(Matrix const &matrix, size_t row, size_t col)
{
  auto const rows = matrix.size();
  auto const cols = matrix.front().size();

  auto const elem = matrix.at(row).at(col);
  for (size_t i{row + 1}, j{col + 1}; i < rows and j < cols; i++, j++)
  {
    if (elem != matrix.at(i).at(j))
    {
      return false;
    }
  }
  return true;
}

bool is_toeplitz(Matrix const &matrix)
{
  auto const rows = matrix.size();
  auto const cols = matrix.front().size();

  for (size_t i{0}; i < rows; i++)
  {
    if (not check_diagonal(matrix, i, 0))
    {
      return false;
    }
  }

  for (size_t j{1}; j < cols; j++)
  {
    if (not check_diagonal(matrix, 0, j))
    {
      return false;
    }
  }

  return true;
}

int main()
{
  {
    // Example 1
    Matrix matrix = {
      {1, 2, 3, 4},
      {5, 1, 2, 3},
      {9, 5, 1, 2},
    };

    std::cout << "Example 1: " << (is_toeplitz(matrix) ? "true" : "false") << '\n';
  }
  {
    // Example 2
    Matrix matrix = {
      {1, 2},
      {2, 2},
    };

    std::cout << "Example 2: " << (is_toeplitz(matrix) ? "true" : "false") << '\n';
  }
  {
    // Example 3
    Matrix matrix = {
      {1, 6},
      {3, 1},
    };

    std::cout << "Example 3: " << (is_toeplitz(matrix) ? "true" : "false") << '\n';
  }
}
