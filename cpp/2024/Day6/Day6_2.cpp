#include <algorithm>
#include <functional>
#include <set>

#include "fileio.h"
#include "strategies.h"
#include "utils.h"

#define START_POS '^'
#define POSITION '.'
#define OBSTACLE '#'
#define NEW_OBSTACLE 'O'
#define INVALID_POS -1

void find_starting_position(const vector<vector<char>> &map, int &ix, int &iy);
void step(const vector<vector<char>> &map, int &ix, int &iy, const vector<function<void(int &, int &)>> strategies, int &index);
bool check_loop(const vector<vector<char>> &map, int ix, int iy);

const vector<function<void(int &, int &)>> strategies = {N, E, S, W};

int main()
{
  auto map = read_file_char("Day6_input.txt");

  int ix_start, iy_start;
  int strat_index = 0;
  find_starting_position(map, ix_start, iy_start);

  int ix = ix_start;
  int iy = iy_start;
  vector<pair<int, int>> new_obstacles;

  while (is_bound(map, ix, iy))
  {
    int ix_copy = ix;
    int iy_copy = iy;
    strategies[strat_index](ix_copy, iy_copy);

    if (is_bound(map, ix_copy, iy_copy))
    {
      if (map[ix_copy][iy_copy] == OBSTACLE)
      {
        step(map, ix, iy, strategies, strat_index);
        continue;
      }
      map[ix_copy][iy_copy] = OBSTACLE;
    }

    if (check_loop(map, ix_start, iy_start))
    {
      new_obstacles.push_back({ix_copy, iy_copy});
    }

    if (is_bound(map, ix_copy, iy_copy))
    {
      map[ix_copy][iy_copy] = POSITION;
    }

    step(map, ix, iy, strategies, strat_index);
  }

  for (auto obstacle : new_obstacles)
  {
    map[obstacle.first][obstacle.second] = NEW_OBSTACLE;
  }

  map[ix_start][iy_start] = POSITION;

  int result = 0;
  for (auto row : map)
  {
    result += count(row.begin(), row.end(), NEW_OBSTACLE);
  }

  cout << "Result is: " << result << endl;

  return 0;
}

void find_starting_position(const vector<vector<char>> &map, int &ix, int &iy)
{
  for (int row = 0; row < map.size(); row++)
  {
    for (int col = 0; col < map[0].size(); col++)
    {
      if (map[row][col] == START_POS)
      {
        ix = row;
        iy = col;
        return;
      }
    }
  }
  ix = INVALID_POS;
  iy = INVALID_POS;
}

void step(const vector<vector<char>> &map, int &ix, int &iy, const vector<function<void(int &, int &)>> strategies, int &index)
{
  auto strategy = strategies[index];

  int temp_x = ix;
  int temp_y = iy;
  strategy(temp_x, temp_y);
  if (is_bound(map, temp_x, temp_y) && map[temp_x][temp_y] == OBSTACLE)
  {
    index = ++index % strategies.size();
    return;
  }
  strategies[index](ix, iy);
}

bool check_loop(const vector<vector<char>> &map, int ix, int iy)
{
  set<tuple<int, int, int>> visited;
  int strat_index = 0;
  while (is_bound(map, ix, iy))
  {
    visited.insert({ix, iy, strat_index});
    step(map, ix, iy, strategies, strat_index);
    if (visited.find({ix, iy, strat_index}) != visited.end())
    {
      return true;
    }
  }
  return false;
}