#include <functional>
#include <map>
#include <stack>
#include <unordered_set>

#include "fileio.h"
#include "strategies.h"
#include "utils.h"

int explore_region(const vector<vector<char>> &input, int ix, int iy);
int explore_plot(const vector<vector<char>> &input, int ix, int iy, const char plant, stack<pair<int, int>> &plots, function<void(int &, int &)> dir);

map<char, function<void(int &, int &)>> dir_map = {{'N', N}, {'E', E}, {'S', S}, {'W', W}};

unordered_set<pair<int, int>, pair_hash> visited_plots;

int main()
{
  auto input = read_file_char("Day12_input.txt");

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
  visited_plots.insert({ix, iy});
  const auto plant = input[ix][iy];
  int perimeter = 0;
  for (const auto &dir : {'N', 'E', 'S', 'W'})
  {
    perimeter += explore_plot(input, ix, iy, plant, plots, dir_map[dir]);
  }
  int area = 1;
  while (!plots.empty())
  {
    auto plot = plots.top();
    plots.pop();
    area++;
    for (const auto &dir : {'N', 'E', 'S', 'W'})
    {
      perimeter += explore_plot(input, plot.first, plot.second, plant, plots, dir_map[dir]);
    }
  }
  return perimeter * area;
}

int explore_plot(const vector<vector<char>> &input, int ix, int iy, const char plant, stack<pair<int, int>> &plots, function<void(int &, int &)> dir)
{
  dir(ix, iy);
  if (visited_plots.find({ix, iy}) != visited_plots.end())
  {
    if (is_bound(input, ix, iy) && input[ix][iy] == plant)
    {
      return 0;
    }
    return 1;
  }
  if (is_bound(input, ix, iy) && input[ix][iy] == plant)
  {
    plots.push({ix, iy});
    visited_plots.insert({ix, iy});
    return 0;
  }
  return 1;
}