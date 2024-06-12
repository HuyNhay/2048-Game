#include "GameLibrary.h"

Encrypter::PublicKey::PublicKey() : 
	e(PUBLIC_KEY_E), 
	n(PUBLIC_KEY_N) {

}

Encrypter::PublicKey::~PublicKey() {
	e = 0;
	n = 0;
}

Encrypter::Encrypter(string fileName) : 
	key() {
	if (output.is_open()) {
		output.close();
	}
	output.open(fileName, ios::binary);
}

Encrypter::~Encrypter() {
	if (output.is_open()) {
		output.close();
	}
}

void Encrypter::openFile(string fileName) {
	if (output.is_open()) {
		output.close();
	}
	output.open(fileName, ios::binary);
}

int Encrypter::power(int a, int b) const {
	int ans = 1;
	while (b) {
		if (b & 1) ans = 1LL * ans * a % key.n;
		a = 1LL * a * a % key.n;
		b >>= 1;
	}
	return ans;
}

int Encrypter::encrypt(int data) const {
	return power(data, key.e);
}

void Encrypter::writeInt(int data) {
	data = encrypt(data);
	output.write((char*)&data, sizeof(int));
}

void Encrypter::writeBool(bool data){
	writeInt(((int)data) + 10);
}

void Encrypter::writeChar(char data) {
	writeInt((int)data);
}
void Encrypter::writeBoolArray(bool* data, int len) {
	for (int i = 0; i < len; i++) {
		writeBool(data[i]);
	}
}

void Encrypter::writeString(string data) {
	// write data's length
	int len = (int) data.length();
	writeInt(len);
	for (char c : data) {
		writeChar(c);
	}
}
