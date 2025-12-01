
#include <functional>
#include <string>

#include "fileio.h"

bool checkForUnsafeLevels(vector<int> vec, function<bool(int, int)> comparator, bool bad_level = false);
vector<int> checkAfterErase(vector<int> vec, int idx);

int main()
{
  auto input = read_file("Day2_input.txt");

  vector<vector<int>> processed_input;

  for (int i = 0; i < input.size(); i++)
  {
    auto processed_row = split_line(input.at(i));
    vector<int> row;
    for (int j = 0; j < processed_row.size(); j++)
    {
      row.push_back(stoi(processed_row.at(j)));
    }
    processed_input.push_back(row);
  }

  int result = 0;

  for (auto row : processed_input)
  {
    if (checkForUnsafeLevels(row, [](int a, int b)
                             { return a >= b; }) ||
        checkForUnsafeLevels(row, [](int a, int b)
                             { return a <= b; }))
    {
      result++;
    }
  }

  cout << "The result is: " << result << endl;

  return 0;
}

bool checkForUnsafeLevels(vector<int> vec, function<bool(int, int)> comparator, bool bad_level)
{
  for (int i = 0; i < vec.size() - 1; i++)
  {
    if (abs(vec[i] - vec[i + 1]) > 3)
    {
      if (!bad_level)
      {
        return checkForUnsafeLevels(checkAfterErase(vec, i + 1), comparator, true) ||
               checkForUnsafeLevels(checkAfterErase(vec, i), comparator, true);
      }
      else
      {
        return false;
      }
    }
    if (comparator(vec[i], vec[i + 1]))
    {
      if (!bad_level)
      {
        return checkForUnsafeLevels(checkAfterErase(vec, i + 1), comparator, true) ||
               checkForUnsafeLevels(checkAfterErase(vec, i), comparator, true);
      }
      else
      {
        return false;
      }
    }
  }
  return true;
}

vector<int> checkAfterErase(vector<int> vec, int idx)
{
  vec.erase(vec.begin() + idx);
  return vec;
}