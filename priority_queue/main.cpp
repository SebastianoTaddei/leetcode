/*
Just some tests on how the STL priority queue works.
*/

#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using one_dim   = int;
using two_dim   = std::tuple<int, int>;
using three_dim = std::tuple<int, int, int>;

using one_queue   = std::priority_queue<one_dim, std::vector<one_dim>, std::greater<one_dim>>;
using two_queue   = std::priority_queue<two_dim, std::vector<two_dim>, std::greater<two_dim>>;
using three_queue = std::priority_queue<three_dim, std::vector<three_dim>, std::greater<three_dim>>;

int main()
{
  { // 1D
    std::vector<one_dim> data = {1, 3, 2, 5};
    one_queue queue{};
    for (auto const &elem : data)
    {
      queue.push(elem);
    }

    std::cout << "1D: ";
    while (not queue.empty())
    {
      std::cout << queue.top() << ", ";
      queue.pop();
    }
    std::cout << '\n';
  }
  { // 2D
    std::vector<two_dim> data = {
      {1, 3},
      {1, 2},
      {2, 1},
      {2, 2},
    };
    two_queue queue{};
    for (auto const &elem : data)
    {
      queue.push(elem);
    }

    std::cout << "2D: ";
    while (not queue.empty())
    {
      auto const elem = queue.top();
      std::cout << "[" << std::get<0>(elem) << ", ";
      std::cout << std::get<1>(elem) << "], ";
      queue.pop();
    }
    std::cout << '\n';
  }
  { // 3D
    std::vector<three_dim> data = {
      {1, 2, 1},
      {1, 2, 3},
      {2, 1, 1},
      {2, 1, 0},
    };
    three_queue queue{};
    for (auto const &elem : data)
    {
      queue.push(elem);
    }

    std::cout << "3D: ";
    while (not queue.empty())
    {
      auto const elem = queue.top();
      std::cout << "[" << std::get<0>(elem) << ", ";
      std::cout << std::get<1>(elem) << ", ";
      std::cout << std::get<2>(elem) << "], ";
      queue.pop();
    }
    std::cout << '\n';
  }
}
