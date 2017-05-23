// Test list.hpp

#include <fundamentals/list.hpp>
#include <sorting.hpp>
#include <utils.hpp>

#include <string>
#include <iostream>

using namespace std;
using namespace algs;

int main()
{
  List<string> list;
  cout << "created an empty list: " << list << endl;

  cout << "-- try putting things --" << endl;
  string smith("AgentSmith");
  list.push_front("Miku");
  cout << "pushed Miku front: " << list << endl;
  list.push_front("John");
  cout << "pushed John front: " << list << endl;
  list.push_front("Lily");
  cout << "pushed Lily front: " << list << endl;
  list.push_front("Magna");
  cout << "pushed Magna front: " << list << endl;

  cout << "-- try iterating -- " << endl;
  int count = 0;
  const List<string>& rlist = list;
  for(const string& s : rlist) {
    ++count;
    cout << count << " : " << s << endl;
  }

  // check all iterator operations
  auto b = list.begin(), a = b++;
  cout << "*a: " << *a << endl;
  cout << "*b: " << *b << endl;
  cout << "a != b: " << (a != b) << endl;
  cout << "*a++: " << *a++ << endl;
  cout << "a == b: " << (a == b) << endl;

  cout << "-- try to modifying after Lily --" << endl;
  cout << "Insert after lily: ";
  for(auto i = list.begin(); i != list.end(); ++i)
    if (*i == "Lily") {
      list.insert_after(i, smith);
      list.insert_after(i, "LilyLover");
    }
  cout << list << endl;

  cout << "Get smiths around: ";
  list.push_front(smith);
  cout << list << endl;

  cout << "Kill the smith after LilyLover: ";
  for(auto i = list.begin(); i != list.end(); ++i)
    if (*i == "LilyLover") list.erase_after(i);
  cout << list << endl;

  cout << "-- try to merge and sort --" << endl;
  List<int> l1, l2;
  vector<int> ran;
  Random::uniform(ran, 20, 5);
  for (int i : ran) l1.push_front(i);
  ran.clear();
  Random::uniform(ran, 20, 8);
  for (int i : ran) l2.push_front(i);
  cout << "l2: " << l2 << endl;
  cout << "l1: " << l1 << endl;
  l1.sort();
  cout << "sorted l1: " << l1 << endl;

  return 0;
}
