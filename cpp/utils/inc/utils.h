#include <iostream>
#include <vector>

using namespace std;

void print_map(const vector<vector<char>> &input);

template <typename T>
bool is_bound(const vector<vector<T>> &vec, int ix, int iy)
{
  return ix >= 0 && iy >= 0 && ix < vec.size() && iy < vec[0].size();
}

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