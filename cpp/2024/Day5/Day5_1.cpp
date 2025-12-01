#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <unordered_set>

#include "fileio.h"

bool check_list(vector<int> list, map<int, set<int>> rules);
bool check_intersection(set<int> set1, set<int> set2);

int main()
{
  auto input = read_file("Day5_input.txt");
  auto it = find(input.begin(), input.end(), "");

  vector<string> input_rules = vector<string>(input.begin(), it);
  vector<string> input_lists = vector<string>(it + 1, input.end());

  map<int, set<int>> rules;
  vector<vector<int>> lists;

  for (auto rule : input_rules)
  {
    const auto key = stoi(split_line(rule, '|')[0]);
    const auto value = stoi(split_line(rule, '|')[1]);
    rules[key].insert(value);
  }

  for (auto list : input_lists)
  {
    vector<int> temp;
    for (auto number : split_line(list, ','))
    {
      temp.push_back(stoi(number));
    }
    lists.push_back(temp);
  }

  int result = 0;

  for (auto list : lists)
  {
    if (check_list(list, rules))
    {
      result += list[list.size() / 2];
    }
  }

  cout << "Result is: " << result << endl;

  return 0;
}

bool check_list(vector<int> list, map<int, set<int>> rules)
{
  set<int> numbers;
  for (const auto number : list)
  {
    numbers.insert(number);
    if (check_intersection(numbers, rules[number]))
    {
      return false;
    }
  }
  return true;
}

bool check_intersection(set<int> set1, set<int> set2)
{
  unordered_set<int> lookup = unordered_set<int>(set1.begin(), set1.end());
  for (const auto number : set2)
  {
    if (lookup.find(number) != lookup.end())
    {
      return true;
    }
  }
  return false;
}