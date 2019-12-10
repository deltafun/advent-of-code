#include <cmath>
#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

using Clock = std::chrono::high_resolution_clock;
const std::string inputLoc = "../input/01.txt";

std::vector<int> GetModules() {
  std::ifstream infile(inputLoc);
  std::string buf;
  std::vector<int> res;

  while (std::getline(infile, buf)) {
    res.emplace_back(std::stoi(buf));
  }

  return res;
}

int main() {
  auto start = Clock::now();

  auto mods = GetModules();

  int fuelone = 0;
  for (const auto& mod : mods) {
    fuelone += mod / 3 - 2;
  }

  auto partOne = Clock::now();

  int fueltwo = 0;
  for (auto mod : mods) {
    while (mod > 5) { // 1 * 3 + 2
      mod = mod / 3 - 2;
      fueltwo += mod;
    }
  }

  auto end = Clock::now();

  std::cout << "Part One: " << fuelone << std::endl;
  std::cout << "Part Two: " << fueltwo << std::endl;

  std::cout << "Time: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(partOne - start).count()
    << " + "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - partOne).count()
    << " = "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    << " ms" << std::endl;

  return 0;
}
