#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> read_file(string file_ath);
vector<string> split_line(string str, char delimiter = ' ');
vector<vector<string>> split_vector(const vector<string> &vec, string delimiter = "\n");
vector<vector<char>> read_file_char(string file_path);
