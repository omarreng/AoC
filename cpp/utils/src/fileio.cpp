#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "fileio.h"

using namespace std;

vector<string> read_file(string file_path)
{
  ifstream inputFile(file_path, ifstream::in);

  if (!inputFile.is_open())
  {
    ostringstream error_message;
    error_message << "Error opening file: " << file_path;
    throw invalid_argument(error_message.str());
  }

  vector<string> result;
  string line;

  while (getline(inputFile, line))
  {
    result.push_back(line);
  }

  inputFile.close();

  return result;
}

vector<string> split_line(string str, char delimiter)
{
  istringstream iss(str);
  string token;
  vector<string> result;

  while (std::getline(iss, token, delimiter))
  {
    result.push_back(token);
  }

  return result;
}

vector<vector<string>> split_vector(const vector<string> &vec, string delimiter)
{
  vector<vector<string>> result;
  vector<string> temp;
  for (string str : vec)
  {
    if (str == delimiter)
    {
      result.push_back(temp);
      temp.clear();
      continue;
    }
    temp.push_back(str);
  }
  if (!temp.empty())
  {
    result.push_back(temp);
  }
  return result;
}

vector<vector<char>> read_file_char(string file_path)
{
  vector<vector<char>> result;
  auto input = read_file(file_path);
  for (auto line : input)
  {
    result.push_back(vector<char>(line.begin(), line.end()));
  }
  return result;
}