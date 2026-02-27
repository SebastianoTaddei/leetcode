/*
An array of boolean values is divided into two sections: The left section
consists of all false, and the right section consists of all true. Find the
first True in a Sorted Boolean Array of the right section, i.e., the index of
the first true element. If there is no true element, return -1.

Input: arr = [false, false, true, true, true]
Output: 2
Explanation: The first true's index is 2.
*/

#include <iostream>
#include <vector>

template <class Feasible>
int first_true(std::vector<bool> const &data, Feasible feasible)
{
  int left      = 0;
  int right     = data.size() - 1;
  int first_idx = -1;
  while (left <= right)
  {
    int const middle = (right - left) / 2 + left;

    if (feasible(data.at(middle)))
    {
      first_idx = middle;
      right     = middle - 1;
    }
    else
    {
      left = middle + 1;
    }
  }

  return first_idx;
}

int main()
{
  { // Example 1
    std::vector<bool> data = {false, false, true, true, true};
    std::cout << "Example 1: " << first_true(data, [](bool elem) { return elem == true; }) << '\n';
  }
  { // Example 2
    std::vector<bool> data = {false, false, false, false, false};
    std::cout << "Example 2: " << first_true(data, [](bool elem) { return elem == true; }) << '\n';
  }
  { // Example 3
    std::vector<bool> data = {false, true, true, true, true};
    std::cout << "Example 3: " << first_true(data, [](bool elem) { return elem == true; }) << '\n';
  }
}
