#include "priorityQueue.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

Entry queue[MAX_ENTRIES];
int queueSize = 0;

int getPriority(const string& category) {
    if (category == "parent") return 1;
    if (category == "teacher") return 2;
    if (category == "student") return 3;
    return -1;
}

void enqueue(const string& category, const string& name) {
    int priority = getPriority(category);
    if (priority == -1) return;

    Entry newEntry = { priority, name, category };

    int i;
    for (i = queueSize - 1; (i >= 0 && queue[i].priority > newEntry.priority); i--) {
        queue[i + 1] = queue[i];
    }
    queue[i + 1] = newEntry;
    queueSize++;
}

void processQueue() {
    cout << "===============================" << endl;
    cout << "         Priority Queue        " << endl;
    cout << "===============================" << endl;
    cout << left << setw(10) << "Name" << " | " << left << setw(10) << "Category" << endl;
    cout << "-------------------------------" << endl;

    for (int i = 0; i < queueSize; i++) {
        cout << left << setw(10) << queue[i].name
            << " | " << (queue[i].category == "parent" ? "Parent" :
                queue[i].category == "teacher" ? "Teacher" : "Student") << endl;
    }
    cout << "===============================" << endl;
}

void loadEntries(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        string category;
        string name;
        bool foundColon = false;

        for (char c : line) {
            if (c == ':') {
                foundColon = true;
                continue;
            }
            if (!foundColon) {
                category += c;
            }
            else {
                name += c;
            }
        }

        while (!category.empty() && category[0] == ' ') {
            category.erase(0, 1);
        }

        while (!name.empty() && name[0] == ' ') {
            name.erase(0, 1);
        }
        while (!name.empty() && name[name.size() - 1] == ' ') {
            name.erase(name.size() - 1);
        }

        enqueue(category, name);
    }
}

int main() {
    loadEntries("entries.txt");
    processQueue();
    return 0;
}
