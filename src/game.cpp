#include "game.hpp"

void Game::load() {
    lua.open_libraries(sol::lib::base, sol::lib::coroutine, sol::lib::string, sol::lib::package, sol::lib::table,
                       sol::lib::math);

    cerr << "loading fennel" << endl;
    lua.require_file("fennel", "vendor/fennel.lua");
    cerr << "loading lume" << endl;
    lua.require_file("lume", "vendor/lume.lua");
    cerr << "loading config" << endl;
    config = fennel_eval<sol::table>("script/config.fnl");
    cerr << "loading scenario" << endl;
    scenario = Scenario(fennel_eval<sol::table>("script/" + config.get_or<std::string>("loadScenario", "scenario.fnl")));

    cerr << "configuring lua environment" << endl;
    sol::usertype<Roster> roster_type = lua.new_usertype<Roster>("Roster");
    roster_type["add"] = &Roster::add;
    roster_type["get"] = &Roster::get;
    lua["roster"] = roster;

    sol::usertype<Fighter> fighter_type = lua.new_usertype<Fighter>("Fighter");
    fighter_type["name"] = &Fighter::name;

    fennel_load("script/roster.fnl");
}