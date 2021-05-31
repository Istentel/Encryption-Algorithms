#include <iostream>
#include <vector>
#include <string>

#define BYTELENGTH 32
#define SIZE 1024 //number of pseudo random numbers multiplied by BYTELENGTH

using namespace std;

//a function to convert integers to bytes
vector<vector<bool>> intToBytes(vector<unsigned int> seed) {
	vector<vector<bool>> bytes;

	for (auto n : seed) {
		vector<bool> byte;
		unsigned int nr = n;
		for (int i = 0; i < BYTELENGTH; i++) {
			byte.push_back(nr % 2);
			nr /= 2;
		}
		reverse(byte.begin(), byte.end());
		bytes.push_back(byte);
	}

	return bytes;
}

vector<vector<bool>> lfsr(vector<unsigned int> seed) {
	//converting seed ints to bytes
	vector<vector<bool>> seedToBytes = intToBytes(seed);

	for (int i = 0; i < seedToBytes.size(); i++) {
		vector<bool> byte;
		//last bit of the seed 
		bool lastBit = seedToBytes[seedToBytes.size() - 1][seedToBytes[0].size() - 1];
		for (int j = 0; j < seedToBytes[0].size(); j++) {
			//xor between first and last bits of the seed
			bool bit = seedToBytes[i][j] ^ lastBit;
			byte.push_back(bit);
			//last bit is now the bit just created 
			lastBit = bit;
		}
		seedToBytes.push_back(byte);
		//stopping point
		if (seedToBytes.size() * seedToBytes[0].size() >= SIZE) break;
	}

	return seedToBytes;
}

vector<unsigned int> bytesToInt(vector<vector<bool>> bytes) {
	vector<unsigned int> numbers;
	int size = SIZE / BYTELENGTH;

	for (int i = 0; i < size; i++) {
		unsigned int nr = 0;
		int k = 1;
		for (int j = 0; j < BYTELENGTH; j++) {
			if (bytes[i][j])
				nr += bytes[i][j] * pow(2, BYTELENGTH - k);
			k++;
		}
		numbers.push_back(nr);
	}

	return numbers;
}

void print(vector<vector<bool>> v) {
	for (auto i : v) {
		for (bool j : i) {
			cout << j << " ";
		}
		cout << "\n";
	}
}

void print(vector<unsigned int> v) {
	for (unsigned int i : v) {
		cout << i << " ";
	}
}

int main() {
	vector<unsigned int> seed = { 149837465, 575678, 9873383, 758698354 };

	cout << "Seed bytes:\n";
	print(intToBytes(seed));
	cout << "\nPseudo Random Bytes:\n";
	vector<vector<bool>> pseudoRandomBytes = lfsr(seed);
	print(pseudoRandomBytes);
	cout << "\nPseudo Random Numbers:\n";
	print(bytesToInt(pseudoRandomBytes));
}