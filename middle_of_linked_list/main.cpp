/*
Given the head of a singly linked list, return the middle node of the linked
list.

If there are two middle nodes, return the second middle node.

Example 1:

Input: head = [1,2,3,4,5]
Output: [3,4,5]
Explanation: The middle node of the list is node 3.

Example 2:

Input: head = [1,2,3,4,5,6]
Output: [4,5,6]
Explanation: Since the list has two middle nodes with values 3 and 4, we return
the second one.

Constraints:

The number of nodes in the list is in the range [1, 100].
1 <= Node.val <= 100
*/

#include <iostream>
#include <memory>
#include <vector>

struct ListNode
{
  int value;
  std::shared_ptr<ListNode> next;
};

using ListNodePtr = std::shared_ptr<ListNode>;

ListNodePtr make_list(std::vector<int> const &values)
{
  ListNodePtr head{nullptr};
  ListNodePtr current{nullptr};

  for (auto const &value : values)
  {
    auto node = std::make_shared<ListNode>(ListNode{.value = value, .next = nullptr});
    if (head == nullptr)
    {
      head    = node;
      current = head;
    }
    else
    {
      current->next = node;
    }

    current = node;
  }

  return head;
}

void print_list(ListNodePtr head)
{
  while (head != nullptr)
  {
    std::cout << head->value << "->";
    head = head->next;
  }
  std::cout << '\n';
}

ListNodePtr find_middle(ListNodePtr head)
{
  ListNodePtr slow = head;
  ListNodePtr fast = head;

  while (fast != nullptr and fast->next != nullptr)
  {
    if (slow->next == nullptr)
    {
      return slow;
    }
    slow = slow->next;

    fast = fast->next;

    if (fast->next == nullptr)
    {
      return slow;
    }
    fast = fast->next;
  }

  return slow;
}

int main()
{
  { // Example 1
    std::vector<int> values = {1, 2, 3, 4, 5};
    auto const head         = make_list(values);
    auto const middle       = find_middle(head);
    print_list(middle);
  }
  { // Example 2
    std::vector<int> values = {1, 2, 3, 4, 5, 6};
    auto const head         = make_list(values);
    auto const middle       = find_middle(head);
    print_list(middle);
  }
  { // Example 3
    std::vector<int> values = {};
    auto const head         = make_list(values);
    auto const middle       = find_middle(head);
    print_list(middle);
  }
  { // Example 4
    std::vector<int> values = {1};
    auto const head         = make_list(values);
    auto const middle       = find_middle(head);
    print_list(middle);
  }
  { // Example 5
    std::vector<int> values = {1, 2};
    auto const head         = make_list(values);
    auto const middle       = find_middle(head);
    print_list(middle);
  }
  { // Example 6
    std::vector<int> values = {1, 2, 3};
    auto const head         = make_list(values);
    auto const middle       = find_middle(head);
    print_list(middle);
  }
  { // Example 7
    std::vector<int> values = {1, 2, 3, 4};
    auto const head         = make_list(values);
    auto const middle       = find_middle(head);
    print_list(middle);
  }
}
