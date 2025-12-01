#include <cmath>
#include <functional>
#include <map>

#include "fileio.h"
#include "strategies.h"

vector<pair<size_t, vector<size_t>>> process_input(const vector<string> &input);
void permutations(int n, vector<vector<string>> &result);
void get_permutations(int n, vector<vector<string>> &result, vector<string> permutation);

map<string, function<size_t(size_t, size_t)>> operators = {{"ADD", ADD}, {"MUL", MUL}};
map<int, vector<vector<string>>> cache;

int main()
{
  auto input = read_file("Day7_input.txt");
  auto calibration_tests = process_input(input);

  size_t result = 0;

  for (auto test : calibration_tests)
  {
    vector<vector<string>> operations;
    operations.reserve(pow(test.second.size() - 1, 2));
    permutations(test.second.size() - 1, operations);

    for (int i = 0; i < operations.size(); i++)
    {
      auto current_test = test.second;
      for (int j = 0; j < operations[0].size(); j++)
      {
        current_test[0] = operators[operations[i][j]](current_test[0], current_test[1]);
        current_test.erase(current_test.begin() + 1);
        if (current_test[0] > test.first)
        {
          break;
        }
      }
      if (current_test[0] == test.first)
      {
        result += test.first;
        break;
      }
    }
  }

  cout << "Result is: " << result << endl;

  return 0;
}

vector<pair<size_t, vector<size_t>>> process_input(const vector<string> &input)
{
  vector<pair<size_t, vector<size_t>>> tests;
  for (auto &line : input)
  {
    auto temp = split_line(line, ':');
    size_t result = stoll(temp[0]);
    vector<size_t> values;
    for (auto &number : split_line(temp[1]))
    {
      if (!number.empty())
      {
        values.push_back(stoll(number));
      }
    }
    tests.push_back({result, values});
  }
  return tests;
}

void permutations(int n, vector<vector<string>> &result)
{
  if (cache.find(n) != cache.end())
  {
    result = cache[n];
    return;
  }
  get_permutations(n, result, {});
  cache[n] = result;
}

void get_permutations(int n, vector<vector<string>> &result, vector<string> permutation)
{
  if (n == 0)
  {
    result.push_back(permutation);
    return;
  }
  vector<string> temp = permutation;

  permutation.push_back("ADD");
  get_permutations(n - 1, result, permutation);

  temp.push_back("MUL");
  get_permutations(n - 1, result, temp);
}