#include <string>
#include <set>
#include <array>

using namespace std;

enum Stat
{
  S_Force = 0,
  S_Precision,
  S_Agility,
  S_Intellect,
  S_Courage,
  S_Luck,
  LAST_STAT,
};

const int MAX_GROWTH = 20;

class Stats
{
  std::array<int, LAST_STAT> stats;
  std::array<int, LAST_STAT> growths;

public:
  Stats() : stats{{0, 0, 0, 0, 0, 0}}, growths{{0, 0, 0, 0, 0, 0}} {}

  void setStat(Stat stat, int val)
  {
    stats[stat] = val;
  }

  void grow()
  {
    for (int i = 0; i < LAST_STAT; i++)
    {
      signed int growth = growths[i];
      while (growth > 0)
      {
        int roll = rand() % MAX_GROWTH;
        if (roll < growth)
        {
          stats[i]++;
        }
        growth -= roll;
      }
    }
  }
};

class Fighter
{
  int id;
  string name;
  Stats stats;

public:
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

  void add(string name)
  {
    fighters.insert(Fighter(size, name));
    size++;
  }
};