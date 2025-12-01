#include <iostream>
#include <iterator>
#include <vector>
#include <string>

#include "fileio.h"

using namespace std;

int count_line(const string &str);

int main()
{
    int result = 0;
    vector<string> file = readFile("input_day1.txt");

    for (string &s : file)
    {
        int number = count_line(s);
        result += count_line(s);
        cout << s << " : " << number << endl;
    }

    cout << result;

    return 0;
}

int count_line(const string &str)
{
    int result = 0;

    for (auto charStart = str.begin(); charStart != str.end(); charStart++)
    {
        if (isdigit(*charStart))
        {
            int number = *charStart - '0';
            result += number * 10;
            break;
        }
    }

    bool found = false;

    for (auto charEnd = str.end(); charEnd != str.begin(); charEnd--)
    {
        if (isdigit(*charEnd))
        {
            result += *charEnd - '0';
            found = true;
            break;
        }
    }

    if (!found && isdigit(*str.begin()))
    {
        result += *str.begin() - '0';
    }

    return result;
}