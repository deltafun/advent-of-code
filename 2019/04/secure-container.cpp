#include <chrono>
#include <fstream>
#include <iostream>

using Clock = std::chrono::high_resolution_clock;
// const std::string Input = "../input/04.txt";

using CodeRange = std::pair<int, int>;
const CodeRange Input{ 108457, 562041 };

// Number of codes that have the following property:
//  (a) Each digit is monotonically increasing
//  (b) There exists a pair of consecutive digits
//
// Eg: 112, 12334
int CalculateCodes(const CodeRange& codes)
{
  int res = 0;

  for (int ii = codes.first; ii <= codes.second; ++ii)
  {
    bool hasPair = false;
    bool itsGood = true;
    int prev = 0;

    for (const auto& c : std::to_string(ii))
    {
      int digit = c - '0';
      hasPair |= digit == prev;
      if (digit < prev)
      {
        itsGood = false;
        break;
      }
      prev = digit;
    }

    res += hasPair && itsGood;
  }

  return res;
}

int CalculateComplicatedCodes(const CodeRange& codes)
{
  int res = 0;

  for (int ii = codes.first; ii <= codes.second; ++ii)
  {
    bool itsGood          = true;
    bool hasPair          = false;
    int prev              = 0;
    int consecutiveDigits = 0;
    std::string number{ std::to_string(ii) };

    for (int jj = 0; jj < number.size(); ++jj)
    {
      int digit = number[jj] - '0';
      bool isPair = prev == digit;

      hasPair |= !isPair && consecutiveDigits == 1;
      consecutiveDigits = isPair ? consecutiveDigits + 1 : 0;

      if (digit < prev)
      {
        itsGood = false;
        break;
      }

      prev = digit;
    }

    hasPair |= consecutiveDigits == 1;

    res += hasPair && itsGood;
  }

  return res;
}

int main()
{
  auto start = Clock::now();

  auto solone = CalculateCodes(Input);

  auto partOne = Clock::now();

  auto soltwo = CalculateComplicatedCodes(Input);

  auto end = Clock::now();

  std::cout << "Part One: " << solone << std::endl;
  std::cout << "Part Two: " << soltwo << std::endl;

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
