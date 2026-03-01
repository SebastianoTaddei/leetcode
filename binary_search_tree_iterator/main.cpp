/*
Implement the BSTIterator class that represents an iterator over the in-order
traversal of a binary search tree (BST):

BSTIterator(TreeNode root) Initializes an object of the BSTIterator class. The
root of the BST is given as part of the constructor. The pointer should be
initialized to a non-existent number smaller than any element in the BST.
boolean hasNext() Returns true if there exists a number in the traversal to the
right of the pointer, otherwise returns false. int next() Moves the pointer to
the right, then returns the number at the pointer. Notice that by initializing
the pointer to a non-existent smallest number, the first call to next() will
return the smallest element in the BST.

You may assume that next() calls will always be valid. That is, there will be at
least a next number in the in-order traversal when next() is called.

Example 1:

Input
["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext",
"next", "hasNext"]
[[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
Output
[null, 3, 7, true, 9, true, 15, true, 20, false]

Explanation
BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
bSTIterator.next();    // return 3
bSTIterator.next();    // return 7
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 9
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 15
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 20
bSTIterator.hasNext(); // return False

Constraints:

The number of nodes in the tree is in the range [1, 105].
0 <= Node.val <= 106
At most 105 calls will be made to hasNext, and next.

Follow up:

Could you implement next() and hasNext() to run in average O(1) time and use
O(h) memory, where h is the height of the tree?
*/

#include <iostream>
#include <memory>
#include <optional>
#include <vector>

struct TreeNode;
using TreeNodePtr = std::shared_ptr<TreeNode>;
using Element     = std::optional<int>;

struct TreeNode
{
  int val{0};
  TreeNodePtr left{nullptr};
  TreeNodePtr right{nullptr};
};

TreeNodePtr make_node(int val)
{
  return std::make_shared<TreeNode>(TreeNode{.val = val, .left = nullptr, .right = nullptr});
}

TreeNodePtr make_tree(std::vector<Element> const &values)
{
  if (values.size() == 0 or not values.front())
  {
    return {};
  }

  TreeNodePtr root = make_node(values.front().value());
  std::queue<TreeNodePtr> queue{};
  queue.push(root);
  size_t idx{1};
  while (idx < values.size())
  {
    auto const node = queue.front();
    queue.pop();

    if (node == nullptr)
    {
      continue;
    }

    if (values.at(idx))
    {
      node->left = make_node(values.at(idx).value());
      queue.push(node->left);
    }
    idx++;
    if (values.at(idx))
    {
      node->right = make_node(values.at(idx).value());
      queue.push(node->right);
    }
    idx++;
  }

  return root;
}

struct BSTIterator
{
  BSTIterator(TreeNodePtr const &root) { this->traverse(root); }

  [[nodiscard]] int next()
  {
    if (not this->has_next())
    {
      return -1;
    }

    auto const _next = this->stack.top();
    this->stack.pop();
    this->traverse(_next->right);

    return _next->val;
  }

  [[nodiscard]] bool has_next() const { return not this->stack.empty(); }

private:
  std::stack<TreeNodePtr> stack{};

  void traverse(TreeNodePtr node)
  {
    while (node != nullptr)
    {
      this->stack.push(node);
      node = node->left;
    }
  }
};

int main()
{
  { // Example 1
    std::vector<Element> values = {7, 3, 15, std::nullopt, std::nullopt, 9, 20};
    auto const tree             = make_tree(values);
    auto bst_it                 = BSTIterator(tree);
    std::cout << "Example 1\n";
    std::cout << bst_it.next() << '\n';
    std::cout << bst_it.next() << '\n';
    std::cout << (bst_it.has_next() ? "true" : "false") << '\n';
    std::cout << bst_it.next() << '\n';
    std::cout << (bst_it.has_next() ? "true" : "false") << '\n';
    std::cout << bst_it.next() << '\n';
    std::cout << (bst_it.has_next() ? "true" : "false") << '\n';
    std::cout << bst_it.next() << '\n';
    std::cout << (bst_it.has_next() ? "true" : "false") << '\n';
  }
}
