#include <chrono>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <sstream>

using Clock = std::chrono::high_resolution_clock;
const std::string Input  = "../input/03.txt";
const std::string Input1 = "../input/03.debug1.txt";
const std::string Input2 = "../input/03.debug2.txt";

enum Direction { U, D, L, R };
const std::map<char, Direction> StringToDirection{
  { 'U', U }, { 'D', D }, { 'L', L }, { 'R', R }
};

using Coordinate = std::pair<int, int>;

int ManhattanDistance(const Coordinate& a, const Coordinate& b) {
  return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}

int ManhattanDistance(const Coordinate& a) {
  return std::abs(a.first) + std::abs(a.second);
}

int SolutionGenerator(const std::string& input)
{
  std::ifstream infile(input);
  std::string wire;
  std::map<Coordinate, int> grid; // coord, wire

  int res = std::numeric_limits<int>::max();

  int wireNum = 0;
  while (std::getline(infile, wire)) {
    std::istringstream inwire(wire);
    std::string token;
    Coordinate pos;

    while (std::getline(inwire, token, ',')) {
      Direction dir = StringToDirection.at(token[0]);
      token[0] = '0';
      int travelDist = std::stoi(token);

      for (int ii = 1; ii <= travelDist; ++ii) {
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
      } // end for
    } // end while

    ++wireNum;
  }

  return res;
}

int main() {
  auto start = Clock::now();

  int solone = SolutionGenerator(Input);

  auto partOne = Clock::now();

  auto end = Clock::now();

  std::cout << "Part One: " << solone << std::endl;
  std::cout << "Part Two: " << std::endl;

  std::cout << "Time: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(partOne - start).count()
    << " + "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - partOne).count()
    << " = "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    << " ms" << std::endl;

  return 0;
}
