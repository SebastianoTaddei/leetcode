/*
Given an array of integers nums and an integer target, return indices of the
two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not
use the same element twice.

You can return the answer in any order.

Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]
Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]


Constraints:

2 <= nums.length <= 104
-109 <= nums[i] <= 109
-109 <= target <= 109
Only one valid answer exists.

Follow-up: Can you come up with an algorithm that is less than O(n2) time complexity?
*/

#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

std::pair<int, int> two_sum(std::vector<int> const &nums, int target)
{
  std::unordered_map<int, int> found{};

  for (int i{0}; i < nums.size(); i++)
  {
    auto const need = target - nums.at(i);
    if (found.find(need) != found.end())
    {
      return {found[need], i};
    }
    found[nums.at(i)] = i;
  }

  return {-1, -1};
}

int main()
{
  { // Example 1
    std::vector<int> const nums = {2, 7, 11, 15};
    constexpr int target{9};
    auto const [i, j] = two_sum(nums, target);
    std::cout << "Example 1: (" << i << ", " << j << ")\n";
  }
  { // Example 2
    std::vector<int> const nums = {3, 2, 4};
    constexpr int target{6};
    auto const [i, j] = two_sum(nums, target);
    std::cout << "Example 1: (" << i << ", " << j << ")\n";
  }
  { // Example 3
    std::vector<int> const nums = {3, 3};
    constexpr int target{6};
    auto const [i, j] = two_sum(nums, target);
    std::cout << "Example 1: (" << i << ", " << j << ")\n";
  }
}
