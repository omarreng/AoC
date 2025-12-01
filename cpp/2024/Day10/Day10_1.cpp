#include <functional>
#include <map>
#include <set>
#include <stack>

#include "fileio.h"
#include "strategies.h"
#include "utils.h"

vector<pair<int, int>> find_trailheads(const vector<vector<char>> &input);
int explore_trailhead(int ix, int iy, const vector<vector<char>> &input);

map<char, function<void(int &, int &)>> dir_map = {{'N', N}, {'E', E}, {'S', S}, {'W', W}};
map<char, vector<char>> directions = {{'N', {'N', 'E', 'W'}}, {'E', {'S', 'N', 'E'}}, {'S', {'W', 'E', 'S'}}, {'W', {'N', 'S', 'W'}}};

int main()
{
  auto input = read_file_char("Day10_input.txt");
  auto trailheads = find_trailheads(input);

  size_t result = 0;
  for (const auto &trailhead : trailheads)
  {
    result += explore_trailhead(trailhead.first, trailhead.second, input);
  }

  cout << endl;
  cout << "Result is: " << result << endl;

  return 0;
}

vector<pair<int, int>> find_trailheads(const vector<vector<char>> &input)
{
  vector<pair<int, int>> result;
  for (int i = 0; i < input.size(); i++)
  {
    for (int j = 0; j < input[i].size(); j++)
    {
      if (input[i][j] == '0')
      {
        result.push_back({i, j});
      }
    }
  }
  return result;
}

int explore_trailhead(int ix, int iy, const vector<vector<char>> &input)
{
  set<pair<int, int>> results;
  stack<pair<pair<int, int>, vector<char>>> trails;
  for (const auto &dir : {'N', 'E', 'S', 'W'})
  {
    int temp_x = ix;
    int temp_y = iy;
    dir_map[dir](temp_x, temp_y);
    if (is_bound(input, temp_x, temp_y) && input[temp_x][temp_y] - input[ix][iy] == 1)
    {
      trails.push({{temp_x, temp_y}, directions[dir]});
    }
  }
  while (!trails.empty())
  {
    auto trail = trails.top();
    trails.pop();
    for (const auto &dir : trail.second)
    {
      int temp_x = trail.first.first;
      int temp_y = trail.first.second;
      dir_map[dir](temp_x, temp_y);
      if (is_bound(input, temp_x, temp_y) && input[temp_x][temp_y] - input[trail.first.first][trail.first.second] == 1 && input[temp_x][temp_y] == '9')
      {
        results.insert({temp_x, temp_y});
        continue;
      }
      if (is_bound(input, temp_x, temp_y) && input[temp_x][temp_y] - input[trail.first.first][trail.first.second] == 1)
      {
        trails.push({{temp_x, temp_y}, directions[dir]});
      }
    }
  }
  return results.size();
}