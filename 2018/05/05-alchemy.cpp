#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>

using Clock = std::chrono::high_resolution_clock;

const std::string inputLoc = "../input/05.txt";

bool AreReactive(const char& a, const char& b) {
  return (a - 'a') == (b - 'A') || (a - 'A') == (b - 'a');
}

std::string PerformAlchemicalReduction() {
  std::ifstream inFile(inputLoc);
  char unit;

  std::string polymer;
  polymer.reserve(50000);

  while (inFile.get(unit)) {
    if (polymer.empty() || !AreReactive(polymer.back(), unit)) {
      polymer.push_back(unit);
    }
    else {
      polymer.pop_back();
    }
  }

  return polymer;
}

int FullyReactPolymer() {
  std::ifstream inFile(inputLoc);
  char unit;

  std::string polymer;
  polymer.reserve(50000);

  std::priority_queue<int, std::vector<int>, std::greater<int>> lengths;

  for (char c = 'a'; c <= 'z'; ++c) {
    while (inFile.get(unit)) {
      if (!AreReactive(unit, c) && unit != c) {
        if (polymer.empty() || !AreReactive(polymer.back(), unit)) {
          polymer.push_back(unit);
        }
        else {
          polymer.pop_back();
        }
      }
    }

    lengths.emplace(polymer.size());
    polymer.clear();

    inFile.clear();
    inFile.seekg(0, std::ios::beg);
  }

  return lengths.top();
}

int main() {
  auto start = Clock::now();

  std::string polymer = PerformAlchemicalReduction();
  auto partOne = Clock::now();

  auto shortest = FullyReactPolymer();
  auto end = Clock::now();

  std::cout << "Part One: " << polymer.size() << std::endl;
  std::cout << "Part Two: " << shortest;
  std::cout << std::endl;

  std::cout << "Time: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(partOne - start).count()
    << " + "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - partOne).count()
    << " = "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    << " ms" << std::endl;

  getchar();
  return 4;
}
