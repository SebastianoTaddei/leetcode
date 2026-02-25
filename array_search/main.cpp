/*
Just a couple of array search algorithms:

- linear search (linear_search): O(n)
- binary search (binary_search): O(log(n))
*/

#include <iostream>
#include <vector>

int linear_search(std::vector<int> const &data, int search_for)
{
  for (int i{0}; i < data.size(); i++)
  {
    if (data.at(i) == search_for)
    {
      return i;
    }
  }

  return -1;
}

int binary_search(std::vector<int> const &data, int search_for)
{
  int left  = 0;
  int right = data.size() - 1;

  while (left <= right)
  {
    auto const middle = left + (right - left) / 2;
    if (search_for == data.at(middle))
    {
      return middle;
    }
    if (search_for < data.at(middle))
    {
      right = middle - 1;
    }
    else
    {
      left = middle + 1;
    }
  }

  return -1;
}

int main()
{
  { // Example 1
    std::vector<int> data    = {1, 2, 3, 4, 5};
    constexpr int search_for = 3;
    std::cout << "Example 1 - linear search: " << linear_search(data, search_for) << '\n';
    std::cout << "Example 1 - binary search: " << binary_search(data, search_for) << '\n';
  }
  { // Example 2
    std::vector<int> data    = {1, 2, 3, 4};
    constexpr int search_for = 3;
    std::cout << "Example 2 - linear search: " << linear_search(data, search_for) << '\n';
    std::cout << "Example 2 - binary search: " << binary_search(data, search_for) << '\n';
  }
  { // Example 3
    std::vector<int> data    = {1, 2, 3, 4, 5, 9, 12};
    constexpr int search_for = 13;
    std::cout << "Example 3 - linear search: " << linear_search(data, search_for) << '\n';
    std::cout << "Example 3 - binary search: " << binary_search(data, search_for) << '\n';
  }
}
