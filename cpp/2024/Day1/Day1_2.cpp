#include <algorithm>
#include <cstdint>
#include <map>
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

    map<int64_t, int64_t> map;

    for (auto number : list_2)
    {
        map[number] += 1;
    }

    int result = 0;

    for (auto number : list_1)
    {
        result += number * map[number];
    }

    cout << "The result is: " << result << endl;

    return 0;
}