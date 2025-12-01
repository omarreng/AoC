#include "fileio.h"

#include <cstdint>

int main()
{
  auto input = read_file_char("Day1_input.txt")[0];

  std::uint64_t sum = 0;

  for (int i = 0; i < input.size(); i++)
  {
    int j = (input.size() / 2 + i) % input.size();
    if (input[i] == input[j])
    {
      sum += input[i] - '0';
    }
  }

  std::cout << "The answer is: " << sum << std::endl;

  return 0;
}