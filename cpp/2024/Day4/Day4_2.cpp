#include <functional>
#include <string>

#include "fileio.h"
#include "strategies.h"

bool is_bound(int ix, int iy, int rows, int cols);
bool probe_letters(vector<vector<char>> puzzle, int ix, int iy, pair<function<void(int &, int &)>, function<void(int &, int &)>> direction);
void add_result(vector<vector<bool>> &results, int ix, int iy, pair<function<void(int &, int &)>, function<void(int &, int &)>> direction);
void print_result(vector<vector<char>> input, vector<vector<bool>> results, bool print_all = false);

const vector<pair<function<void(int &, int &)>, function<void(int &, int &)>>> strategies = {{NE, SW}, {SE, NW}, {SW, NE}, {NW, SE}};
const vector<char> letters = {'M', 'A', 'S'};
const char first_letter = 'A';

int main()
{
  auto input = read_file_char("Day4_input.txt");

  const auto rows = input.size();
  const auto cols = input[0].size();

  vector<vector<bool>> results(rows, vector<bool>(cols, false));
  int result = 0;

  print_result(input, results, true);

  for (int row = 0; row < rows; row++)
  {
    for (int col = 0; col < cols; col++)
    {
      if (input[row][col] != first_letter)
      {
        continue;
      }
      vector<pair<function<void(int &, int &)>, function<void(int &, int &)>>> matches;
      for (const auto strategy : strategies)
      {
        if (probe_letters(input, row, col, strategy))
        {
          matches.push_back(strategy);
        }
      }
      if (matches.size() == 2)
      {
        result++;
        add_result(results, row, col, matches[0]);
        add_result(results, row, col, matches[1]);
      }
    }
  }

  print_result(input, results);

  cout << "Result is: " << result << endl;

  return 0;
}

bool is_bound(int ix, int iy, int rows, int cols)
{
  return ix >= 0 && iy >= 0 && ix < rows && iy < cols;
}

bool probe_letters(vector<vector<char>> puzzle, int ix, int iy, pair<function<void(int &, int &)>, function<void(int &, int &)>> direction)
{
  const auto rows = puzzle.size();
  const auto cols = puzzle[0].size();
  direction.second(ix, iy);
  for (const auto letter : letters)
  {
    if (!is_bound(ix, iy, rows, cols) || puzzle[ix][iy] != letter)
    {
      return false;
    }
    direction.first(ix, iy);
  }
  return true;
}

void add_result(vector<vector<bool>> &results, int ix, int iy, pair<function<void(int &, int &)>, function<void(int &, int &)>> direction)
{
  direction.second(ix, iy);
  for (const auto letter : letters)
  {
    results[ix][iy] = true;
    direction.first(ix, iy);
  }
}

void print_result(vector<vector<char>> input, vector<vector<bool>> results, bool print_all)
{
  const auto rows = input.size();
  const auto cols = input[0].size();

  for (int row = 0; row < rows; row++)
  {
    for (int col = 0; col < cols; col++)
    {
      if (results[row][col] || print_all)
      {
        cout << input[row][col];
      }
      else
      {
        cout << ".";
      }
    }
    cout << endl;
  }
  cout << endl;
}