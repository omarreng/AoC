#include "utils.h"

void print_map(const vector<vector<char>> &input)
{
  for (const auto &row : input)
  {
    for (const auto &col : row)
    {
      cout << col;
    }
    cout << endl;
  }
  cout << endl;
}