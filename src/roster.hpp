#pragma once

#include <string>
#include <set>
#include <array>
#include <utility>

#include "sol/sol.hpp"

using namespace std;

class Stats {

public:
    Stats() {}

    void set(const sol::table &tbl);

    void grow();
};

class Fighter {
public:
    const int id;
    const string name;
    Stats stats;

    Fighter(int id, string name) : id{id}, name{std::move(name)} {}

    friend bool operator<(const Fighter &l, const Fighter &r);
};

bool operator<(const Fighter &l, const Fighter &r);

class Roster {
    int size;
    set<Fighter> fighters;

public:
    void add(string name, const sol::table &stats);

    const Fighter &get(string name);
};