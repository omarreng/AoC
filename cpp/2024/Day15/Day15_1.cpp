#include <functional>
#include <map>

#include "fileio.h"
#include "strategies.h"
#include "utils.h"

#define ROBOT '@'
#define WALL '#'
#define BOX 'O'
#define EMPTY_SPACE '.'
#define INVALID_POS {-1, -1}

vector<vector<char>> get_puzzle(const vector<string> &input);
vector<char> get_moves(const vector<string> &input);
pair<int, int> find_start_pos(const vector<vector<char>> &input);
pair<bool, vector<pair<int, int>>> is_move_possible(int ix, int iy, function<void(int &, int &)> dir, vector<vector<char>> &input);
void perform_move(vector<pair<int, int>> &boxes, vector<vector<char>> &input);

map<char, function<void(int &, int &)>> dir_map = {{'^', N}, {'>', E}, {'v', S}, {'<', W}};

int main()
{
  auto input = read_file("Day15_input.txt");
  auto split_input = split_vector(input, "");

  auto puzzle = get_puzzle(split_input[0]);
  const auto moves = get_moves(split_input[1]);

  auto position = find_start_pos(puzzle);

  for (const auto move : moves)
  {
    auto possible_move = is_move_possible(position.first, position.second, dir_map[move], puzzle);
    if (possible_move.first)
    {
      perform_move(possible_move.second, puzzle);
      dir_map[move](position.first, position.second);
    }
  }

  size_t result = 0;
  for (int ix = 0; ix < puzzle.size(); ix++)
  {
    for (int iy = 0; iy < puzzle[ix].size(); iy++)
    {
      if (puzzle[ix][iy] == BOX)
      {
        result += ix * 100 + iy;
      }
    }
  }

  cout << endl;
  cout << "Result is: " << result << endl;

  return 0;
}

vector<vector<char>> get_puzzle(const vector<string> &input)
{
  vector<vector<char>> result;
  for (const auto &line : input)
  {
    result.push_back(vector<char>(line.begin(), line.end()));
  }
  return result;
}

vector<char> get_moves(const vector<string> &input)
{
  vector<char> result;
  for (const auto &line : input)
  {
    vector<char> temp = vector<char>(line.begin(), line.end());
    result.insert(result.end(), temp.begin(), temp.end());
  }
  return result;
}

pair<int, int> find_start_pos(const vector<vector<char>> &input)
{
  for (int ix = 0; ix < input.size(); ix++)
  {
    for (int iy = 0; iy < input[ix].size(); iy++)
    {
      if (input[ix][iy] == ROBOT)
      {
        return {ix, iy};
      }
    }
  }
  return INVALID_POS;
}

pair<bool, vector<pair<int, int>>> is_move_possible(int ix, int iy, function<void(int &, int &)> dir, vector<vector<char>> &input)
{
  bool is_possible = false;
  vector<pair<int, int>> boxes;
  boxes.push_back({ix, iy});
  dir(ix, iy);
  while (is_bound(input, ix, iy))
  {
    if (input[ix][iy] == BOX)
    {
      boxes.push_back({ix, iy});
      dir(ix, iy);
      continue;
    }
    if (input[ix][iy] == WALL)
    {
      break;
    }
    if (input[ix][iy] == EMPTY_SPACE)
    {
      is_possible = true;
      boxes.push_back({ix, iy});
      break;
    }
  }
  return {is_possible, boxes};
}

void perform_move(vector<pair<int, int>> &boxes, vector<vector<char>> &input)
{
  input[boxes[0].first][boxes[0].second] = EMPTY_SPACE;
  input[boxes[1].first][boxes[1].second] = ROBOT;
  if (boxes.size() == 2)
  {
    return;
  }
  input[boxes[boxes.size() - 1].first][boxes[boxes.size() - 1].second] = BOX;
}