#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <set>
#include <vector>

using Clock = std::chrono::high_resolution_clock;
const std::string inputLoc = "../input/06.txt";

using Coordinate = std::pair<int, int>;

int ManhattanDistance(const Coordinate& a, const Coordinate& b) {
  return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}

std::map<Coordinate, char> coordToChar;
std::vector<Coordinate> GetCoordinates() {
  std::ifstream inFile(inputLoc);
  std::string token;
  std::vector<Coordinate> coords;

  int i = 0;
  char c = 'a';

  while (std::getline(inFile, token, ',')) {
    if (++i == 26)
      c = 'A';
    int x = std::stoi(token);
    std::getline(inFile, token);
    int y = std::stoi(token);

    Coordinate coord = { x, y };
    coords.emplace_back(coord);

    coordToChar.emplace(coord, c++);
  }

  return coords;
}

std::pair<int, int> GetGridSize(const std::vector<Coordinate>& coords) {
  int x = -1;
  int y = -1;

  for (int i = 0; i < coords.size(); ++i) {
    x = std::max(x, coords[i].first);
    y = std::max(y, coords[i].second);
  }

  return { x, y };
}

int GetMaxArea(
  const std::vector<Coordinate>& coords, int x, int y) {

  std::set<Coordinate> infinite;
  std::map<Coordinate, int> coordToArea;
  int big = std::max(x, y);
  for (int i = 0; i <= big; ++i) {
    for (int j = 0; j <= big; ++j) {
      //std::cout << i << " " << j << std::endl;
      std::set<Coordinate> equidistantPoints;
      std::map<int, Coordinate> manDistanceToCoordinate;
      Coordinate point{ j, i };

      for (auto it = coords.cbegin(); it != coords.cend(); ++it) {

        int distance = ManhattanDistance(point, *it);

        if (manDistanceToCoordinate.count(distance) > 0) {
          equidistantPoints.emplace(manDistanceToCoordinate[distance]);
          equidistantPoints.emplace(*it);
        }
        else if (distance > 0 || true) {
          manDistanceToCoordinate.emplace(distance, *it);
        }
      }

      if (manDistanceToCoordinate.begin()->first == 0) {
        //std::cout << "~";
        continue;
      }

      Coordinate coordinate = manDistanceToCoordinate.begin()->second;

      // Filter out points that are equidistant from multiple coordinates.
      // Don't bother with "infinite" coordinates.
      if (infinite.count(coordinate) == 0
        && equidistantPoints.count(coordinate) == 0) {

        if (i == 0 || i == big || j == 0 || j == big) {
          infinite.emplace(coordinate);
          //std::cout << ".";
        }
        else if (coordToArea.count(coordinate) == 0) {
          coordToArea.emplace(coordinate, 1);
          //std::cout << coordToChar[coordinate];
        }
        else {
          ++coordToArea[coordinate];
          //std::cout << coordToChar[coordinate];
        }
      }
      else {
        //std::cout << ".";
      }
    } // end coordinate

    //std::cout << "\n";
  } // end row

  int maxArea = 0;
  
  for (auto coordAreaPair : coordToArea) {
    if (coordAreaPair.second > maxArea) {
      maxArea = coordAreaPair.second;
    }
  }
  
  auto solution = std::max_element(coordToArea.begin(), coordToArea.end(),
    [](auto a, auto b) { return a.second < b.second; });
  return maxArea + 1;
}

int GetMaxRegion(
  const std::vector<Coordinate>& coords, int x, int y) {

  int big = std::max(x, y); // lol
  int region = 0;

  for (int i = 0; i <= big; ++i) {
    for (int j = 0; j <= big; ++j) {

      Coordinate point{ j, i };
      int total = 0;

      for (auto it = coords.cbegin(); it != coords.cend(); ++it) {
        total += ManhattanDistance(point, *it);
      }

      if (total < 10000) {
        ++region;
      }
    }
  } // end row

  return region;
}

int main() {
  auto start = Clock::now();

  auto coords = GetCoordinates();
  auto gridSize = GetGridSize(coords);

  auto maxArea = GetMaxArea(coords, gridSize.first, gridSize.second);

  auto partOne = Clock::now();

  auto maxRegion = GetMaxRegion(coords, gridSize.first, gridSize.second);

  auto end = Clock::now();

  std::cout << "Part One: " << maxArea << std::endl;

  std::cout << "Part Two: " << maxRegion << std::endl;

  std::cout << "Time: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(partOne - start).count()
    << " + "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - partOne).count()
    << " = "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    << " ms" << std::endl;

  getchar();
  return 5;
}