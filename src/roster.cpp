#include "roster.hpp"
#include <iostream>

void Stats::set(const sol::table &tbl) {
    cerr << "I'd like to set stats, but it's disabled" << endl;
}

void Stats::grow() {
    /*
    for (auto &i : ALL_STATS) {
        signed int growth = growths[static_cast<int>(i)];
        while (growth > 0) {
            int roll = rand() % MAX_GROWTH;
            if (roll < growth) {
                stats[static_cast<int>(i)]++;
            }
            growth -= roll;
        }
    }
     */
}

bool operator<(const Fighter &l, const Fighter &r) {
    return l.id < r.id;
}

void Roster::add(string name, const sol::table &stats) {
    auto fighter = new Fighter(size, name);
    fighter->stats.set(stats);
    fighters.insert(*fighter);
    size++;
}

const Fighter &Roster::get(string name) {
    return *find_if(fighters.begin(), fighters.end(), [&](auto f) { return f.name == name; });
}
