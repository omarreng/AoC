#include <algorithm>
#include <functional>

#include "fileio.h"
#include "strategies.h"
#include "utils.h"

#define START_POS '^'
#define OBSTACLE '#'
#define VISITED 'X'
#define INVALID_POS -1

void find_starting_position(vector<vector<char>> map, int &ix, int &iy);
void step(vector<vector<char>> &map, int &ix, int &iy, const vector<function<void(int &, int &)>> strategies, int &index);

const vector<function<void(int &, int &)>> strategies = {N, E, S, W};

int main()
{
  auto map = read_file_char("Day6_input.txt");

  int ix, iy;
  find_starting_position(map, ix, iy);

  int strat_index = 0;

  while (is_bound(map, ix, iy))
  {
    step(map, ix, iy, strategies, strat_index);
  }

  int result = 0;
  for (auto row : map)
  {
    result += count(row.begin(), row.end(), VISITED);
  }

  cout << "Result is: " << result << endl;

  return 0;
}

void find_starting_position(vector<vector<char>> map, int &ix, int &iy)
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

void step(vector<vector<char>> &map, int &ix, int &iy, const vector<function<void(int &, int &)>> strategies, int &index)
{
  map[ix][iy] = VISITED;
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