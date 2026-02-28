/*
Just various algorithms for path planning on a 2D grid:

- DFS
- BFS
- Dijkstra
- Greedy
- A*
*/

#include <array>
#include <climits>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <utility>
#include <vector>

using Point     = std::pair<int, int>;
using Grid      = std::vector<std::vector<int>>;
using Path      = std::vector<Point>;
using Obstacles = std::vector<Point>;
using Item      = std::pair<int, Point>;
using PQueue    = std::priority_queue<Item, std::vector<Item>, std::greater<Item>>;

std::array<std::pair<int, int>, 4> moves = {
  std::pair{1, 0},
  std::pair{0, 1},
  std::pair{-1, 0},
  std::pair{0, -1},
};

void print_solution(Grid const &grid, Path const &path, Obstacles const &obstacles)
{
  int rows = grid.size();
  int cols = rows ? grid[0].size() : 0;

  // ANSI Colors
  const std::string RESET  = "\033[0m";
  const std::string GREEN  = "\033[1;32m";
  const std::string RED    = "\033[1;31m";
  const std::string ORANGE = "\033[38;5;208m";
  const std::string GRAY   = "\033[90m";

  std::vector<std::vector<char>> mask(rows, std::vector<char>(cols, 0));

  for (const auto &o : obstacles)
    if (o.first >= 0 && o.first < rows && o.second >= 0 && o.second < cols)
      mask[o.first][o.second] = '#';

  for (const auto &p : path)
    if (p.first >= 0 && p.first < rows && p.second >= 0 && p.second < cols)
      mask[p.first][p.second] = '*';

  if (!path.empty())
  {
    mask[path.front().first][path.front().second] = 'S';
    mask[path.back().first][path.back().second]   = 'G';
  }

  // Top border
  std::cout << "\n┌";
  for (int c = 0; c < cols; ++c)
    std::cout << "────";
  std::cout << "┐\n";

  for (int r = 0; r < rows; ++r)
  {
    std::cout << "│";
    for (int c = 0; c < cols; ++c)
    {

      if (mask[r][c] == '#')
      {
        std::cout << GRAY << " ██ " << RESET;
      }
      else if (mask[r][c] == 'S')
      {
        std::cout << ORANGE << std::setw(3) << grid[r][c] << " " << RESET;
      }
      else if (mask[r][c] == 'G')
      {
        std::cout << RED << std::setw(3) << grid[r][c] << " " << RESET;
      }
      else if (mask[r][c] == '*')
      {
        std::cout << GREEN << std::setw(3) << grid[r][c] << " " << RESET;
      }
      else
      {
        std::cout << std::setw(3) << grid[r][c] << " ";
      }
    }
    std::cout << "│\n";
  }

  // Bottom border
  std::cout << "└";
  for (int c = 0; c < cols; ++c)
    std::cout << "────";
  std::cout << "┘\n";

  std::cout
    << "\nLegend:\n"
    << ORANGE << "orange = start\n"
    << RESET << RED << "red    = goal\n"
    << RESET << GREEN << "green  = path\n"
    << RESET << GRAY << "██     = obstacle\n\n"
    << RESET;
}

Path bfs(Grid const &grid, Obstacles const &obstacles, Point const &start, Point const &goal)
{
  auto const rows = grid.size();
  auto const cols = grid.front().size();

  std::queue<Point> queue{};
  queue.push(start);

  std::map<Point, Point> came_from{};
  std::set<Point> obs{};
  for (auto const &obstacle : obstacles)
  {
    obs.insert(obstacle);
  }

  while (not queue.empty())
  {
    auto const point      = queue.front();
    auto const [row, col] = point;
    queue.pop();

    if (row == goal.first and col == goal.second)
    {
      break;
    }

    for (auto const &move : moves)
    {
      auto const next_row = row + move.first;
      auto const next_col = col + move.second;
      if (next_row < 0 or next_row >= rows or next_col < 0 or next_col >= cols)
      {
        continue;
      }

      auto const next_point = Point{next_row, next_col};
      if (came_from.find(next_point) != came_from.end() or obs.count(next_point) > 0)
      {
        continue;
      }

      queue.push(next_point);
      came_from[next_point] = point;
    }
  }

  Path path_rev{};
  path_rev.push_back(goal);
  while (path_rev.back() != start)
  {
    path_rev.push_back(came_from.at(path_rev.back()));
  }
  Path path{};
  path.reserve(path_rev.size());
  for (size_t i{path_rev.size()}; i > 0; i--)
  {
    path.push_back(path_rev.at(i - 1));
  }

  return path;
}

