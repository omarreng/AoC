#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <unordered_set>

#include "fileio.h"

bool check_list(vector<int> list, map<int, set<int>> rules);
bool check_intersection(set<int> set1, set<int> set2);
bool custom_comparator(int a, int b, set<int> set_a, set<int> set_b);

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

  for (int i = 0; i < lists.size(); i++)
  {
    if (check_list(lists[i], rules))
    {
      lists.erase(lists.begin() + i);
      i--;
    }
  }

  for (auto &list : lists)
  {
    sort(list.begin(), list.end(), [&rules](int a, int b)
         { return custom_comparator(a, b, rules[a], rules[b]); });
  }

  int result = 0;

  for (auto list : lists)
  {
    result += list[list.size() / 2];
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

bool custom_comparator(int a, int b, set<int> set_a, set<int> set_b)
{
  unordered_set lookup_a = unordered_set(set_a.begin(), set_a.end());
  unordered_set lookup_b = unordered_set(set_b.begin(), set_b.end());
  if (lookup_a.find(b) != lookup_a.end())
  {
    return true;
  }
  if (lookup_b.find(a) != lookup_b.end())
  {
    return false;
  }
  return true;
}