#include <chrono>
#include <fstream>
#include <iostream>

using Clock = std::chrono::high_resolution_clock;
const std::string inputLoc = "../input/0X.debug.txt";

int main() {
  auto start = Clock::now();

  auto partOne = Clock::now();

  auto end = Clock::now();

  std::cout << "Part One: " << std::endl;
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