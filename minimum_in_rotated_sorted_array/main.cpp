/*
A sorted array of unique integers was rotated at an unknown pivot. For example,
[10, 20, 30, 40, 50] becomes [30, 40, 50, 10, 20]. Find the index of the
minimum element in this array.

Input: [30, 40, 50, 10, 20]
Output: 3
Explanation: The smallest element is 10, and its index is 3.

Input: [3, 5, 7, 11, 13, 17, 19, 2]
Output: 7
Explanation: The smallest element is 2, and its index is 7.
*/

#include <iostream>
#include <vector>

template <class Feasible>
int minimum_element_idx(std::vector<int> const &data, Feasible feasible)
{
  int left  = 0;
  int right = data.size() - 1;
  int found = -1;

  while (left <= right)
  {
    auto const middle = (right - left) / 2 + left;

    if (feasible(data.at(middle)))
    {
      found = middle;
      right = middle - 1;
    }
    else
    {
      left = middle + 1;
    }
  }

  return found;
}

int main()
{
  { // Example 1
    std::vector<int> data = {30, 40, 50, 10, 20};
    std::cout
      << "Example 1: "
      << minimum_element_idx(data, [end = data.back()](int middle) { return middle <= end; }) << '\n';
  }
  { // Example 2
    std::vector<int> data = {3, 5, 6, 11, 13, 17, 19, 2};
    std::cout
      << "Example 2: "
      << minimum_element_idx(data, [end = data.back()](int middle) { return middle <= end; }) << '\n';
  }
}
