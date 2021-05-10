#include <vector>

using namespace std;

template <typename T>
class Codex
{
  static inline int lastID = 0;

public:
  vector<T> entries;

  class ID
  {
    friend Codex;

    const int id;

    ID(int id) : id{id} {}
  };
  ID add(T item)
  {
    entries.push_back(item);
    return mint();
  }
  T &find(ID id)
  {
    return entries[static_cast<int>(id)];
  }
  T &findByName(string name)
  {
    return *find_if(entries.begin(), entries.end(), [&](auto f) { return f.name == name; });
  }
  static const ID mint()
  {
    return ID(++lastID);
  }
  static const ID none()
  {
    return ID(0);
  }
};