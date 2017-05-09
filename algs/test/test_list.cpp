// Test list.hpp

#include <collections/list.hpp>

#include <string>
#include <iostream>

using namespace std;
using namespace algs;

int main()
{
  List<string> list;
  cout << "created an empty list: " << list << endl;

  string smith("AgentSmith");

  list.push_back("Miku");
  cout << "pushed Miku back: " << list << endl;
  list.push_back("John");
  cout << "pushed John back: " << list << endl;
  list.push_front("Lily");
  cout << "pushed Lily front: " << list << endl;
  list.push_front("Magna");
  cout << "pushed Magna front: " << list << endl;

  cout << "try to iterate: " << endl;
  int count = 0;
  for(const string& s : list) {
    ++count;
    cout << count << " : " << s << endl;
  }

  cout << "try to insert after Lily : " << endl;
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