void dfs_rec(
  Grid const &grid,
  std::set<Point> const &obstacles,
  std::map<Point, Point> &came_from,
  Point const &point,
  Point const &goal
)
{
  if (point == goal)
  {
    return;
  }

  auto const rows       = grid.size();
  auto const cols       = grid.front().size();
  auto const [row, col] = point;
  for (auto const &move : moves)
  {
    auto const next_row = row + move.first;
    auto const next_col = col + move.second;

    if (next_row < 0 or next_row >= rows or next_col < 0 or next_col >= cols)
    {
      continue;
    }

    auto const next_point = Point{next_row, next_col};
    if (obstacles.count(next_point) > 0 or came_from.find(next_point) != came_from.end())
    {
      continue;
    }

    came_from[next_point] = point;
    dfs_rec(grid, obstacles, came_from, next_point, goal);
  }
}

Path dfs(Grid const &grid, Obstacles const &obstacles, Point const &start, Point const &goal)
{
  std::map<Point, Point> came_from{};

  std::set<Point> obs{};
  for (auto const &obstacle : obstacles)
  {
    obs.insert(obstacle);
  }

  dfs_rec(grid, obs, came_from, start, goal);

  Path path_rev{};
  path_rev.push_back(goal);
  while (path_rev.back() != start)
  {
    path_rev.push_back(came_from.at(path_rev.back()));
  }

  Path path{};
  path.reserve(path_rev.size());

  for (size_t i{path_rev.size()}; i > 0; i--)
  {
    path.push_back(path_rev.at(i - 1));
  }

  return path;
}

Path dijkstra(Grid const &grid, Obstacles const &obstacles, Point const &start, Point const &goal)
{
  auto const rows = grid.size();
  auto const cols = grid.front().size();

  std::map<Point, Point> came_from{};
  std::set<Point> obs{};
  for (auto const &obstacle : obstacles)
  {
    obs.insert(obstacle);
  }

  PQueue queue{};
  queue.emplace(0, start);
  std::vector<std::vector<int>> dist(rows, std::vector<int>(cols, INT_MAX));
  dist.at(start.first).at(start.second) = 0;

  while (not queue.empty())
  {
    auto const item       = queue.top();
    auto const cost       = item.first;
    auto const [row, col] = item.second;
    queue.pop();

    if (row == goal.first and col == goal.second)
    {
      break;
    }

    for (auto const &move : moves)
    {
      auto const next_row = row + move.first;
      auto const next_col = col + move.second;

      if (next_row < 0 or next_row >= rows or next_col < 0 or next_col >= cols)
      {
        continue;
      }

      auto const next_point = Point{next_row, next_col};
      if (obs.count(next_point) > 0)
      {
        continue;
      }

      auto const new_cost = dist.at(row).at(col) + grid.at(next_row).at(next_col);
      if (came_from.find(next_point) == came_from.end() or new_cost < dist.at(next_row).at(next_col))
      {
        dist.at(next_row).at(next_col) = new_cost;
        queue.emplace(new_cost, next_point);
        came_from[next_point] = Point{row, col};
      }
    }
  }

  Path path_rev{};
  path_rev.push_back(goal);
  while (path_rev.back() != start)
  {
    path_rev.push_back(came_from.at(path_rev.back()));
  }

  Path path{};
  path.reserve(path_rev.size());
  for (size_t i{path_rev.size()}; i > 0; i--)
  {
    path.push_back(path_rev.at(i - 1));
  }

  return path;
}

Path greedy(Grid const &grid, Obstacles const &obstacles, Point const &start, Point const &goal)
{
  auto const rows = grid.size();
  auto const cols = grid.front().size();

  std::map<Point, Point> came_from{};
  std::set<Point> obs{};
  for (auto const &obstacle : obstacles)
  {
    obs.insert(obstacle);
  }

  PQueue queue{};
  queue.emplace(0, start);

  while (not queue.empty())
  {
    auto const item       = queue.top();
    auto const [row, col] = item.second;
    queue.pop();

    if (row == goal.first and col == goal.second)
    {
      break;
    }

    for (auto const &move : moves)
    {
      auto const next_row = row + move.first;
      auto const next_col = col + move.second;

      if (next_row < 0 or next_row >= rows or next_col < 0 or next_col >= cols)
      {
        continue;
      }

      auto const next_point = Point{next_row, next_col};
      if (obs.count(next_point) > 0 or came_from.find(next_point) != came_from.end())
      {
        continue;
      }

      queue.emplace(grid.at(next_row).at(next_col), next_point);
      came_from[next_point] = Point{row, col};
    }
  }

  Path path_rev{};
  path_rev.push_back(goal);
  while (path_rev.back() != start)
  {
    path_rev.push_back(came_from.at(path_rev.back()));
  }

  Path path{};
  path.reserve(path_rev.size());
  for (size_t i{path_rev.size()}; i > 0; i--)
  {
    path.push_back(path_rev.at(i - 1));
  }

  return path;
}

