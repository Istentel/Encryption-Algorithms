#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#define BYTE 32

using namespace std;

string getText() {
	string p;
	cout << "Text: ";
	getline(cin, p);
	return p;
}

string getUserInputKey(string p) {
	string k;
	do {
		cout << "Key: ";
		getline(cin, k);
		if (k.length() != p.length()) {
			cout << "Key length must match text length.\n";
		}
	} while (k.length() != p.length());

	return k;
}

string getPseudorandomKey(int length) {
	srand(time(NULL));
	string key;

	for (int i = 0; i < length; i++) {
		key += char(rand() % 255);

	}

	return key;
}

vector<vector<int>> to_Byte(string str) {
	vector<vector<int>> byteText;
	for (int i = 0; i < str.length(); i++) {
		vector<int> b;
		int ch = (int)str[i];
		for (int j = 0; j < BYTE; j++) {
			b.push_back(ch % 2);
			ch /= 2;
		}
		reverse(b.begin(), b.end());
		byteText.push_back(b);
	}

	return byteText;
}

string binarToChar(const vector<vector<int>> t) {
	string textDecryptedStr;

	for (vector<int> j : t) {
		int bytesToAscii = 0;
		int ii = BYTE - 1;
		for (int i : j) {
			bytesToAscii += pow(2, ii--) * i;
		}
		textDecryptedStr += (char)bytesToAscii;
	}

	return textDecryptedStr;
}

vector<vector<int>> e(string p, string k) {
	vector<vector<int>> textEncrypted;
	vector<vector<int>> PB = to_Byte(p);
	vector<vector<int>> KB = to_Byte(k);

	for (int i = 0; i < PB.size(); i++) {
		vector<int> k;
		for (int j = 0; j < PB[0].size(); j++) {
			k.push_back(PB[i][j] ^ KB[i][j]);
		}
		textEncrypted.push_back(k);
	}

	return textEncrypted;
}

vector<vector<int>> d(vector<vector<int>> c, string k) {
	string textDecryptedStr;
	vector<vector<int>> textDecrypted;
	vector<vector<int>> KB = to_Byte(k);

	for (int i = 0; i < KB.size(); i++) {
		vector<int> k;
		for (int j = 0; j < KB[0].size(); j++) {
			k.push_back(c[i][j] ^ KB[i][j]);
		}
		textDecrypted.push_back(k);
	}

	return textDecrypted;
}

int main() {
	string P;
	string K;
	vector<vector<int>> textEncrypted;

	P = getText();
	K = getPseudorandomKey(P.length());

	textEncrypted = e(P, K);
	cout << "\nKey: " << K;
	cout << "\nText encrypted: " << binarToChar(textEncrypted) << "\n";
	cout << "Text decrypted: " << binarToChar(d(textEncrypted, K));
}
