#include <iostream>
#include <vector>
#include <algorithm>

using std::cin; using std::cout;
using std::endl; using std::string;
using std::sort; using std::vector;

int main()
{
  cout << "Please input: " << endl;
  vector<string> words;
  string x;
  while (cin >> x)
    words.push_back(x);

  sort(words.begin(), words.end());

  typedef vector<string>::size_type vec_sz;
  string current = words[0];
  vec_sz count = 1;

  cout << endl;

  // we found word x count times
  for (vec_sz i = 1; i < words.size(); ++i) {
    if (words[i] != current) {
      cout << current << ":\t" << count << endl;
      current = words[i];
      count = 1;
    } else ++count;
    if (i == words.size() - 1)
      cout << current << ":\t" << count << endl;
  }


  return 0;
}
      
