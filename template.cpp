#include <chrono>
#include <fstream>
#include <iostream>

using Clock = std::chrono::high_resolution_clock;
const std::string Input = "../input/XX.debug.txt";

int main()
{
  auto start = Clock::now();

  auto partOne = Clock::now();

  auto end = Clock::now();

  std::cout << "Part One: " << std::endl;
  std::cout << "Part Two: " << std::endl;

  // clang-format off
  std::cout << "Time: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(partOne - start).count()
    << " + "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - partOne).count()
    << " = "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    << " ms" << std::endl;
  // clang-format on

  return 0;
}
