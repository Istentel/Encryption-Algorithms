#include <iostream>
#include <string>
#include <vector>

//Cifrul Vigenere

using namespace std;

string getRidOfSpaces(string t) {
	string newStr;
	for (char c : t) {
		if (c != ' ')
			newStr += c;
	}

	return newStr;
}

string getText() {
	string text;
	do {
		cout << "Text: ";
		getline(cin, text);
	} while (text.length() <= 1);

	return getRidOfSpaces(text);
}

string getKey() {
	string key;
	do {
		cout << "Key: ";
		getline(cin, key);
	} while (key.length() <= 1);

	return getRidOfSpaces(key);
}

vector<vector<char>> getMatrix(string key) {
	vector<vector<char>> m;

	for (int i = 0; i < key.length(); i++) {
		vector<char> row;
		row.push_back(key[i]);
		int k = 0;
		for (int j = 1; j < 26; j++) {
			char c = char(key[i] + j);
			
			if (c > 122 || c < 97)
				c = char(97 + k++);

			row.push_back(c);
		}
		m.push_back(row);
	}

	return m;
}

int getCode(char c) {
	if (isupper(c))
		return int(c - 'A');
	else
		return int(c - 'a');
}

string e(string p, string k) {
	vector<vector<char>> m = getMatrix(k);
	string encryptedText;
	int kl = k.length();

	for (int i = 0; i < p.length(); i++) {
		encryptedText += m[i % kl][getCode(p[i])];
	}

	return encryptedText;
}

int findChar(char c, int x, vector<vector<char>> m) {
	for (int i = 0; i < m[0].size(); i++) {
		if (m[x][i] == c) return i;
	}

	return -1;
}

string d(string c, string k) {
	vector<vector<char>> m = getMatrix(k);
	string decryptText;
	int kl = k.length();

	for (int i = 0; i < c.length(); i++) {
		decryptText += char(findChar(c[i], i % kl , m) + 'a');
	}

	return decryptText;
}

void print(vector<vector<char>> m) {
	for (auto i : m) {
		for (char j : i) {
			cout << j << " ";
		}
		cout << "\n";
	}
}

int main() {
	string P;
	string K;
	vector<vector<char>> m;

	P = getText();
	K = getKey();
	m = getMatrix(K);

	print(m);

	string te = e(P, K);

	cout << "Text encrypted: " << te << "\n";
	cout << "Text decrypted: " << d(te, K);
}