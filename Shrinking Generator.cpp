#include <iostream>	
#include <vector>
#include <string>

#define BYTELENGTH 8
#define SIZE 256

using namespace std;

vector<string> getSeeds() {
	vector<string> seeds;
	string s1, s2;

	cout << "Seed1: ";
	getline(cin, s1);
	cout << "Seed2: ";
	getline(cin, s2);

	seeds.push_back(s1);
	seeds.push_back(s2);

	return seeds;
}

vector<vector<bool>> stringToBytes(string s) {
	vector<vector<bool>> bytes;

	for (char c : s) {
		vector<bool> byte;
		int ch = (int)c;
		for (int i = 0; i < BYTELENGTH; i++) {
			byte.push_back(ch % 2);
			ch /= 2;
		}
		reverse(byte.begin(), byte.end());
		bytes.push_back(byte);
	}

	return bytes;
}

vector<vector<bool>> lfsr(string seed) {
	vector<vector<bool>> seedToBytes = stringToBytes(seed);

	for (int i = 0; i < seedToBytes.size(); i++) {
		vector<bool> byte;
		bool lastBit = seedToBytes[seedToBytes.size() - 1][seedToBytes[0].size() - 1];
		for (int j = 0; j < seedToBytes[0].size(); j++) {
			bool bit = seedToBytes[i][j] ^ lastBit;
			byte.push_back(bit);
			lastBit = bit;
		}
		seedToBytes.push_back(byte);
		if (seedToBytes.size() * seedToBytes[0].size() >= SIZE) break;
	}

	return seedToBytes;
}

vector<vector<bool>> shrinkingGenerator(string s1, string s2) {
	vector<vector<bool>> shrinkedNumbers;
	//converting seed to bytes
	vector<vector<bool>> seed1 = lfsr(s1);
	vector<vector<bool>> seed2 = lfsr(s2);
	vector<bool> row;

	for (int i = 0; i < SIZE / BYTELENGTH; i++) {
		for (int j = 0; j < BYTELENGTH; j++) {
			// if the bit of seed1 is true add the bit the seed2 to the row
			if (seed1[i][j]) {
				row.push_back(seed2[i][j]);
			}

			//once row size is equal to BYTHLENGTH add it to the shrinkedNumbers
			if (row.size() == BYTELENGTH) {
				shrinkedNumbers.push_back(row);
				//clear older bits
				row.clear();
			}
		}
		
	}
	shrinkedNumbers.push_back(row);

	return shrinkedNumbers;
}

vector<vector<bool>> selfShrinkingGenerator(string s) {
	vector<vector<bool>> shrinkedNumbers;
	vector<vector<bool>> seed = lfsr(s);
	vector<bool> row;
	int seedSize = seed.size();

	//looping through half of the bits in the seed
	for (int i = 0; i < seedSize / 2; i++) {
		for (int j = 0; j < BYTELENGTH; j++) {
			//if bit in the first half is true add the correspondent bit in the second half 
			if (seed[i][j]) {
				row.push_back(seed[(seedSize / 2) + i][j]);
			}

			//once row size is equal to BYTELENGTH add it to the shrinkedNumbers
			if (row.size() == BYTELENGTH) {
				shrinkedNumbers.push_back(row);
				//clear older bits
				row.clear();
			}
		}
	}
	shrinkedNumbers.push_back(row);

	return shrinkedNumbers;
}

void print(vector<vector<bool>> v) {
	for (auto i : v) {
		for (int j : i) {
			cout << j << " ";
		}
		cout << "\n";
	}
}

int main() {
	vector<string> seeds;
	seeds = getSeeds();

	cout << "\nSeed1:\n";
	print(stringToBytes(seeds[0]));
	cout << "\nSeed2:\n";
	print(stringToBytes(seeds[1]));
	cout << "\n\n";

	cout << "Shrinking Generator: \n";
	print(shrinkingGenerator(seeds[0], seeds[1]));
	cout << "\n\n";

	cout << "Self-Shrinking Generator: \n";
	print(selfShrinkingGenerator(seeds[0]));
}