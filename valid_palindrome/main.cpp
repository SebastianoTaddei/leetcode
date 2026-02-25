/*
A phrase is a palindrome if, after converting all uppercase letters into
lowercase letters and removing all non-alphanumeric characters, it reads the
same forward and backward. Alphanumeric characters include letters and numbers.

Given a string s, return true if it is a palindrome, or false otherwise.

Example 1:

Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.
Example 2:

Input: s = "race a car"
Output: false
Explanation: "raceacar" is not a palindrome.
Example 3:

Input: s = " "
Output: true
Explanation: s is an empty string "" after removing non-alphanumeric characters.
Since an empty string reads the same forward and backward, it is a palindrome.

Constraints:

1 <= s.length <= 2 * 105
s consists only of printable ASCII characters.
*/

#include <cctype>
#include <iostream>
#include <string>

bool valid_palindrome(std::string const &s)
{
  int left  = 0;
  int right = s.size() - 1;

  while (left < right)
  {
    if (not std::isalnum(s.at(left)))
    {
      left++;
      continue;
    }
    if (not std::isalnum(s.at(right)))
    {
      right--;
      continue;
    }

    if (std::tolower(s.at(left)) != std::tolower(s.at(right)))
    {
      return false;
    }

    left++;
    right--;
  }

  return true;
}

int main()
{
  { // Example 1
    std::string const s{"A man, a plan, a canal: Panama"};
    std::cout << "Example 1: " << (valid_palindrome(s) ? "true" : "false") << '\n';
  }
  { // Example 2
    std::string const s{"race a car"};
    std::cout << "Example 2: " << (valid_palindrome(s) ? "true" : "false") << '\n';
  }
  { // Example 3
    std::string const s{" "};
    std::cout << "Example 3: " << (valid_palindrome(s) ? "true" : "false") << '\n';
  }
}
