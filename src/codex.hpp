#pragma once

#include <vector>
#include <string>

using namespace std;

template <typename T>
class Codex
{
public:
    enum class ID {};

    vector<T> entries;
    ID lastID;

    Codex(): lastID{static_cast<ID>(0)} {}

    ID add(T item) {
        entries.push_back(item);
        lastID = static_cast<ID>(entries.size());
        return lastID;
    }

    T &find(ID id) {
        return entries[static_cast<int>(id)];
    }

    T find(string name) {
        return *find_if(entries.begin(), entries.end(), [&](auto f) { return f.name == name; });
    }
};