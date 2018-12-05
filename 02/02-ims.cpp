#include <vector>
#include <array>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

const string inputLoc = "../input/02.txt";

void PrintAnsOne() {
  ifstream inFile(inputLoc);
  string idBuf;

  if (!inFile) {
    cout << "FIXME";
    exit(1);
  }

  array<int, 26> letterCount{ 0 };
  int twos = 0;
  int threes = 0;

  while (getline(inFile, idBuf)) {
    bool foundTwo = false;
    bool foundThree = false;

    for (const char& c : idBuf) {
      ++letterCount[c - 'a'];
    }

    for (const int& x : letterCount) {
      if (!foundTwo && x == 2) {
        ++twos;
        foundTwo = true;
      }

      if (!foundThree && x == 3) {
        ++threes;
        foundThree = true;
      }
      
      if (foundTwo && foundThree) {
        break;
      }
    }

    letterCount.fill(0);
  }

  cout << "Uno: " << twos << " * " << threes << " = " << twos * threes << endl;
}

void PrintAnsTwo() {
  ifstream inFile(inputLoc);
  if (!inFile) {
    cout << "fixme";
    exit(1);
  }

  vector<string> ids;
  string idBuf;
  while (getline(inFile, idBuf)) {
    ids.emplace_back(idBuf);
  }
  
  // just check each id against every id after it
  for (auto it = ids.cbegin(); it != ids.cend(); ++it) {
    for (auto jt = next(it); jt != ids.cend(); ++jt) {
      
      int diffIndex = -1;

      // compare chars
      for (string::size_type i = 0; i < it->size(); ++i) {
        if ( (*it)[i] != (*jt)[i] ) {
          if (diffIndex >= 0) {
            diffIndex = -1;
            break;
          }

          diffIndex = i;
        }
      }

      if (diffIndex >= 0) {
        string theOne = *it;
        theOne.erase(theOne.begin() + diffIndex);
        
        cout << "Dos: " << *it << " \\cap " << *jt 
             << " = " << theOne << endl;
        return;
      }
    }
  }
}

int main() {
  PrintAnsOne();
  PrintAnsTwo();

  getchar();
  return 1;
}