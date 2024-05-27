#include "GameLibrary.h"

void removeSpaces(string& name) {
    // remove head and tail spaces
    if (name == "") return;

    if (name[0] != ' ' && name[name.size() - 1] != ' ') {
        return;
    }

    int first = 0;
    while (name[first] == ' ') {
        first++;
    }

    if (first == (int)name.size()) {
        name = "";
        return;
    }

    int last = (int)name.size() - 1;
    while (name[last] == ' ') {
        last--;
    }

    name = name.substr(first, last - first + 1);

    // remove middle spaces
    string s = "";
    for (int i = 0; i < (int)name.size(); i++) {
        if (name[i] == ' ' && s.back() == ' ') continue;
        s = s + name[i];
    }
    name = s;
}

int numberLength(int num) {
    return to_string(num).length();
}