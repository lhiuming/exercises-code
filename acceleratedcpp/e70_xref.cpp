#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "split.h"

using std::cout;
using std::cin;
using std::endl;
using std::istream;
using std::string;
using std::vector;
using std::map;
using std::pair;

map< string, vector<int> >
xref(istream& in, vector<string> find_words(const string&) = split) // default
{
  string line;
  int line_number = 0;
  map< string, vector<int> > ret;

  while (getline(in, line)) {
    ++line_number;

    vector<string> words = find_words(line);

    for (vector<string>::const_iterator it = words.begin();
      it != words.end(); ++it)
      if ( find(ret[*it].begin(), ret[*it].end(), line_number)
        == ret[*it].end() )
        ret[*it].push_back(line_number);
  }
  return ret;
}

typedef pair<int, string> num_word;
typedef vector<num_word> NumberedWord;

NumberedWord to_indexedword(const map< string, vector<int> >& m)
{
  NumberedWord ret;
  num_word c;

  for (map< string, vector<int> >::const_iterator it = m.begin();
    it != m.end(); ++it) {
    c.first = it->second.size();
    c.second = it->first;
    ret.push_back(c);
    }

  return ret;
}

bool compare_first(const num_word a, const num_word b)
{
  return a.first < b.first;
}

void print_lines(vector<int>::const_iterator b, vector<int>::const_iterator e)
{
  cout << *b;
  ++b;
  while (b != e){
    cout << ", " << *b;
    ++b;
  }
  cout << endl;
  return;
}

int main()
{
  map< string, vector<int> > ret = xref(cin);

  // unsroded version
  for (map< string, vector<int> >::const_iterator it = ret.begin();
       it != ret.end(); ++it) {
    // print the word
    cout << it->first << " occurs on line(s): ";
    // print the line numbers
    print_lines(it->second.begin(), it->second.end());
  }

  cout << endl;

  // sort the map by value size
  NumberedWord map_order = to_indexedword(ret);
  sort(map_order.begin(), map_order.end(), compare_first);
  // print according to the mao_order
  for (NumberedWord::size_type i = 0; i != map_order.size(); ++i) {
    string word = map_order[i].second;
    // print the word
    cout << word << " occurs on lines(s); ";
    // print the line nums
    print_lines(ret[word].begin(), ret[word].end());
  }

  return 0;
}
