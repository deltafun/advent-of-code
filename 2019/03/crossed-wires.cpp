#include <chrono>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>

using Clock = std::chrono::high_resolution_clock;
const std::string Input  = "../input/03.txt";
const std::string Input1 = "../input/03.debug1.txt";
const std::string Input2 = "../input/03.debug2.txt";
const std::string Input3 = "../input/03.debug3.txt";

enum Direction { U, D, L, R };
const std::map<char, Direction> StringToDirection{
  { 'U', U }, { 'D', D }, { 'L', L }, { 'R', R }
};

using Coordinate = std::pair<int, int>;

int ManhattanDistance(const Coordinate& a) {
  return std::abs(a.first) + std::abs(a.second);
}

int SolutionGenerator(const std::string& input)
{
  std::ifstream infile(input);
  std::string wire;
  std::map<Coordinate, int> grid; // coord, wire

  int res     = std::numeric_limits<int>::max();
  int wireNum = 0;

  while (std::getline(infile, wire)) {
    std::istringstream inwire(wire);
    std::string token;
    Coordinate pos;

    while (std::getline(inwire, token, ',')) {
      Direction dir = StringToDirection.at(token[0]);
      token[0] = '0';
      int travelDist = std::stoi(token);

      while (travelDist--) {
        switch (dir) {
          case U:
            ++pos.second;
            break;
          case D:
            --pos.second;
            break;
          case R:
            ++pos.first;
            break;
          case L:
            --pos.first;
            break;
        }

        auto it = grid.find(pos);
        if (it != grid.end() && it->second != wireNum)
          res = std::min(res, ManhattanDistance(pos));
        else
          grid.emplace(pos, wireNum);
      }
    }

    ++wireNum;
  }

  return res;
}

int SolutionGeneratorSeriesX(const std::string& input) {
  std::ifstream infile(input);
  std::string wire;
  std::map<Coordinate, int> grid; // coord, steps

  int res        = std::numeric_limits<int>::max();
  int secondWire = false;

  while (std::getline(infile, wire)) {
    std::istringstream inwire(wire);
    std::string token;
    Coordinate pos;
    int steps = 0;

    while (std::getline(inwire, token, ',')) {
      Direction dir = StringToDirection.at(token[0]);
      token[0] = '0';
      int travelDist = std::stoi(token);

      while (travelDist--) {
        ++steps;

        switch (dir) {
          case U:
            ++pos.second;
            break;
          case D:
            --pos.second;
            break;
          case R:
            ++pos.first;
            break;
          case L:
            --pos.first;
            break;
        }

        auto it = grid.find(pos);
        if (it == grid.end() && !secondWire)
          grid.emplace(pos, steps);
        else if (secondWire)
          res = std::min(res, it->second + steps);
      }
    }

    secondWire = true;
  }

  return res;
}

int main() {
  auto start = Clock::now();

  std::cout << SolutionGenerator(Input1) << "\n"
            << SolutionGenerator(Input2) << "\n"
            << SolutionGenerator(Input3) << "\n";
  int solone = SolutionGenerator(Input); // 1337

  auto partOne = Clock::now();

  std::cout << SolutionGeneratorSeriesX(Input1) << "\n"
            << SolutionGeneratorSeriesX(Input2) << "\n"
            << SolutionGeneratorSeriesX(Input3) << "\n";
  int soltwo = SolutionGeneratorSeriesX(Input); // 65356

  auto end = Clock::now();

  std::cout << "Part One: " << solone << std::endl;
  std::cout << "Part Two: " << soltwo << std::endl;

  std::cout << "Time: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(partOne - start).count()
    << " + "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - partOne).count()
    << " = "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    << " ms" << std::endl;

  return 0;
}
