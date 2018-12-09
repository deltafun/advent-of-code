#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

// For some reason equality - or something idk - doesn't work with MSVC. 
// It looks like it thinks that if I match "foo", then, when using an 
// sregex_iterator, any "foo" must be equal. This breaks std::distance. 
// They told me about using regex.
#include <boost/regex.hpp>

using Clock = std::chrono::high_resolution_clock;
using TimeStamp = std::array<int, 4>;

enum TimeStampIndex {
  Month, Day, Hour, Minute
};

enum Action {
  Start, Sleep, Wake
};

const std::unordered_map<std::string, Action> MatchToGuardAction = {
  {"Guard", Start}, {"falls", Sleep}, {"wakes", Wake}
};

struct GuardActivity {
  TimeStamp timeStamp;
  Action action;
  int guardId;
};

inline bool operator<(const GuardActivity& lhs, const GuardActivity& rhs) {
  return lhs.timeStamp < rhs.timeStamp;
}

inline bool operator==(const GuardActivity& lhs, const GuardActivity& rhs) {
  return lhs.timeStamp == rhs.timeStamp;
}

std::vector<GuardActivity> GetGuardActivity() {
  std::vector<GuardActivity> guards;
  guards.reserve(1098);

  std::ifstream inFile("../input/04.txt");
  std::string buf;

  boost::regex re("[A-Za-z0-9]+");

  while (getline(inFile, buf)) {
    GuardActivity guard;

    auto activityBegin = boost::sregex_iterator(buf.begin(), buf.end(), re);
    // idc about the year. Or the hour, but it's too late now whatever.
    std::advance(activityBegin, 1); 

    auto activityEnd = boost::sregex_iterator();

    for (auto it = activityBegin; it != activityEnd; ++it) {
      std::string match = it->str();
      int position = std::distance(activityBegin, it);

      if (position < guard.timeStamp.size()) {
        guard.timeStamp[position] = std::stoi(match);
      }
      else { // early exit
        guard.action = MatchToGuardAction.at(match);
        guard.guardId = guard.action == Start
          ? std::stoi((++it)->str())
          : -1;
        break;
      }
    }

    guards.emplace_back(guard);
  }

  std::sort(guards.begin(), guards.end());
  return guards;
}

std::pair<int, int> GetSleepiestGuard(const std::vector<GuardActivity>& guards) {
  std::unordered_map<int, int> guardIdToTimeSlept;

  int sleepiest = guards[0].guardId;
  int candidate = sleepiest;
  int startSleep = 0;

  for (auto it = guards.cbegin(); it != guards.cend(); ++it) {
    switch (it->action) {
      case Start: {
        candidate = it->guardId;
        if (guardIdToTimeSlept.find(it->guardId) == guardIdToTimeSlept.end()) {
          guardIdToTimeSlept[it->guardId] = 0;
        }
        break;
      }
      case Sleep: {
        startSleep = it->timeStamp[Minute];
        break;
      }
      case Wake: {
        guardIdToTimeSlept.at(candidate) += it->timeStamp[Minute] - startSleep;
        sleepiest =
          guardIdToTimeSlept.at(sleepiest) > guardIdToTimeSlept.at(candidate)
          ? sleepiest
          : candidate;
        break;
      }
    }
  }

  return { sleepiest, guardIdToTimeSlept.at(sleepiest) };
}

int GetSleepiestMinute(
  const int& sleepiestGuard,
  const std::vector<GuardActivity>& guards) {

  std::array<int, 60> minuteCount{ 0 };
  int currentGuard = guards[0].guardId;
  int startSleep = -1;

  for (auto it = guards.cbegin(); it != guards.cend(); ++it) {
    switch (it->action) {
      case Start: {
        currentGuard = it->guardId;
        break;
      }
      case Sleep: {
        startSleep = it->timeStamp[Minute];
        break;
      }
      case Wake: {
        if (currentGuard == sleepiestGuard) {
          for (int i = startSleep; i < it->timeStamp[Minute]; ++i)
            ++minuteCount[i];
        }
        break;
      }
    }
  }

  auto maxMinute = std::max_element(minuteCount.cbegin(), minuteCount.cend());
  int index = std::distance(minuteCount.cbegin(), maxMinute);

  return index;
}

std::tuple<int, int, int> GetSleepiestMinute(
  const std::vector<GuardActivity>& guards) {

  std::map<int, std::array<int, 60>> idToMinuteCount;

  int currentGuard = -1;
  int sleepStart = -1;

  for (auto it = guards.cbegin(); it != guards.cend(); ++it) {
    switch (it->action) {
      case Start: {
        currentGuard = it->guardId;

        if (idToMinuteCount.find(it->guardId) == idToMinuteCount.cend()) {
          idToMinuteCount[currentGuard] = std::array<int, 60>{0};
        }
      }
      case Sleep: {
        sleepStart = it->timeStamp[Minute];
      }
      case Wake: {
        auto& minuteCount = idToMinuteCount.at(currentGuard);

        for (int min = sleepStart; min < it->timeStamp[Minute]; ++min) {
          ++minuteCount[min];
        }
      }
    }
  }

  // count, min, id
  std::tuple<int, int, int> runningMax{ -1, -1, -1 };

  for (auto it = idToMinuteCount.cbegin(); it != idToMinuteCount.cend(); ++it) {
    auto max = std::max_element(it->second.cbegin(), it->second.cend());
    std::tuple<int, int, int> candidate =
      std::make_tuple(*max, max - it->second.cbegin(), it->first);

    runningMax = std::max(runningMax, candidate);
  }

  return runningMax;
}


int main() {
  auto start = Clock::now();

  auto guards = GetGuardActivity();
  auto parsed = Clock::now();

  // PART ONE
  auto sleepiestGuard = GetSleepiestGuard(guards);
  auto sleepiestMin = GetSleepiestMinute(sleepiestGuard.first, guards);
  auto partOne = Clock::now();

  // PART TWO
  // count, min, id
  auto anotherSleepiestMin = GetSleepiestMinute(guards);
  auto end = Clock::now();

  std::cout << "Guard #" << sleepiestGuard.first
    << " slept for " << sleepiestGuard.second << " min\n"
    << "Hash code: " << sleepiestGuard.first << " * " << sleepiestMin
    << " = " << sleepiestGuard.first * sleepiestMin << std::endl;

  std::cout << "Guard #" << std::get<2>(anotherSleepiestMin)
    << " slept at minute " << std::get<1>(anotherSleepiestMin)
    << " a total of " << std::get<0>(anotherSleepiestMin) << " times\n"
    << "Hash code: "
    << std::get<2>(anotherSleepiestMin) * std::get<1>(anotherSleepiestMin)
    << std::endl;

  std::cout << "Time: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(parsed - start).count()
    << " + "
    << std::chrono::duration_cast<std::chrono::milliseconds>(partOne - parsed).count()
    << " + "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - partOne).count()
    << " = "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    << " ms" << std::endl;

  getchar();
  return 3;
}
