#include <string>
#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <exception>
#include <cstdlib>  // RAND_MAX defined here. stdlin.h wrapped in std ns
#include <ctime>

#include "split.h"

using std::string;
using std::map;
using std::vector;
using std::list;

using std::istream;
using std::cin;
using std::cout;
using std::endl;

using std::rand;
using std::srand;
using std::time;

using std::domain_error;
using std::logic_error;

typedef vector<string> Rule;
typedef vector<Rule> Rule_collection;
typedef map<string, Rule_collection> Grammar;


Grammar read_grammar(istream& in)
{
  Grammar ret;
  string line;

  while (getline(in, line)) {
    vector<string> entry = split(line);
    if (!entry.empty())
    ret[entry[0]].push_back( Rule(entry.begin() + 1, entry.end()));
  }
  return ret;
}


bool brancketed(const string& s)
{
  return s.size() > 1 && s[0] == '<' && s[s.size()-1] == '>';
}


int nrand(int n)
{
  if (n <= 0)
    throw domain_error("Argument to nrand is not positive");

  int factor = (n - 1) / RAND_MAX + 1; // i dont know what to do if
  // factor * RAND_MAX > INT_MAX
  const int bucket_size = RAND_MAX / n;
  do {
    r = rand() / bucket_size; // may exceed n
  }
  while (r >= n);

  return r;
}

//typedef vector<string> Sent;
typedef list<string> Sent; // any type that supports push_back

void gen_aux(const Grammar& g, const string& word, Sent & ret)
{
  if(!brancketed(word)) {
    ret.push_back(word);
  } else {
    Grammar::const_iterator it = g.find(word);
    if (it == g.end())
      throw logic_error("empty rule");

    const Rule_collection& c = it->second;
    const Rule& r = c[nrand(c.size())];

    for (Rule::const_iterator i = r.begin(); i != r.end(); ++i)
      gen_aux(g, *i, ret);
  }
}


Sent gen_sentence(const Grammar& g)
{
  Sent ret;
  gen_aux(g, "<sentence>", ret);
  return ret;
}


int main() {
  srand(time(0));  // random result on each run

  // test nrand for large n
  for (int i = 0; i < 10; i++)
    cout << nrand(2147483647) << endl;

  // read grammar and generate sentence
  Sent sentence = gen_sentence(read_grammar(cin));

  Sent::const_iterator it = sentence.begin();
  // the first word
  if (!sentence.empty()) {
    cout << *it;
    ++it;
  }
  // the rest
  while (it != sentence.end()) {
    cout << " " << *it;
    ++ it;
  }
  cout << endl;
  return 0;
}
