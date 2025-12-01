#include "fileio.h"

void process_blink(vector<size_t> &input, int &ix);

#define BLINKS 25

int main()
{
  auto input = read_file("Day11_input.txt");
  input = split_line(input[0]);
  vector<size_t> stones;

  for (const auto &s : input)
  {
    stones.push_back(stoll(s));
  }

  for (int i = 0; i < BLINKS; i++)
  {
    for (int ix = 0; ix < stones.size(); ix++)
    {
      process_blink(stones, ix);
    }
  }

  cout << "Result is: " << stones.size() << endl;

  return 0;
}

void process_blink(vector<size_t> &input, int &ix)
{
  if (input[ix] == 0)
  {
    input[ix] = 1;
  }
  else if (to_string(input[ix]).size() % 2 == 0)
  {
    auto ixs = to_string(input[ix]);
    auto ixs_1 = ixs.substr(0, ixs.length() / 2);
    auto ixs_2 = ixs.substr(ixs.length() / 2);
    input[ix] = stoll(ixs_1);
    input.insert(input.begin() + ix + 1, stoll(ixs_2));
    ix++;
  }
  else
  {
    input[ix] *= 2024;
  }
}