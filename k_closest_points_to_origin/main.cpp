/*
Given an array of points where points[i] = [xi, yi] represents a point on the
X-Y plane and an integer k, return the k closest points to the origin (0, 0).

The distance between two points on the X-Y plane is the Euclidean distance
(i.e., √(x1 - x2)2 + (y1 - y2)2).

You may return the answer in any order. The answer is guaranteed to be unique
(except for the order that it is in).

Example 1:

Input: points = [[1,3],[-2,2]], k = 1
Output: [[-2,2]]
Explanation:
The distance between (1, 3) and the origin is sqrt(10).
The distance between (-2, 2) and the origin is sqrt(8).
Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
We only want the closest k = 1 points from the origin, so the answer is just
[[-2,2]].

Example 2:

Input: points = [[3,3],[5,-1],[-2,4]], k = 2
Output: [[3,3],[-2,4]]
Explanation: The answer [[-2,4],[3,3]] would also be accepted.

Constraints:

1 <= k <= points.length <= 104
-104 <= xi, yi <= 104
*/

#include <iostream>
#include <utility>
#include <vector>

using Point = std::pair<int, int>;
using Item  = std::pair<int, Point>;

[[nodiscard]] int dist(Point const &point)
{
  return point.first * point.first + point.second * point.second;
}

std::vector<Point> k_closest(std::vector<Point> const &points, int const k)
{
  auto const size = static_cast<int>(points.size());
  if (size <= k)
  {
    return points;
  }

  std::priority_queue<Item> queue{};
  for (int i{0}; i < k; i++)
  {
    auto const &point = points.at(i);
    queue.emplace(dist(point), point);
  }

  for (int i{k}; i < size; i++)
  {
    auto const &point   = points.at(i);
    auto const _dist    = dist(point);
    auto const furthest = queue.top();
    if (_dist < furthest.first)
    {
      queue.pop();
      queue.emplace(_dist, point);
    }
  }

  std::vector<Point> closests{};
  closests.reserve(k);
  while (not queue.empty())
  {
    closests.push_back(queue.top().second);
    queue.pop();
  }

  return closests;
}

void print_points(std::vector<Point> const &points)
{
  std::cout << '[';
  for (auto const &point : points)
  {
    std::cout << '(' << point.first << ", " << point.second << "), ";
  }
  std::cout << "]\n";
}

int main()
{
  { // Example 1
    std::vector<Point> points = {
      Point{1, 3},
      Point{-2, 2},
    };
    constexpr int k{1};
    auto const closests = k_closest(points, k);
    std::cout << "Example 1: ";
    print_points(closests);
  }
  { // Example 2
    std::vector<Point> points = {
      Point{3, 3},
      Point{5, -1},
      Point{-2, 4},
    };
    constexpr int k{2};
    auto const closests = k_closest(points, k);
    std::cout << "Example 2: ";
    print_points(closests);
  }
}
