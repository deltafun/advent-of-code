#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <assert.h>
#include <set>
#include <chrono>

using namespace std;
using Clock = chrono::high_resolution_clock;

const string inputLoc = "../input/03.txt";

enum Ticket {
  TicketNum, X, Y, W, L
};

vector<int> GetParsedTicket(string ticket) {
  regex reg("[0-9]+");

  sregex_iterator next(ticket.begin(), ticket.end(), reg);
  sregex_iterator end;

  vector<int> parsedTicket;

  while (next != end) {
    smatch match = *next;
    parsedTicket.emplace_back(stoi(match.str()));
    ++next;
  }

  assert(parsedTicket.size() == 5);
  return parsedTicket;
}

int main() {
  auto start = Clock::now();

  ifstream inFile(inputLoc);
  string buf;

  vector<vector<vector<int>>> fabric(
    1000, vector<vector<int>>(1000, vector<int>()));

  while (getline(inFile, buf)) {
    auto xy = GetParsedTicket(buf);

    for (int i = xy[X]; i < xy[X] + xy[W]; ++i) {
      for (int j = xy[Y]; j < xy[Y] + xy[L]; ++j) {
        fabric[i][j].emplace_back(xy[TicketNum]);
      }
    }
  }

  int count = 0;
  set<int> nonoverlapClaimCandidates;

  for (int i = 0; i < fabric.size(); ++i) {
    for (int j = 0; j < fabric[0].size(); ++j) {
      if (fabric[i][j].size() == 1) {
        nonoverlapClaimCandidates.emplace(fabric[i][j][0]);
      }
    }
  }

  for (int i = 0; i < fabric.size(); ++i) {
    for (int j = 0; j < fabric[0].size(); ++j) {
      if (fabric[i][j].size() > 1) {
        ++count;
        for (auto& claim : fabric[i][j]) {
          nonoverlapClaimCandidates.erase(claim);
        }
      }
    }
  }

  assert(nonoverlapClaimCandidates.size() == 1);

  cout << "Part 1: " << count << endl;
  cout << "Part 2: " << *nonoverlapClaimCandidates.begin() << endl;

  auto end = Clock::now();
  cout 
    << "Time: "
    << chrono::duration_cast<chrono::seconds>(end - start).count()
    << " s" << endl;

  getchar();
  return 2;
}
