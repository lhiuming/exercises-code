// Test list.hpp

#include <fundamentals/list.hpp>

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
  list.push_back("Miku");
  cout << "pushed Miku back: " << list << endl;
  list.push_back("John");
  cout << "pushed John back: " << list << endl;
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
  list.push_back(smith); list.push_front(smith);
  cout << list << endl;

  cout << "Kill the smith after LilyLover: ";
  for(auto i = list.begin(); i != list.end(); ++i)
    if (*i == "LilyLover") list.erase_after(i);
  cout << list << endl;

  return 0;
}
