#include <functional>
#include <map>
#include <set>

#include "fileio.h"
#include "utils.h"

map<char, vector<pair<int, int>>> scan_for_antennas(vector<vector<char>> &input);
void process_antenna_pair(pair<int, int> a1, pair<int, int> a2, const vector<vector<char>> &input, set<pair<int, int>> &results);
function<int(int)> get_linear_func(pair<int, int> p1, pair<int, int> p2);

int main()
{
  auto input = read_file_char("Day8_input.txt");
  auto antenna_map = scan_for_antennas(input);

  print_map(input);

  set<pair<int, int>> results;
  for (const auto &[frequency, antennas] : antenna_map)
  {
    for (int i = 0; i < antennas.size(); i++)
    {
      for (int j = i + 1; j < antennas.size(); j++)
      {
        process_antenna_pair(antennas[i], antennas[j], input, results);
      }
    }
  }

  for (const auto &result : results)
  {
    if (input[result.first][result.second] == '.')
    {
      input[result.first][result.second] = '#';
    }
  }

  print_map(input);

  cout << "Result is: " << results.size() << endl;

  return 0;
}

map<char, vector<pair<int, int>>> scan_for_antennas(vector<vector<char>> &input)
{
  map<char, vector<pair<int, int>>> result;
  for (int row = 0; row < input.size(); row++)
  {
    for (int col = 0; col < input[0].size(); col++)
    {
      if (input[row][col] != '.')
      {
        result[input[row][col]].push_back({row, col});
      }
    }
  }
  return result;
}

void process_antenna_pair(pair<int, int> a1, pair<int, int> a2, const vector<vector<char>> &input, set<pair<int, int>> &results)
{
  const auto line = get_linear_func(a1, a2);
  int delta = abs(a1.first - a2.first);

  const auto antenna_1 = a1.first < a2.first ? a1 : a2;
  const auto antenna_2 = a1.first < a2.first ? a2 : a1;

  const auto possible_antinode_1 = make_pair(antenna_1.first - delta, line(antenna_1.first - delta));
  const auto possible_antinode_2 = make_pair(antenna_2.first + delta, line(antenna_2.first + delta));

  if (is_bound(input, possible_antinode_1.first, possible_antinode_1.second))
  {
    results.insert(possible_antinode_1);
  }

  if (is_bound(input, possible_antinode_2.first, possible_antinode_2.second))
  {
    results.insert(possible_antinode_2);
  }
}

function<int(int)> get_linear_func(pair<int, int> p1, pair<int, int> p2)
{
  return [p1, p2](int x) -> int
  {
    int my = p2.second - p1.second;
    int mx = p2.first - p1.first;
    int by = p1.second * mx - my * p1.first;

    return (my * x + by) / mx;
  };
}