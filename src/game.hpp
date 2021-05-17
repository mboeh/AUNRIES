#pragma once

#include "codex.hpp"
#include "roster.hpp"
#include <fstream>
#include <iostream>

class Game {
public:
    Roster roster;
    sol::state lua;
    sol::table config;

    void load();

    template<typename T>
    T fennel_eval(string filename) {
        std::cerr << "loading source (" << filename << ")" << std::endl;

        sol::table fnl = lua["fennel"];
        sol::function fnl_eval = fnl["eval"];
        sol::table opts = lua.create_table_with("filename", filename);

        ifstream f(filename);
        stringstream buf;
        buf << f.rdbuf();

        T result = fnl_eval(buf.str(), opts);
        return result;
    }

    void fennel_load(string filename) {
        fennel_eval<sol::object>(std::move(filename));
    }
};