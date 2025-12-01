#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "fileio.hpp"

using namespace std;

vector<vector<char>> process_input(vector<string> &vec);
std::pair<int, int> parse_number(vector<char> &vec, int index);
bool is_part_number(int row, int start, int end, vector<vector<char>> &vec, int number, map<std::pair<int, int>, vector<int>> &gears);
bool is_valid_index(int i, int j, vector<vector<char>> &vec);

int main()
{
    vector<string> input = readFile("input_day3.txt");
    vector<vector<char>> processed_input = process_input(input);

    std::pair<int, int> test_pair;
    vector<int> test_vector;

    map<std::pair<int, int>, vector<int>> gears;

    int result = 0;
    int gear_result = 0;

    for (int i = 0; i < processed_input.size(); i++)
    {
        for (int j = 0; j < processed_input.at(i).size(); j++)
        {
            if (std::isdigit(processed_input.at(i).at(j)))
            {
                std::pair<int, int> number = parse_number(processed_input.at(i), j);
                if (is_part_number(i, j, number.second, processed_input, number.first, gears))
                {
                    result += number.first;
                    cout << "This is a part number : " << number.first << endl;
                }
                j = number.second;
            }
        }
    }

    for (const auto &kvpair : gears)
    {
        if (kvpair.second.size() == 2)
        {
            gear_result += kvpair.second.at(0) * kvpair.second.at(1);
        }
    }

    cout << "Result : " << result << endl;
    cout << "Gear result : " << gear_result << endl;

    return 0;
}

vector<vector<char>> process_input(vector<string> &vec)
{
    vector<vector<char>> result;
    for (string &str : vec)
    {
        vector<char> temp_vec;
        for (char &c : str)
        {
            temp_vec.push_back(c);
        }
        result.push_back(temp_vec);
    }
    return result;
}

std::pair<int, int> parse_number(vector<char> &vec, int index)
{
    int result = 0;
    while (index < vec.size() && std::isdigit(vec.at(index)))
    {
        result = result * 10 + vec.at(index++) - '0';
    }
    return std::make_pair(result, index - 1);
}

bool is_part_number(int row, int start, int end, vector<vector<char>> &vec, int number, map<std::pair<int, int>, vector<int>> &gears)
{
    bool found = false;
    for (int i = row - 1; i < row + 2; i++)
    {
        for (int j = start - 1; j < end + 2; j++)
        {
            if (is_valid_index(i, j, vec))
            {
                if (!std::isdigit(vec.at(i).at(j)) && vec.at(i).at(j) != '.')
                {
                    if (vec.at(i).at(j) == '*')
                    {
                        if (gears.find(std::make_pair(i, j)) != gears.end())
                        {
                            gears.at(std::make_pair(i, j)).push_back(number);
                        }
                        else
                        {
                            vector<int> temp{number};
                            gears[std::make_pair(i, j)] = temp;
                        }
                    }
                    found = true;
                }
            }
        }
    }
    return found;
}

bool is_valid_index(int i, int j, vector<vector<char>> &vec)
{
    return i >= 0 && j >= 0 && i < vec.size() && j < vec.at(0).size();
}