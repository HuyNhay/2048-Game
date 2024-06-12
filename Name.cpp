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
    return (int)to_string(num).length();
}

bool checkInvalidCharacter(string name) {
    for (char c : name) {
        if (c == ' ') continue;
        if (c >= 'a' && c <= 'z') continue;
        if (c >= 'A' && c <= 'Z') continue;
        if (c >= '1' && c <= '9') continue;
        //cout << c << endl;
        //system("pause");
        return true;
    }
    return false;
}

bool checkNameExistence(List<Player>* rankings, string name) {
    for (
        Node<Player>* curNode = rankings->head;
        curNode != nullptr;
        curNode = curNode->next
        ) {
        if (curNode->data.name == name) {
            return true;
        }
    }
    return false;
}