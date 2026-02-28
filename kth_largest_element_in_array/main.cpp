/*
Given an integer array nums and an integer k, return the kth largest element in
the array.

Note that it is the kth largest element in the sorted order, not the kth
distinct element.

Can you solve it without sorting?

Example 1:

Input: nums = [3,2,1,5,6,4], k = 2
Output: 5

Example 2:

Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
Output: 4

Constraints:

1 <= k <= nums.length <= 105
-104 <= nums[i] <= 104
*/

#include <iostream>
#include <queue>
#include <vector>

int kth_largest(std::vector<int> const &nums, int const k)
{
  std::priority_queue<int, std::vector<int>, std::greater<int>> queue{};
  for (int i{0}; i < k; i++)
  {
    queue.push(nums.at(i));
  }
  for (int i{k}; i < static_cast<int>(nums.size()); i++)
  {
    auto const num      = nums.at(i);
    auto const smallest = queue.top();
    if (num > smallest)
    {
      queue.pop();
      queue.push(num);
    }
  }

  return queue.top();
}

int main()
{
  { // Example 1
    std::vector<int> nums = {3, 2, 1, 5, 6, 4};
    constexpr int k{2};
    std::cout << "Example 1: " << kth_largest(nums, k) << '\n';
  }
  { // Example 2
    std::vector<int> nums = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    constexpr int k{4};
    std::cout << "Example 1: " << kth_largest(nums, k) << '\n';
  }
}