Path astar(Grid const &grid, Obstacles const &obstacles, Point const &start, Point const &goal)
{
  auto const rows = grid.size();
  auto const cols = grid.front().size();

  std::map<Point, Point> came_from{};
  std::set<Point> obs{};
  for (auto const &obstacle : obstacles)
  {
    obs.insert(obstacle);
  }

  PQueue queue{};
  queue.emplace(0, start);

  std::vector<std::vector<int>> dist(rows, std::vector<int>(cols, INT_MAX));
  dist.at(start.first).at(start.second) = 0;

  while (not queue.empty())
  {
    auto const item       = queue.top();
    auto const cost       = item.first;
    auto const [row, col] = item.second;
    queue.pop();

    if (row == goal.first and col == goal.second)
    {
      break;
    }

    for (auto const &move : moves)
    {
      auto const next_row = row + move.first;
      auto const next_col = col + move.second;

      if (next_row < 0 or next_row >= rows or next_col < 0 or next_col >= cols)
      {
        continue;
      }

      auto const next_point = Point{next_row, next_col};
      if (obs.count(next_point) > 0)
      {
        continue;
      }

      auto const heuristic = std::abs(goal.first - next_row) + std::abs(goal.second - next_col);
      auto const new_cost  = cost + grid.at(next_row).at(next_col) + heuristic;
      if (new_cost < dist.at(next_row).at(next_col) or came_from.find(next_point) == came_from.end())
      {
        came_from[next_point] = Point{row, col};
        queue.emplace(new_cost, next_point);
        dist.at(next_row).at(next_col) = new_cost;
      }
    }
  }

  Path path_rev{};
  path_rev.push_back(goal);
  while (path_rev.back() != start)
  {
    path_rev.push_back(came_from.at(path_rev.back()));
  }

  Path path{};
  path.reserve(path_rev.size());
  for (size_t i{path_rev.size()}; i > 0; i--)
  {
    path.push_back(path_rev.at(i - 1));
  }

  return path;
}

int main()
{
  Grid const grid = {
    {1, 1, 1, 5, 5, 5, 1, 1, 1, 1},
    {1, 9, 1, 9, 9, 5, 1, 9, 9, 1},
    {1, 9, 1, 1, 1, 5, 1, 1, 9, 1},
    {1, 9, 9, 9, 1, 5, 9, 1, 9, 1},
    {1, 1, 1, 9, 1, 1, 9, 1, 1, 1},
    {5, 5, 1, 9, 9, 1, 9, 9, 9, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 9, 1},
    {1, 9, 9, 9, 9, 9, 9, 1, 9, 1},
    {1, 1, 1, 1, 1, 1, 9, 1, 1, 1},
    {9, 9, 9, 9, 9, 1, 1, 1, 9, 1}
  };
  Obstacles const obstacles = {
    {0, 3}, {0, 4}, {0, 5}, {1, 1}, {1, 5}, {1, 7}, {1, 8}, {2, 3}, {2, 7}, {3, 1},
    {3, 2}, {3, 3}, {3, 7}, {4, 5}, {4, 6}, {4, 7}, {5, 2}, {5, 5}, {6, 2}, {6, 3},
    {6, 5}, {6, 8}, {7, 8}, {8, 1}, {8, 2}, {8, 3}, {8, 8}, {9, 5}
  };
  // Obstacles const obstacles = {};
  Point const start{0, 0};
  Point const goal{9, 9};

  { // BFS
    auto const path = bfs(grid, obstacles, start, goal);
    std::cout << "Breadth First Search:\n";
    print_solution(grid, path, obstacles);
  }
  { // DFS
    auto const path = dfs(grid, obstacles, start, goal);
    std::cout << "Depth First Search:\n";
    print_solution(grid, path, obstacles);
  }
  { // Dijkstra
    auto const path = dijkstra(grid, obstacles, start, goal);
    std::cout << "Dijkstra:\n";
    print_solution(grid, path, obstacles);
  }
  { // Greedy
    auto const path = greedy(grid, obstacles, start, goal);
    std::cout << "Greedy:\n";
    print_solution(grid, path, obstacles);
  }
  { // A*
    auto const path = greedy(grid, obstacles, start, goal);
    std::cout << "A*:\n";
    print_solution(grid, path, obstacles);
  }
}
