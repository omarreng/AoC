#include <algorithm>
#include <functional>
#include <map>
#include <stack>
#include <unordered_set>

#include "fileio.h"
#include "strategies.h"
#include "utils.h"

int explore_region(const vector<vector<char>> &input, int ix, int iy);
int explore_plot(const vector<vector<char>> &input, int ix, int iy, const char plant, stack<pair<int, int>> &plots, const char dir);
void add_side(const char dir, int ix, int iy);
int count_hsides(const vector<vector<char>> &input, unordered_map<int, vector<int>> &sides);
int count_vsides(const vector<vector<char>> &input, unordered_map<int, vector<int>> &sides);

map<char, function<void(int &, int &)>> dir_map = {{'N', N}, {'E', E}, {'S', S}, {'W', W}};

unordered_set<pair<int, int>, pair_hash> visited_plots;
unordered_map<int, vector<int>> horizontal_up_sides;
unordered_map<int, vector<int>> horizontal_down_sides;
unordered_map<int, vector<int>> vertical_left_sides;
unordered_map<int, vector<int>> vertical_right_sides;

int main()
{
  auto input = read_file_char("Day12_input_test2.txt");

  int result = 0;
  for (int ix = 0; ix < input.size(); ix++)
  {
    for (int iy = 0; iy < input[0].size(); iy++)
    {
      if (visited_plots.find({ix, iy}) == visited_plots.end())
      {
        result += explore_region(input, ix, iy);
      }
    }
  }

  cout << "Result is: " << result << endl;

  return 0;
}

int explore_region(const vector<vector<char>> &input, int ix, int iy)
{
  stack<pair<int, int>> plots;
  horizontal_up_sides = {};
  horizontal_down_sides = {};
  vertical_left_sides = {};
  vertical_right_sides = {};
  visited_plots.insert({ix, iy});
  const auto plant = input[ix][iy];
  int perimeter = 0;
  for (const auto &dir : {'N', 'E', 'S', 'W'})
  {
    perimeter += explore_plot(input, ix, iy, plant, plots, dir);
  }
  int area = 1;
  while (!plots.empty())
  {
    auto plot = plots.top();
    plots.pop();
    area++;
    for (const auto &dir : {'N', 'E', 'S', 'W'})
    {
      perimeter += explore_plot(input, plot.first, plot.second, plant, plots, dir);
    }
  }
  return area * (count_hsides(input, horizontal_up_sides) +
                 count_hsides(input, horizontal_down_sides) +
                 count_vsides(input, vertical_left_sides) +
                 count_vsides(input, vertical_right_sides));
}

int explore_plot(const vector<vector<char>> &input, int ix, int iy, const char plant, stack<pair<int, int>> &plots, const char dir)
{
  dir_map[dir](ix, iy);
  if (visited_plots.find({ix, iy}) != visited_plots.end())
  {
    if (is_bound(input, ix, iy) && input[ix][iy] == plant)
    {
      return 0;
    }
    add_side(dir, ix, iy);
    return 1;
  }
  if (is_bound(input, ix, iy) && input[ix][iy] == plant)
  {
    plots.push({ix, iy});
    visited_plots.insert({ix, iy});
    return 0;
  }
  add_side(dir, ix, iy);
  return 1;
}

void add_side(const char dir, int ix, int iy)
{
  switch (dir)
  {
  case 'N':
    dir_map['S'](ix, iy);
    horizontal_up_sides[ix].push_back(iy);
    break;
  case 'S':
    dir_map['N'](ix, iy);
    horizontal_down_sides[ix].push_back(iy);
    break;
  case 'E':
    dir_map['W'](ix, iy);
    vertical_right_sides[iy].push_back(ix);
    break;
  case 'W':
    dir_map['E'](ix, iy);
    vertical_left_sides[iy].push_back(ix);
    break;
  }
}

int count_hsides(const vector<vector<char>> &input, unordered_map<int, vector<int>> &sides)
{
  int result = 0;
  for (auto &[key, side] : sides)
  {
    result++;
    sort(side.begin(), side.end());
    for (int i = 0; i < side.size() - 1; i++)
    {
      if ((side[i + 1] - side[i]) != 1)
      {
        result++;
        continue;
      }
      if (is_bound(input, key, i) && input[key][side[i]] != input[key][side[i + 1]])
      {
        result++;
      }
    }
  }
  return result;
}

int count_vsides(const vector<vector<char>> &input, unordered_map<int, vector<int>> &sides)
{
  int result = 0;
  for (auto &[key, side] : sides)
  {
    result++;
    sort(side.begin(), side.end());
    for (int i = 0; i < side.size() - 1; i++)
    {
      if ((side[i + 1] - side[i]) != 1)
      {
        result++;
        continue;
      }
      if (is_bound(input, i, key) && input[side[i]][key] != input[side[i + 1]][key])
      {
        result++;
      }
    }
  }
  return result;
}