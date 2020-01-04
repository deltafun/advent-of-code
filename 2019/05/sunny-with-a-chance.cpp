#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using Clock = std::chrono::high_resolution_clock;
const std::string Input = "../input/05.txt";

enum class Opcode
{
  Add = 1,
  Mul = 2,
  In = 3,
  Out = 4,
  End = 99
};

const std::map<int, Opcode> IntToOpcode{
  {1, Opcode::Add},
  {2, Opcode::Mul},
  {3, Opcode::In},
  {4, Opcode::Out},
  {99, Opcode::End},
};

const std::map<Opcode, int> OpcodeToParams{
  {Opcode::Add, 3},
  {Opcode::Mul, 3},
  {Opcode::In, 1},
  {Opcode::Out, 1},
  {Opcode::End, 0},
};

enum class Mode
{
  Position = 0,
  Immediate = 1
};

const std::map<int, Mode> IntToMode{
  {0, Mode::Position},
  {1, Mode::Immediate},

};

struct Instruction
{
  Opcode op;
  std::array<Mode, 3> modes;

  Instruction(int instruction)
  {
    try
    {
      op = IntToOpcode.at(instruction % 100);
    }
    catch (const std::out_of_range& e)
    {
      std::cerr << "Parsing error: instruction is " << instruction
                << " and instruction % 100 is " << instruction % 100 << "\n";
      throw e;
    }

    instruction /= 100;
    for (int ii = 0; ii < modes.size(); ++ii)
    {
      try
      {
        modes[ii] = IntToMode.at(instruction % 10);
      }
      catch (const std::out_of_range& e)
      {
        std::cerr << "Parsing error: " << instruction
                  << " and instruction % 10 is " << instruction % 10 << "\n";
        throw e;
      }
      instruction /= 10;
    }
  }
};

std::vector<int> GetTESTProgram()
{
  std::ifstream infile(Input);
  std::string token;
  std::vector<int> res;

  while (std::getline(infile, token, ','))
  {
    res.emplace_back(std::stoi(token));
  }

  return res;
}

int FooHard(std::vector<int> opcodes, int input)
{
  for (int ii = 0; opcodes[ii] != static_cast<int>(Opcode::End);)
  {
    Instruction inst{opcodes[ii]};
    std::array<int, 3> paramsIdx;

    for (int jj = 0; jj < OpcodeToParams.at(inst.op); ++jj)
    {
      paramsIdx[jj] =
        inst.modes[jj] == Mode::Immediate ? ii + jj + 1 : opcodes[ii + jj + 1];
    }

    switch (inst.op)
    {
      case Opcode::Add:
        opcodes[paramsIdx[2]] = opcodes[paramsIdx[0]] + opcodes[paramsIdx[1]];
        break;
      case Opcode::Mul:
        opcodes[paramsIdx[2]] = opcodes[paramsIdx[0]] * opcodes[paramsIdx[1]];
        break;
      case Opcode::In:
        opcodes[paramsIdx[0]] = input;
        break;
      case Opcode::Out:
        std::cout << opcodes[paramsIdx[0]] << "\n";
        break;
      default:
        break;
    }

    ii += OpcodeToParams.at(inst.op) + 1;
  }

  return opcodes[0];
}

int main()
{
  auto start = Clock::now();

  auto opcodes = GetTESTProgram();
  int partOneAns = FooHard(opcodes, 1);

  auto partOne = Clock::now();

  // int partTwoAns = FooHarder(opcodes, 19690720);

  auto end = Clock::now();

  std::cout << "Part One: " << partOneAns << std::endl;
  // std::cout << "Part Two: " << partTwoAns << std::endl;

  // clang-format off
  std::cout << "Time: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(partOne - start).count()
    << " + "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - partOne).count()
    << " = "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    << " ms" << std::endl;
  // clang-format on

  return 5;
}
