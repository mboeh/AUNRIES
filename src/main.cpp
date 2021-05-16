#include <raylib.h>
#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>

#include "sol/sol.hpp"
#include "game.hpp"
#include "asset_loader.hpp"
#include "tiled.hpp"
#include "map_scene.hpp"

template<typename T>
T fennel_eval(sol::state &lua, string filename) {
    cerr << "loading source (" << filename << ")" << endl;

    sol::table fnl = lua["fennel"];
    sol::function fnl_eval = fnl["eval"];
    sol::table opts = lua.create_table_with("filename", filename);

    ifstream f(filename);
    stringstream buf;
    buf << f.rdbuf();

    T result = fnl_eval(buf.str(), opts);
    return result;
}

void fennel_load(sol::state &lua, string filename) {
    fennel_eval<sol::object>(lua, std::move(filename));
}

int main() {
    auto game = make_shared<Game>();
    auto assets = make_shared<AssetLoader>(game);
    auto tiled = make_shared<TiledLoader>();
    MapScene scene(assets, tiled);

    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::coroutine, sol::lib::string, sol::lib::package, sol::lib::table,
                       sol::lib::math);

    cerr << "loading fennel" << endl;
    lua.require_file("fennel", "vendor/fennel.lua");
    cerr << "loading lume" << endl;
    lua.require_file("lume", "vendor/lume.lua");

    cerr << "loading config" << endl;
    auto config = fennel_eval<sol::table>(lua, "script/config.fnl");

    cerr << "configuring lua environment" << endl;
    sol::usertype<Roster> roster_type = lua.new_usertype<Roster>("Roster");
    roster_type["add"] = &Roster::add;
    roster_type["get"] = &Roster::get;
    lua["roster"] = game->roster;

    sol::usertype<Fighter> fighter_type = lua.new_usertype<Fighter>("Fighter");
    fighter_type["name"] = &Fighter::name;

    fennel_load(lua, "script/roster.fnl");

    int screenw = config.get_or("width", 300);
    int screenh = config.get_or("height", 300);

    InitWindow(screenw, screenh, config.get<string>("title").c_str());

    scene.makeImage(screenw/2, screenh/2);
    scene.loadMap(config.get<string>("firstMap"));
    scene.draw();

    Texture2D tex = LoadTextureFromImage(*scene.getScreen());

    SetTextureFilter(tex, FILTER_POINT);

    while (!WindowShouldClose()) {
        if (scene.draw()) {
            UnloadTexture(tex);
            tex = LoadTextureFromImage(*scene.getScreen());
            SetTextureFilter(tex, FILTER_POINT);
        }
        BeginDrawing();
        DrawTextureEx(tex, Vector2{0, 0}, 0.0, 2.0, WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}