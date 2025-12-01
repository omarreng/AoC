#include <algorithm>
#include <string>

#include "fileio.h"

#define SUBSTR_LEN 3

void process_multiplications(string input, uint &result);
void filter_multiplications(string line, vector<int> &instances);
vector<int> find(string line, string substring = "mul");
bool is_number(string number);

int main()
{
  auto input = read_file("Day3_input.txt");
  string processed_input;
  for (const auto line : input)
  {
    processed_input += line;
  }

  uint result = 0;

  process_multiplications(processed_input, result);

  cout << "Result is: " << result << endl;

  return 0;
}

void process_multiplications(string input, uint &result)
{
  auto instances = find(input);
  filter_multiplications(input, instances);

  for (const auto instance : instances)
  {
    auto first_parantheses = input[instance + 3];
    if (first_parantheses != '(')
    {
      continue;
    }
    auto comma = input.find(",", instance + SUBSTR_LEN + 1);
    auto second_parentheses = input.find(")", instance + SUBSTR_LEN + 1);
    if (comma > second_parentheses)
    {
      continue;
    }
    const auto first_number = input.substr(instance + SUBSTR_LEN + 1, comma - (instance + SUBSTR_LEN + 1));
    const auto second_number = input.substr(comma + 1, second_parentheses - (comma + 1));

    if (is_number(first_number) && is_number(second_number))
    {
      result += stoi(first_number) * stoi(second_number);
    }
  }
}

void filter_multiplications(string line, vector<int> &instances)
{
  auto dos = find(line, "do()");
  auto donts = find(line, "don't()");
  vector<pair<int, int>> invalid_ranges;

  for (const auto dont : donts)
  {
    auto it = upper_bound(dos.begin(), dos.end(), dont);
    if (it == dos.end())
    {
      invalid_ranges.push_back(make_pair(dont, line.size()));
      break;
    }
    invalid_ranges.push_back(make_pair(dont, *it));
  }

  for (int i = 0; i < instances.size(); i++)
  {
    auto target = instances[i];
    if (any_of(invalid_ranges.begin(), invalid_ranges.end(), [target](const pair<int, int> &interval)
               { return target >= interval.first && target <= interval.second; }))
    {
      instances.erase(instances.begin() + i);
      i--;
    }
  }
}

vector<int> find(string line, string substring)
{
  vector<int> result;
  size_t pos = line.find(substring);
  while (pos != string::npos)
  {
    result.push_back(pos);
    pos = line.find(substring, pos + substring.length());
  }
  return result;
}

bool is_number(string number)
{
  try
  {
    size_t pos;
    stoi(number, &pos);
    return pos == number.size();
  }
  catch (const exception &)
  {
    return false;
  }
}