#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

#include "fileio.hpp"

using namespace std;

int main()
{
    vector<string> input = readFile("input_day4.txt");

    int result = 0;

    for (const string &card : input)
    {
        int score = 0;
        vector<string> split_card = split_line(split_line(card, ':').at(1), '|');

        vector<string> winning_numbers = split_line(split_card.at(0), ' ');
        vector<string> numbers = split_line(split_card.at(1), ' ');

        winning_numbers.erase(std::remove(winning_numbers.begin(), winning_numbers.end(), ""), winning_numbers.end());
        numbers.erase(std::remove(numbers.begin(), numbers.end(), ""), numbers.end());

        for (const string &s : numbers)
        {
            if (std::find(winning_numbers.begin(), winning_numbers.end(), s) != winning_numbers.end())
            {
                score++;
            }
        }

        result += score ? static_cast<int>(pow(2, score - 1)) : 0;
    }

    cout << "Result : " << result << endl;

    return 0;
}