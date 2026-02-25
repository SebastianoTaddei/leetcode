/*
Given a string s, find the length of the longest substring without duplicate
characters.

Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3. Note that "bca" and
"cab" are also correct answers.

Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a
substring.

Constraints:

0 <= s.length <= 5 * 104
s consists of English letters, digits, symbols and spaces.
*/

#include <algorithm>
#include <iostream>
#include <string>

int longest_substring(std::string const &s)
{
  int left    = 0;
  int right   = 0;
  int longest = 0;

  while (right < s.size())
  {
    auto const ch = s.at(right);
    bool add      = true;
    for (int i{left}; i < right and add; i++)
    {
      add = ch != s.at(i);
    }
    right   += static_cast<int>(add);
    left    += 1 - static_cast<int>(add);
    longest  = std::max(longest, right - left);
  }

  return longest;
}

int main()
{
  { // Example 1
    std::string s{"abcabcbb"};
    std::cout << "Example 1: " << longest_substring(s) << '\n';
  }
  { // Example 2
    std::string s{"bbbbb"};
    std::cout << "Example 2: " << longest_substring(s) << '\n';
  }
  { // Example 3
    std::string s{"pwwkew"};
    std::cout << "Example 3: " << longest_substring(s) << '\n';
  }
}
