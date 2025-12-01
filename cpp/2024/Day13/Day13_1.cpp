#include <functional>
#include <map>
#include <numeric>

#include "fileio.h"

#define A "A"
#define B "B"
#define PRIZE "PRIZE"
#define COST_A 3
#define COST_B 1

vector<map<string, pair<int, int>>> analyze_input(const vector<vector<string>> &input);
pair<int, int> get_numbers(const string &s, const char delimiter);
tuple<int, int, int> extendedGCD(int a, int b);

int main()
{
  auto input = read_file("Day13_input_test.txt");
  auto split_input = split_vector(input, "");

  auto claw_machines = analyze_input(split_input);

  for (auto &machine : claw_machines)
  {
    int a = machine["A"].first;
    int b = machine["B"].first;
    int c = machine["PRIZE"].first;
    auto [gcd, x0, y0] = extendedGCD(a, b);
    if (c % gcd == 0)
    {
      function<int(int)> solution_x = [b, c, gcd, x0](int k) -> int
      { return (c / gcd) * x0 - (b / gcd) * k; };
      function<int(int)> solution_y = [a, c, gcd, y0](int k) -> int
      { return (c / gcd) * y0 + (a / gcd) * k; };
      int kx = ((c / gcd) * x0) * (gcd / b);
      int ky = ((c / gcd) * y0) * (gcd / a) * (-1);
      vector<int> k_values;
      for (int i = min(kx, ky); i <= max(kx, ky); i++)
      {
        k_values.push_back(i);
      }
    }
  }

  return 0;
}

vector<map<string, pair<int, int>>> analyze_input(const vector<vector<string>> &input)
{
  vector<map<string, pair<int, int>>> machines;
  for (const auto &machine : input)
  {
    map<string, pair<int, int>> temp;
    temp.insert({A, get_numbers(machine[0], '+')});
    temp.insert({B, get_numbers(machine[1], '+')});
    temp.insert({PRIZE, get_numbers(machine[2], '=')});
    machines.push_back(temp);
  }
  return machines;
}

pair<int, int> get_numbers(const string &s, const char delimiter)
{
  auto ix = split_line(split_line(s, ',')[0], delimiter)[1];
  auto iy = split_line(split_line(s, ',')[1], delimiter)[1];
  return {stoi(ix), stoi(iy)};
}

tuple<int, int, int> extendedGCD(int a, int b)
{
  if (b == 0)
  {
    return {a, 1, 0};
  }
  auto [gcd, x1, y1] = extendedGCD(b, a % b);
  int x = y1;
  int y = x1 - (a / b) * y1;
  return {gcd, x, y};
}