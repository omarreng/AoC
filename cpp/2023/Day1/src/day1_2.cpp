#include <iostream>
#include <unordered_map>
#include <iterator>
#include <vector>
#include <string>

#include "fileio.hpp"

using namespace std;

unordered_map<string, int> numbers{
    {"zero", 0},
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9}};

int find_first(const string &str);
int find_last(const string &str);

std::pair<int, string> find_min_first(const string &str);
std::pair<int, string> find_max_last(const string &str);

int main()
{
    int result = 0;
    vector<string> file = readFile("input_day1.txt");

    for (string &s : file)
    {
        int first = find_first(s);
        int last = find_last(s);
        int number = 0;
        std::pair<int, string> first_part = find_min_first(s.substr(0, first));
        std::pair<int, string> last_part = find_max_last(s.substr(last + 1, s.size()));
        if (first_part.second != "")
        {
            first = numbers[first_part.second];
        }
        else
        {
            first = s.at(first) - '0';
        }

        if (last_part.second != "")
        {
            last = numbers[last_part.second];
        }
        else
        {
            last = s.at(last) - '0';
        }

        number += first * 10;
        number += last;
        cout << s << " : " << number << endl;
        // cout << first_part.second << " : " << last_part.second << endl;
        result += number;
    }

    cout << result;

    return 0;
}

int find_first(const string &str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (isdigit(str.at(i)))
        {
            return i;
        }
    }
    return -1;
}

int find_last(const string &str)
{
    for (int i = str.size() - 1; i >= 0; i--)
    {
        if (isdigit(str.at(i)))
        {
            return i;
        }
    }
    return -1;
}

std::pair<int, string> find_min_first(const string &str)
{
    std::pair<int, string> result = std::make_pair(str.size(), "");
    for (auto &s : numbers)
    {
        if (str.find(s.first) != string::npos && str.find(s.first) < result.first)
        {
            result = std::make_pair(str.find(s.first), s.first);
        }
    }
    return result;
}

std::pair<int, string> find_max_last(const string &str)
{
    std::pair<int, string> result = std::make_pair(-1, "");
    for (auto &s : numbers)
    {
        int position = str.rfind(s.first);
        if (str.rfind(s.first) != string::npos && position > result.first)
        {
            result = std::make_pair(position, s.first);
        }
    }
    return result;
}