#include <iostream>
#include <vector>
#include <string>
#include <stdint.h>
#include <map>

#include "fileio.hpp"

using namespace std;

vector<vector<int64_t>> parse_map(const vector<string> str);
int64_t traverse_maps(const vector<vector<vector<int64_t>>> vec, int64_t seed);
int64_t traverse_map(const vector<vector<int64_t>> vec, int64_t source);

int main()
{
    vector<string> input = readFile("input_day5.txt");
    vector<vector<string>> processed_input = split_vector(input, "");

    vector<string> seeds = split_line(processed_input.at(0).at(0), ' ');
    seeds.erase(seeds.begin());

    vector<vector<string>> maps;

    for (int i = 1; i < processed_input.size(); i++)
    {
        string name = processed_input.at(i).at(0);
        name = split_line(name, ' ').at(0);

        vector<string> vec;
        for (int j = 1; j < processed_input.at(i).size(); j++)
        {
            vec.push_back(processed_input.at(i).at(j));
        }
        maps.push_back(vec);
    }

    vector<vector<vector<int64_t>>> processed_maps;

    for (const vector<string> vec : maps)
    {
        vector<vector<int64_t>> temp = parse_map(vec);
        processed_maps.push_back(temp);
    }

    uint64_t result = traverse_maps(processed_maps, std::stoll(seeds.at(0)));

    for (int i = 1; i < seeds.size(); i++)
    {
        uint64_t temp = traverse_maps(processed_maps, std::stoll(seeds.at(i)));
        if (temp < result)
        {
            result = temp;
        }
    }

    cout << "Result : " << result << endl;

    return 0;
}

vector<vector<int64_t>> parse_map(const vector<string> vec)
{
    vector<vector<int64_t>> result;
    for (const string str : vec)
    {
        vector<string> temp_s = split_line(str, ' ');
        vector<int64_t> temp_i;
        for (const string str : temp_s)
        {
            temp_i.push_back(std::stoll(str));
        }
        result.push_back(temp_i);
    }
    return result;
}

int64_t traverse_maps(const vector<vector<vector<int64_t>>> vec, int64_t seed)
{
    for (const vector<vector<int64_t>> temp : vec)
    {
        seed = traverse_map(temp, seed);
    }
    return seed;
}

int64_t traverse_map(const vector<vector<int64_t>> vec, int64_t source)
{
    for (const vector<int64_t> range : vec)
    {
        if (source >= range.at(1) && source < (range.at(1) + range.at(2)))
        {
            return (source - range.at(1)) + range.at(0);
        }
    }
    return source;
}