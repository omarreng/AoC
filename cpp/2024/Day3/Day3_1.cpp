#include <string>

#include "fileio.h"

#define SUBSTR_LEN 3

vector<int> find_sum(string line, string substring = "mul");
bool is_number(string number);

int main()
{
  auto input = read_file("Day3_input.txt");

  int result = 0;

  for (const auto line : input)
  {
    const auto instances = find_sum(line);

    for (const auto instance : instances)
    {
      auto first_parantheses = line[instance + 3];
      if (first_parantheses != '(')
      {
        continue;
      }
      auto comma = line.find(",", instance + SUBSTR_LEN + 1);
      auto second_parentheses = line.find(")", instance + SUBSTR_LEN + 1);
      if (comma > second_parentheses)
      {
        continue;
      }
      const auto first_number = line.substr(instance + SUBSTR_LEN + 1, comma - (instance + SUBSTR_LEN + 1));
      const auto second_number = line.substr(comma + 1, second_parentheses - (comma + 1));

      if (is_number(first_number) && is_number(second_number))
      {
        result += stoi(first_number) * stoi(second_number);
      }
    }
  }

  cout << "Result is: " << result << endl;

  return 0;
}

vector<int> find_sum(string line, string substring)
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