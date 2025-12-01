#include "fileio.h"

vector<tuple<int, int, bool>> unravel_disk_map(const string &input);

#define FREE_SPACE -1

int main()
{
  const auto input = read_file("Day9_input.txt");
  auto blocks = unravel_disk_map(input[0]);

  int end = blocks.size() - 1;

  while (end >= 0)
  {
    if (get<0>(blocks[end]) == FREE_SPACE || get<2>(blocks[end]))
    {
      end--;
    }
    else
    {
      get<2>(blocks[end]) = true;
      int start = 0;
      while (start < end)
      {
        if (get<0>(blocks[start]) != FREE_SPACE)
        {
          start++;
        }
        else
        {
          if (get<1>(blocks[end]) > get<1>(blocks[start]))
          {
            start++;
          }
          else if (get<1>(blocks[end]) == get<1>(blocks[start]))
          {
            get<0>(blocks[start]) = get<0>(blocks[end]);
            get<0>(blocks[end]) = FREE_SPACE;
            end--;
            break;
          }
          else
          {
            get<1>(blocks[start]) -= get<1>(blocks[end]);
            blocks.insert(blocks.begin() + start, blocks[end]);
            get<0>(blocks[end + 1]) = FREE_SPACE;
            end--;
            break;
          }
        }
      }
    }
  }

  size_t result = 0;
  int index = 0;
  for (const auto &block : blocks)
  {
    for (int i = 0; i < get<1>(block); i++)
    {
      if (get<0>(block) != FREE_SPACE)
      {
        result += get<0>(block) * index;
      }
      index++;
    }
  }

  cout << "Result is: " << result << endl;
  return 0;
}

vector<tuple<int, int, bool>> unravel_disk_map(const string &input)
{
  vector<tuple<int, int, bool>> result;
  int id = 0;
  for (int i = 0; i < input.size(); i++)
  {
    if (id % 2 == 0)
    {
      result.push_back({id / 2, input[i] - '0', false});
    }
    else
    {
      result.push_back({FREE_SPACE, input[i] - '0', false});
    }
    id++;
  }
  return result;
}