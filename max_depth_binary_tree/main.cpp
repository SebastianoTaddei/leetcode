/*
Given the root of a binary tree, return its maximum depth.

A binary tree's maximum depth is the number of nodes along the longest path from
the root node down to the farthest leaf node.

Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: 3

Example 2:

Input: root = [1,null,2]
Output: 2

Constraints:

The number of nodes in the tree is in the range [0, 104].
-100 <= Node.val <= 100
*/

#include <iostream>
#include <memory>
#include <optional>
#include <vector>

struct TreeNode;

using TreeNodePtr = std::shared_ptr<TreeNode>;
using Root        = std::vector<std::optional<int>>;

struct TreeNode
{
  int val{0};
  TreeNodePtr left{nullptr};
  TreeNodePtr right{nullptr};
};

TreeNodePtr make_node(int value)
{
  return std::make_shared<TreeNode>(TreeNode{.val = value, .left = nullptr, .right = nullptr});
}

TreeNodePtr make_tree(Root const &root)
{
  if (root.empty() or not root.front())
  {
    return {};
  }

  TreeNodePtr tree = make_node(root.front().value());

  std::queue<TreeNodePtr> queue{};
  queue.push(tree);

  // [3, 9, 20, null, null, 15, 7]
  int dir{1};
  auto const size = static_cast<int>(root.size());
  while (not queue.empty() and dir < size)
  {
    auto const node = queue.front();
    queue.pop();

    if (root.at(dir))
    {
      node->left = make_node(root.at(dir).value());
      queue.push(node->left);
    }
    dir++;
    if (root.at(dir))
    {
      node->right = make_node(root.at(dir).value());
      queue.push(node->right);
    }
    dir++;
  }

  return tree;
}

void print_tree(TreeNodePtr const &root)
{
  if (root == nullptr)
  {
    return;
  }

  std::queue<TreeNodePtr> queue{};
  queue.push(root);

  while (not queue.empty())
  {
    auto const node = queue.front();
    queue.pop();
    std::cout << node->val << '\n';

    if (node->left != nullptr)
    {
      queue.push(node->left);
      std::cout << node->left->val << ", ";
    }
    else
    {
      std::cout << "null, ";
    }
    if (node->right != nullptr)
    {
      queue.push(node->right);
      std::cout << node->right->val << ", ";
    }
    else
    {
      std::cout << "null, ";
    }
    std::cout << '\n';
  }
}

int max_depth(TreeNodePtr const &root)
{
  if (root == nullptr)
  {
    return 0;
  }

  return std::max(max_depth(root->left), max_depth(root->right)) + 1;
}

int main()
{
  {
    // Example 1
    Root root       = {3, 9, 20, std::nullopt, std::nullopt, 15, 7};
    auto const tree = make_tree(root);
    std::cout << "Example 1: " << max_depth(tree) << '\n';
  }
  { // Example 2
    Root root       = {1, std::nullopt, 2};
    auto const tree = make_tree(root);
    std::cout << "Example 2: " << max_depth(tree) << '\n';
  }
}
