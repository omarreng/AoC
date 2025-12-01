#include <functional>
#include <limits>
#include <map>
#include <stack>
#include <unordered_set>

#include "fileio.h"
#include "strategies.h"
#include "utils.h"

#define START 'S'
#define END 'E'
#define WALL '#'
#define FREE_SPACE '.'
#define INVALID_POS {-1, -1}

pair<int, int> find_position(const vector<vector<char>> &puzzle, const char position);
size_t find_optimal_score(const vector<vector<char>> &puzzle);

map<char, function<void(int &, int &)>> dir_map = {{'N', N}, {'E', E}, {'S', S}, {'W', W}};
map<char, vector<char>> dir_explore = {{'N', {'W', 'E'}}, {'E', {'N', 'S'}}, {'S', {'E', 'W'}}, {'W', {'S', 'N'}}};

struct node
{
  int ix;
  int iy;
  char direction;
  size_t score;
};

int main()
{
  auto input = read_file_char("Day16_input_test.txt");

  auto start_pos = find_position(input, START);
  auto end_pos = find_position(input, END);

  return 0;
}

pair<int, int> find_position(const vector<vector<char>> &puzzle, const char position)
{
  for (int ix = 0; ix < puzzle.size(); ix++)
  {
    for (int iy = 0; iy < puzzle[ix].size(); iy++)
    {
      if (puzzle[ix][iy] == position)
      {
        return {ix, iy};
      }
    }
  }
  return INVALID_POS;
}

size_t find_optimal_score(const vector<vector<char>> &puzzle)
{
  size_t result = numeric_limits<size_t>::max();
  stack<node> tiles;
  unordered_set<pair<int, int>, pair_hash> visited_tiles;

  auto start_pos = find_position(puzzle, START);
  visited_tiles.insert({start_pos.first, start_pos.second});

  tiles.push({start_pos.first, start_pos.second, 'W', 2000});
  tiles.push({start_pos.first, start_pos.second, 'N', 1000});
  tiles.push({start_pos.first, start_pos.second, 'S', 1000});
  tiles.push({start_pos.first, start_pos.second, 'E', 0});

  while (!tiles.empty())
  {
    auto tile = tiles.top();
    tiles.pop();
    int ix_temp = tile.ix;
    int iy_temp = tile.iy;
    tile.direction(ix_temp, iy_temp);
    if (!is_bound(puzzle, ix_temp, iy_temp))
    {
      continue;
    }
    if (visited_tiles.find({ix_temp, iy_temp}) != visited_tiles.end())
    {
      continue;
    }
  }

  return result;
}