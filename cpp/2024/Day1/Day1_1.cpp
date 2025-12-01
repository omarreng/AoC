#include <algorithm>
#include <cstdint>
#include <string>

#include "fileio.h"

int main()
{
    auto input = read_file("Day1_input.txt"); 

    vector<int64_t> list_1, list_2;
    for (auto row : input)
    {
        auto numbers = split_line(row);
        list_1.push_back(stoi(numbers[0]));
        list_2.push_back(stoi(numbers[3]));
    }

    sort(list_1.begin(), list_1.end());
    sort(list_2.begin(), list_2.end());

    int result = 0;

    for (int i = 0; i < list_1.size(); i++)
    {
      result += std::abs(list_1.at(i) - list_2.at(i));
    }

    cout << "The result is: " << result << endl;

    return 0;
}