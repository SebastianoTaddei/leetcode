/*
Given the root of a binary tree, return the level order traversal of its nodes'
values. (i.e., from left to right, level by level).

Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]

Example 2:

Input: root = [1]
Output: [[1]]

Example 3:

Input: root = []
Output: []

Constraints:

The number of nodes in the tree is in the range [0, 2000].
-1000 <= Node.val <= 1000
*/

#include <iostream>
#include <memory>
#include <optional>
#include <queue>
#include <vector>

struct TreeNode;

using TreeNodePtr = std::shared_ptr<TreeNode>;

struct TreeNode
{
  int val;
  TreeNodePtr left{nullptr};
  TreeNodePtr right{nullptr};
};

TreeNodePtr make_binary_tree(std::vector<std::optional<int>> const &root)
{
  if (root.empty() or not root.front())
  {
    return {};
  }

  TreeNodePtr tree = std::make_shared<TreeNode>(TreeNode{.val = root.front().value()});
  std::queue<TreeNodePtr> queue{};
  queue.push(tree);

  size_t idx{1};
  // [3, 9, 20, null, null, 15, 7]
  while (not queue.empty() and idx < root.size())
  {
    auto const size = queue.size();
    auto const node = queue.front();
    queue.pop();

    if (node == nullptr)
    {
      idx++;
      continue;
    }

    if (root.at(idx))
    {
      node->left = std::make_shared<TreeNode>(TreeNode{.val = root.at(idx).value()});
      queue.push(node->left);
    }
    idx++;

    if (root.at(idx))
    {
      node->right = std::make_shared<TreeNode>(TreeNode{.val = root.at(idx).value()});
      queue.push(node->right);
    }
    idx++;
  }

  return tree;
}

void print_binary_tree(TreeNodePtr const &root)
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
    std::cout << (node->left ? node->left->val : -1) << ' ';
    std::cout << (node->right ? node->right->val : -1) << '\n';

    if (node->left != nullptr)
    {
      queue.push(node->left);
    }
    if (node->right != nullptr)
    {
      queue.push(node->right);
    }
  }
  std::cout << '\n';
}

std::vector<std::vector<int>> get_lot(TreeNodePtr const &root)
{
  if (root == nullptr)
  {
    return {};
  }

  std::vector<std::vector<int>> lot{};
  std::queue<TreeNodePtr> queue{};
  queue.push(root);

  while (not queue.empty())
  {
    auto const size = queue.size();
    std::vector<int> level{};
    level.reserve(size);
    for (size_t i{0}; i < size; i++)
    {
      auto const node = queue.front();
      queue.pop();
      level.push_back(node->val);
      if (node->left != nullptr)
      {
        queue.push(node->left);
      }
      if (node->right != nullptr)
      {
        queue.push(node->right);
      }
    }
    lot.push_back(std::move(level));
  }

  return lot;
}

void print_lot(std::vector<std::vector<int>> const &lot)
{
  std::cout << "[";
  for (auto const &level : lot)
  {
    std::cout << "[";
    for (auto const &elem : level)
    {
      std::cout << elem << ", ";
    }
    std::cout << "], ";
  }
  std::cout << "]\n";
}

int main()
{
  { // Example 1
    std::vector<std::optional<int>> root = {3, 9, 20, std::nullopt, std::nullopt, 15, 7};
    auto const tree                      = make_binary_tree(root);
    auto const lot                       = get_lot(tree);
    std::cout << "Example 1: ";
    print_lot(lot);
  }
  { // Example 2
    std::vector<std::optional<int>> root = {1};
    auto const tree                      = make_binary_tree(root);
    auto const lot                       = get_lot(tree);
    std::cout << "Example 2: ";
    print_lot(lot);
  }
  { // Example 3
    std::vector<std::optional<int>> root = {};
    auto const tree                      = make_binary_tree(root);
    auto const lot                       = get_lot(tree);
    std::cout << "Example 3: ";
    print_lot(lot);
  }
}
