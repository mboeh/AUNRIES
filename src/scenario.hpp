#pragma once
#include <string>
#include <map>
#include "sol/sol.hpp"

class Scenario {
public:
    class Encounter {
    public:
        std::string title;
        std::string map;

        explicit Encounter(const sol::table& tbl) {
            title = tbl["title"];
            map = tbl["map"];
        }
    };
    std::string title;
    std::string firstEncounter;
    std::map<std::string, Encounter> encounters;

    explicit Scenario(const sol::table& tbl) {
        title = tbl["title"];
        firstEncounter = tbl["firstEncounter"];
        tbl.get<sol::table>("encounters").for_each([&](sol::object const& key, sol::object const& value){
            std::string n = key.as<std::string>();
            sol::table tbl = value.as<sol::table>();
            encounters.try_emplace(n, tbl);
        });
    }

    const Encounter& currentEncounter() {
        auto i = encounters.find(firstEncounter);
        if (i != encounters.end()) {
            return i->second;
        } else {
            throw "shit";
        }
    }
};