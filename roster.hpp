#include <string>
#include <set>
#include <array>
#include "sol/sol.hpp"

using namespace std;

enum class Stat
{
  Force = 0,
  Precision,
  Agility,
  Intellect,
  Courage,
  Luck,
  LAST,
};
const size_t LAST_STAT = 6;
const std::array<Stat, LAST_STAT> ALL_STATS = {Stat::Force, Stat::Precision, Stat::Agility, Stat::Intellect, Stat::Courage, Stat::Luck};
const std::array<string, LAST_STAT> STAT_NAMES = {"force", "precision", "agility", "intellect", "courage", "luck"};
const int MAX_GROWTH = 20;

class Stats
{
  std::array<int, LAST_STAT> stats;
  std::array<int, LAST_STAT> growths;

public:
  Stats() : stats{{0, 0, 0, 0, 0, 0}}, growths{{0, 0, 0, 0, 0, 0}} {}

  void set(Stat stat, int val)
  {
    stats[static_cast<int>(stat)] = val;
  }

  void set(const sol::table &tbl)
  {
    for (auto &stat : ALL_STATS)
    {
      auto name = STAT_NAMES[static_cast<int>(stat)];
      sol::optional<int> val = tbl[name];
      if (val != sol::nullopt)
      {
        set(stat, val.value());
      }
    }
  }

  void grow()
  {
    for (auto &i : ALL_STATS)
    {
      signed int growth = growths[static_cast<int>(i)];
      while (growth > 0)
      {
        int roll = rand() % MAX_GROWTH;
        if (roll < growth)
        {
          stats[static_cast<int>(i)]++;
        }
        growth -= roll;
      }
    }
  }
};

class Fighter
{
public:
  const int id;
  const string name;
  Stats stats;

  Fighter(int id, string name) : id{id}, name{name} {}
  friend bool operator<(const Fighter &l, const Fighter &r);
};

bool operator<(const Fighter &l, const Fighter &r)
{
  return l.id < r.id;
}

class Roster
{
  int size;
  set<Fighter> fighters;

public:
  void add(string name, const sol::table &stats)
  {
    auto fighter = new Fighter(size, name);
    fighter->stats.set(stats);
    fighters.insert(*fighter);
    size++;
  }

  const Fighter &get(string name)
  {
    return *find_if(fighters.begin(), fighters.end(), [&](auto f) { return f.name == name; });
  }
};