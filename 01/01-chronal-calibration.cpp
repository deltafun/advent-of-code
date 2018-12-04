#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

vector<int> GetFrequencies() {
	ifstream infile("../input/01.txt");
	string buf;
	vector<int> freqs;

	if (!infile) {
		cout << "Can't read input";
		exit(1);
	}

	while (getline(infile, buf)) {
		freqs.emplace_back(stoi(buf));
	}

	return freqs;
}

void AccioAberration(const vector<int>& freqs) {
	unordered_set<int> seen;
	int sum = 0;
	seen.emplace(0);

	while (true) {
		for (const int& x : freqs) {
			sum += x;
			auto isEmplaced = seen.emplace(sum);
			
			if (!isEmplaced.second) {
				cout << sum << endl;
				return;
			}
		}
	}
}

int main() {
	AccioAberration(GetFrequencies());

	getchar();
	return 0;
}                                                                              