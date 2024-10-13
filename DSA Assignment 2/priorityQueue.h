#pragma once

#include <string>
using namespace std;

const int MAX_ENTRIES = 100;
struct Entry {
    int priority;
    string name;
    string category; 
};

int getPriority(const string& category);
void enqueue(const string& category, const string& name);
void processQueue();
void loadEntries(const string& filePath);
