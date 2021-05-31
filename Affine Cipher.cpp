#include <iostream>
#include <string>

using namespace std;

typedef struct key {
	int a;
	int b;
}key;

const int m = 26;

int cmmdc(int a, int b) {
	while (a != b) {
		if (a > b)
			a -= b;
		else
			b -= a;
	}

	return a;
}

int simetric(const key k) {
	int a_inv = k.a;
	while (true) {
		a_inv++;
		if ((k.a * a_inv % 26) == 1)
			break;
	}

	return a_inv;
}

string citire() {
	string text;
	cout << "Introduceti textul: ";
	getline(cin, text);
	return text;
}

key citireCheie() {
	key k;
	do {
		cout << "Introduceti a: ";
		cin >> k.a;
		cout << "Introduceti b: ";
		cin >> k.b;
		if (cmmdc(k.a, m) != 1) {
			cout << "a trebuie sa fie prim cu 26!\n";
		}
	} while (cmmdc(k.a, m) != 1);
	
	return k;
}

string e(const string p,const key k) {
	string textEncrypted;

	for (int i = 0; i < p.length(); i++) {
		if (p[i] != ' ') {
			int ch = (int)p[i];

			if (p[i] >= 'a' && p[i] <= 'z')
				ch -= (int)'a';
			else if (p[i] >= 'A' && p[i] <= 'Z')
				ch -= (int)'A';
			else {
				textEncrypted += p[i];
				continue;
			}

			int ind = (k.a * ch + k.b) % m;
			textEncrypted += char(ind + ((int)p[i] >= (int)'a' && (int)p[i] <= (int)'z' ? (int)'a' : (int)'A'));
		}
		else
			textEncrypted += p[i];
	}

	return textEncrypted;
}

string d(string c, key k) {
	string textDecrypted;
	int a_inv = simetric(k);

	for (int i = 0; i < c.length(); i++) {
		if (c[i] != ' ') {
			int ch = (int)c[i];

			if (c[i] >= 'a' && c[i] <= 'z')
				ch -= (int)'a';
			else if (c[i] >= 'A' && c[i] <= 'Z')
				ch -= (int)'A';
			else {
				textDecrypted += c[i];
				continue;
			}

			int ind = (a_inv * (ch - k.b)) % m;
			if (ind < 0) ind += m;
			textDecrypted += (char)(ind + ((int)c[i] >= (int)'a' && (int)c[i] <= (int)'z' ? (int)'a' : (int)'A'));
		}
		else
			textDecrypted += c[i];
	}

	return textDecrypted;
}

int main() {
	string P;
	key K;

	P = citire();
	K = citireCheie();

	string textEncrypted = e(P, K);
	cout << textEncrypted << "\n";
	cout << d(textEncrypted, K) << "\n";


}