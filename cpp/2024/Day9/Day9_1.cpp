#include "fileio.h"

vector<int> unravel_disk_map(const string &input);

#define FREE_SPACE -1

int main()
{
  const auto input = read_file("Day9_input.txt");
  auto blocks = unravel_disk_map(input[0]);

  int start = 0;
  int end = blocks.size() - 1;

  while (start < end)
  {
    if (blocks[start] != FREE_SPACE)
    {
      start++;
    }
    else if (blocks[end] == FREE_SPACE)
    {
      end--;
    }
    else
    {
      blocks[start] = blocks[end];
      blocks[end] = FREE_SPACE;
      start++;
      end--;
    }
  }

  size_t result = 0;
  for (int i = 0; i < blocks.size(); i++)
  {
    if (blocks[i] != FREE_SPACE)
    {
      result += blocks[i] * i;
    }
  }

  cout << "Result is: " << result << endl;

  return 0;
}

vector<int> unravel_disk_map(const string &input)
{
  vector<int> result;
  int id = 0;
  for (int i = 0; i < input.size(); i++)
  {
    for (int length = 0; length < (input[i] - '0'); length++)
    {
      if (id % 2 == 0)
      {
        result.push_back(id / 2);
      }
      else
      {
        result.push_back(FREE_SPACE);
      }
    }
    id++;
  }
  return result;
}