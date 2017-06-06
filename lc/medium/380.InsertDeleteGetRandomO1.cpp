
#include <iostream>
#include <vector>
#include <functional>
#include <random>

using namespace std;

class RandomizedSet {
public:
  /** Initialize your data structure here. */
  RandomizedSet() : exist(2, false), values(2), population(0) {
    #ifdef DEBUG
    cout << "Initialize size : " << exist.size() << endl;;
    #endif
  }

  /** Inserts a value to the set. Returns true if the set did not already
   * contain the specified element. */
  bool insert(int val) {
    // check if time to expand
    size_t optimal_size = ceil(population * probe_factor + 1);
    if (exist.size() < optimal_size)
      rehash( optimal_size * 2 );

    // check if already exist
    size_t probe = hashing(val, exist.size());
    #ifdef DEBUG
    cout << "(probe is " << probe;
    #endif
    while ( exist[probe] && (values[probe] != val) )
      probe = ( probe + 1 ) % exist.size();
    #ifdef DEBUG
    cout << "->" << probe << ")";
    #endif
    if (exist[probe]) return false;

    // not exist, just put it
    values[probe] = val;
    exist[probe] = true;
    ++population;
    return true;
  }

  /** Removes a value from the set. Returns true if the set contained the
   * specified element. */
  bool remove(int val) {

    // check if not contains
    size_t probe = hashing(val, exist.size());
    #ifdef DEBUG
    cout << "(probe is " << probe;
    #endif
    while (exist[probe] && (values[probe]) != val)
      probe = ( probe + 1) % exist.size();
    #ifdef DEBUG
    cout << "->" << probe << ")";
    #endif
    if (!exist[probe]) return false;

    // remove the value
    exist[probe] = false;
    --population;

    // ajust (re-insert) the following probe
    probe = ( probe + 1 ) % exist.size();
    while (exist[probe])
    {
      exist[probe] = false;
      size_t reprobe = hashing(values[probe], exist.size());
      while (exist[reprobe]) reprobe = (reprobe+1) % exist.size();
      exist[reprobe] = true;
      values[reprobe] = values[probe];
      #ifdef DEBUG
        cout << "(mv " << values[probe] << " from p" << probe;
        cout << " to p" << reprobe << ")";
      #endif
      probe = (probe+1) % exist.size();
    }

    // check if it is time to shrink
    size_t optimal_size = ceil(population * probe_factor + 1);
    if (optimal_size < exist.size() / 4) rehash( exist.size() / 4 );

    return true;
  }

  /** Get a random element from the set. */
  int getRandom() {
    if (population == 0) throw runtime_error("The set is empty");
    size_t p = get_random(exist.size());
    while (!exist[p]) p = get_random(exist.size());
    return values[p];
  }

private:
    vector<bool> exist;
    vector<int> values;
    size_t population;
    float probe_factor = 2;

    void rehash(size_t new_size) {
        vector<bool> new_exist(new_size, false);
        vector<int> new_values(new_size);

        for (size_t p = 0; p < exist.size(); ++p)
            if (exist[p]) {
                int val = values[p];
                size_t probe = hashing(val, new_size);
                while (new_exist[probe % new_size]) ++probe;
                new_exist[probe] = true;
                new_values[probe] = val;
            }

        #ifdef DEBUG
        cout << "(Re-hashed size to " << new_size << ")";
        #endif

        this->exist = std::move(new_exist);
        this->values = std::move(new_values);
    }

    static size_t hashing(int val, size_t range) {
        // very naive
        // using std::hash ?
        return static_cast<unsigned int>(val) % range;
    }
    static size_t get_random(size_t range) {
      static std::default_random_engine generator;
      std::uniform_int_distribution<size_t> u_dist(0, range);
      return u_dist(generator);
    }
};



int main()
{
  RandomizedSet set;

  for (int i = 0; i < 100; ++i)
    cout << "insert " << i + 1000 << " : " << set.insert(i + 1000) << endl;

  for (int i = 0; i < 100; ++i)
    cout << "insert " << -(i + 1000) << " : " << set.insert(-i-1000) << endl;

  for (int i = 0; i < 100; ++i)
    cout << "remove " << i + 1000 << " : " << set.remove(i + 1000) << endl;

  return 0;
}
