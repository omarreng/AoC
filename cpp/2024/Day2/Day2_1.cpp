#include <string>

#include "fileio.h"

bool isIncreasing(vector<int> vec);
bool isDecreasing(vector<int> vec);
bool isDistanceSafe(vector<int> vec);

int main()
{
  auto input = read_file("Day2_input.txt");

  vector<vector<int>> processed_input;

  for (int i = 0; i < input.size(); i++)
  {
    auto processed_row = split_line(input.at(i));
    vector<int> row;
    for(int j = 0; j < processed_row.size(); j++)
    {
      row.push_back(stoi(processed_row.at(j)));
    }
    processed_input.push_back(row);
  }

  int result = 0;

  for (auto row : processed_input)
  {
    if ( (isIncreasing(row) || isDecreasing(row)) && isDistanceSafe(row) )
    {
      result++;
    }
  }

  cout << "The result is: " << result << endl;

  return 0;
}

bool isIncreasing(vector<int> vec)
{
  for (int i = 0; i < vec.size() - 1; i++)
  {
    if(vec[i] >= vec[i+1])
    {
      return false;
    }
  }
  return true;
}

bool isDecreasing(vector<int> vec)
{
  for (int i = 0; i < vec.size() - 1; i++)
  {
    if(vec[i] <= vec[i+1])
    {
      return false;
    }
  }
  return true;
}

bool isDistanceSafe(vector<int> vec)
{
  for (int i = 0; i < vec.size() - 1; i++)
  {
    if(abs(vec[i] - vec[i+1]) > 3)
    {
      return false;
    }
  }
  return true;
}