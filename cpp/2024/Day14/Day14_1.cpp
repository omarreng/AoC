#include <map>

#include "fileio.h"

#define ROWS 103
#define COLS 101
#define SECONDS 100

#define POS "position"
#define VEL "velocitoy"

vector<map<string, pair<int, int>>> analyze_input(const vector<string> &input);
void move_robot(map<string, pair<int, int>> &robot);

int main()
{
  auto input = read_file("Day14_input.txt");
  auto robots = analyze_input(input);

  for (int i = 0; i < SECONDS; i++)
  {
    for (auto &robot : robots)
    {
      move_robot(robot);
    }
  }

  int quad_1 = 0;
  int quad_2 = 0;
  int quad_3 = 0;
  int quad_4 = 0;

  for (auto &robot : robots)
  {
    if (robot[POS].first < ROWS / 2 && robot[POS].second < COLS / 2)
    {
      quad_1++;
    }
    else if (robot[POS].first < ROWS / 2 && robot[POS].second > COLS / 2)
    {
      quad_2++;
    }
    else if (robot[POS].first > ROWS / 2 && robot[POS].second < COLS / 2)
    {
      quad_3++;
    }
    else if (robot[POS].first > ROWS / 2 && robot[POS].second > COLS / 2)
    {
      quad_4++;
    }
  }

  cout << "Result is: " << quad_1 * quad_2 * quad_3 * quad_4 << endl;

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