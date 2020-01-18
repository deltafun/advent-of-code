#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using Clock = std::chrono::high_resolution_clock;
const std::string Input = "../input/06.txt";
const std::string Input1 = "../input/06.debug.txt";

using ObjToOrbitMap = std::unordered_multimap<std::string, std::string>;

ObjToOrbitMap GetOrbits(const std::string& file)
{
  std::ifstream infile(file);
  std::string line;
  ObjToOrbitMap res;

  while (std::getline(infile, line))
  {
    std::istringstream ss{line};
    std::string token;
    std::pair<std::string, std::string> objToOrbiter;
    int ii = 0;

    while (std::getline(ss, token, ')'))
    {
      if (ii > 0)
        objToOrbiter.second = token;
      else
        objToOrbiter.first = token;

      ++ii;
    }

    res.emplace(objToOrbiter);
  }

  return res;
}

int CalculateOrbits(const ObjToOrbitMap& objToOrbits)
{
  // TODO: Maybe with BFS I can decrease the space req.
  using objToOrbitLevel = std::pair<std::string, int>;

  int res = 0;
  std::unordered_set<std::string> visited;
  std::stack<objToOrbitLevel> toVisit;

  auto comRange = objToOrbits.equal_range("COM");
  for (auto it = comRange.first; it != comRange.second; ++it)
    toVisit.emplace(it->second, 1);

  while (!toVisit.empty())
  {
    auto obj = toVisit.top();
    toVisit.pop();

    if (visited.contains(obj.first)) // keep backtracking
    {
      // TODO: Verify if we even need 'visited'.
      std::cout << "Visited " << obj.first << std::endl;
    }
    else // consider its orbit and try to move forward
    {
      res += obj.second;
      visited.emplace(obj.first);
      int orbits = obj.second + 1;

      auto objRange = objToOrbits.equal_range(obj.first);
      for (auto it = objRange.first; it != objRange.second; ++it)
        toVisit.emplace(it->second, orbits);
    }
  }

  return res;
}

int main()
{
  auto start = Clock::now();

  auto objsToOrbiter = GetOrbits(Input);
  int solone = CalculateOrbits(objsToOrbiter);

  auto partOne = Clock::now();

  auto end = Clock::now();

  std::cout << "Part One: " << solone << std::endl;
  std::cout << "Part Two: " << 0xDEADBEEF << std::endl;

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
