#include <raylib.h>
#include <iostream>
#include <fstream>
#include <utility>

#include "sol/sol.hpp"
#include "game.hpp"
#include "asset_loader.hpp"
#include "map_loader.hpp"

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
    AssetLoader assets(game);
    MapLoader maps;

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

    maps.loadTilemap("basic_map");
    maps.loadTileset("oryx_fan");
    maps.loadTileset("colors");

    InitWindow(config.get_or("width", 300), config.get_or("height", 300), config.get<string>("title").c_str());

    assets.preload();

    Image screen = GenImageColor(240, 240, WHITE);
//
//    ImageDraw(&screen, wall, Rectangle{0, 0, 24, 24}, Rectangle{0, 0, 24, 24}, WHITE);
//    ImageDraw(&screen, wall, Rectangle{0, 0, 24, 24}, Rectangle{24, 0, 24, 24}, WHITE);
//    ImageDraw(&screen, wall, Rectangle{0, 0, 24, 24}, Rectangle{0, 24, 24, 24}, WHITE);
//    ImageDraw(&screen, grass, Rectangle{0, 0, 24, 24}, Rectangle{24, 24, 24, 24}, WHITE);

    Texture2D tex = LoadTextureFromImage(screen);
    UnloadImage(screen);

    SetTextureFilter(tex, FILTER_POINT);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureEx(tex, Vector2{0, 0}, 0.0, 2.0, WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}