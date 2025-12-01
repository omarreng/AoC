#include <cstdint>
#include <unordered_map>

#include "fileio.h"

int64_t process_blink(int64_t input, int blink);
vector<int64_t> calculate(int64_t input);

#define BLINKS 75

struct pair_hash
{
  template <typename T1, typename T2>
  size_t operator()(const pair<T1, T2> &p) const
  {
    auto hash1 = hash<T1>{}(p.first);
    auto hash2 = hash<T2>{}(p.second);
    return hash1 ^ (hash2 << 1);
  }
};

unordered_map<pair<int64_t, int>, int64_t, pair_hash> cache;

int main()
{
  auto input = read_file("Day11_input.txt");
  input = split_line(input[0]);
  vector<int64_t> stones;

  for (const auto &s : input)
  {
    stones.push_back(stoll(s));
  }

  size_t result = 0;
  for (auto const &stone : stones)
  {
    result += process_blink(stone, BLINKS);
  }

  cout << "Result is: " << result << endl;

  return 0;
}

int64_t process_blink(int64_t input, int blink)
{
  if (cache.find({input, blink}) != cache.end())
  {
    return cache[{input, blink}];
  }
  if (blink == 0)
  {
    return 1;
  }
  auto temp = calculate(input);
  if (temp.size() == 1)
  {
    auto result = process_blink(temp[0], blink - 1);
    cache.insert({{input, blink}, result});
    return result;
  }
  auto result1 = process_blink(temp[0], blink - 1);
  auto result2 = process_blink(temp[1], blink - 1);
  cache.insert({{input, blink}, result1 + result2});
  return result1 + result2;
}

vector<int64_t> calculate(int64_t input)
{
  if (input == 0)
  {
    return {1};
  }
  else if (to_string(input).size() % 2 == 0)
  {
    auto s = to_string(input);
    return {stoll(s.substr(0, s.length() / 2)), stoll(s.substr(s.length() / 2))};
  }
  else
  {
    return {input * 2024};
  }
}