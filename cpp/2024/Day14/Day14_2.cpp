#include <map>
#include <opencv4/opencv2/opencv.hpp>

#include "fileio.h"

#define ROWS 103
#define COLS 101
#define SECONDS 10000

#define POS "position"
#define VEL "velocitoy"

vector<map<string, pair<int, int>>> analyze_input(const vector<string> &input);
void move_robot(map<string, pair<int, int>> &robot);
vector<vector<char>> get_map(vector<map<string, pair<int, int>>> &robots);

map<char, char> char_intensity = {{'#', 255}, {'.', 0}};

int main()
{
  const string output_file = "./out/robot_map";
  auto input = read_file("Day14_input.txt");
  auto robots = analyze_input(input);

  for (int i = 0; i < SECONDS; i++)
  {
    for (auto &robot : robots)
    {
      move_robot(robot);
    }
    cv::Mat image(ROWS, COLS, CV_8UC1);
    auto robot_map = get_map(robots);
    for (int ix = 0; ix < ROWS; ix++)
    {
      for (int iy = 0; iy < COLS; iy++)
      {
        image.at<char>(ix, iy) = char_intensity[robot_map[ix][iy]];
      }
    }
    cv::imwrite(output_file + to_string(i) + ".png", image);
  }

  return 0;
}

vector<map<string, pair<int, int>>> analyze_input(const vector<string> &input)
{
  vector<map<string, pair<int, int>>> result;
  for (const auto &line : input)
  {
    auto position = split_line(split_line(split_line(line)[0], '=')[1], ',');
    auto velocity = split_line(split_line(split_line(line)[1], '=')[1], ',');
    result.push_back({{POS, {stoi(position[1]), stoi(position[0])}}, {VEL, {stoi(velocity[1]), stoi(velocity[0])}}});
  }
  return result;
}

void move_robot(map<string, pair<int, int>> &robot)
{
  robot[POS].first = (robot[POS].first + robot[VEL].first) % ROWS;
  if (robot[POS].first < 0)
  {
    robot[POS].first += ROWS;
  }
  robot[POS].second = (robot[POS].second + robot[VEL].second) % COLS;
  if (robot[POS].second < 0)
  {
    robot[POS].second += COLS;
  }
}

vector<vector<char>> get_map(vector<map<string, pair<int, int>>> &robots)
{
  vector<vector<char>> result(ROWS, vector<char>(COLS, '.'));
  for (auto &robot : robots)
  {
    result[robot[POS].first][robot[POS].second] = '#';
  }
  return result;
}