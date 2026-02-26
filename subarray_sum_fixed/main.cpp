/*
Given an array (list) nums consisted of only non-negative integers, find the
largest sum among all subarrays of length k in nums.

For example, if the input is nums = [1, 2, 3, 7, 4, 1], k = 3, then the output
would be 14 as the largest length 3 subarray sum is given by [3, 7, 4] which
sums to 14.
*/

#include <algorithm>
#include <iostream>
#include <vector>

int subarray_sum(std::vector<int> const &data, int k)
{
  if (data.size() < k)
  {
    return -1;
  }

  int highest = 0;
  int i{0};
  for (; i < k; i++)
  {
    highest += data.at(i);
  }
  int window = highest;
  for (; i < data.size(); i++)
  {
    window  = window - data.at(i - k) + data.at(i);
    highest = std::max(highest, window);
  }

  return highest;
}

int main()
{
  { // Example 1
    std::vector<int> data = {1, 2, 3, 7, 4, 1};
    constexpr int k{3};
    std::cout << "Example 1: " << subarray_sum(data, k) << '\n';
  }
  { // Example 2
    std::vector<int> data = {1, 2, 3, 7, 4, 1, 4, 10, 2};
    constexpr int k{3};
    std::cout << "Example 2: " << subarray_sum(data, k) << '\n';
  }
  { // Example 3
    std::vector<int> data = {1, 2, 3, 7, 4, 1, 4, 10, 2};
    constexpr int k{8};
    std::cout << "Example 2: " << subarray_sum(data, k) << '\n';
  }
}
