#include "GameLibrary.h"

Decrypter::PrivateKey::PrivateKey() :
	d(PRIVATE_KEY),
	n(PUBLIC_KEY_N) {

}

Decrypter::PrivateKey::~PrivateKey() {
	d = 0;
	n = 0;
}

Decrypter::Decrypter(string fileName) : 
	key() {
	if (input.is_open()) {
		input.close();
	}
	input.open(fileName, ios::binary);
}

Decrypter::~Decrypter() {
	if (input.is_open()) {
		input.close();
	}
}

int Decrypter::power(int a, int b) const {
	int ans = 1;
	while (b) {
		if (b & 1) ans = 1LL * ans * a % key.n;
		a = 1LL * a * a % key.n;
		b >>= 1;
	}
	return ans;
}

int Decrypter::decrypt(int data) const {
	return power(data, key.d);
}

int Decrypter::readInt() {
	int data = 0;
	input.read((char*)&data, sizeof(int));
	return decrypt(data);
}

char Decrypter::readChar() {
	return (char)readInt();
}

bool Decrypter::readBool() {
	return (bool)(readInt() - 10);
}
string Decrypter::readString() {
	// read string length
	int length = readInt();

	string data = "";
	while (length--) {
		data += readChar();
	}
	return data;
}

void Decrypter::readBoolArray(bool* data, int len) {
	for (int i = 0; i < len; i++) {
		data[i] = readBool();
	}
}