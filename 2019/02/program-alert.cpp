#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using Clock = std::chrono::high_resolution_clock;
const std::string Input = "../input/02.txt";

enum Opcode {
  Add = 1,
  Mul = 2,
  End = 99
};

std::vector<int> Get1202Program() {
  std::ifstream infile(Input);
  std::string token;
  std::vector<int> res;

  while (std::getline(infile, token, ',')) {
    res.emplace_back(std::stoi(token));
  }

  return res;
}

int FooHard(std::vector<int> opcodes, int noun, int verb) {
  opcodes[1] = noun;
  opcodes[2] = verb;

  for (int i = 0; opcodes[i] != End; i += 4) {
    int opcode = opcodes[i];
    int lpos   = opcodes[i + 1];
    int rpos   = opcodes[i + 2];
    int wpos   = opcodes[i + 3];

    if (opcode == Add)
      opcodes[wpos] = opcodes[lpos] + opcodes[rpos];
    else
      opcodes[wpos] = opcodes[lpos] * opcodes[rpos];
  }

  return opcodes[0];
}

int FooHarder(const std::vector<int>& opcodes, int target) {
  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      if (target == FooHard(opcodes, i, j)) {
        return 100 * i + j;
      }
    }
  }

  return -1;
}

int main() {
  auto start = Clock::now();

  auto opcodes   = Get1202Program();
  int partOneAns = FooHard(opcodes, 12, 2);

  auto partOne = Clock::now();

  int partTwoAns = FooHarder(opcodes, 19690720);

  auto end = Clock::now();

  std::cout << "Part One: " << partOneAns << std::endl;
  std::cout << "Part Two: " << partTwoAns << std::endl;

  std::cout << "Time: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(partOne - start).count()
    << " + "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - partOne).count()
    << " = "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    << " ms" << std::endl;

  return 1;
}
