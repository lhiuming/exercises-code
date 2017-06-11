#include <vector>
#include <unordered_set>
#include <iostream>

using namespace std;

class Solution {
public:
  vector<int> findSubstring(string s, vector<string>& words) {
    // Horrible corner cases
    if (words.empty()) return vector<int>();
    if (words[0].empty()) return vector<int>();
    if (s.size() < words[0].size() * words.size()) return vector<int>();

    // make a original set
    const unordered_multiset<string> original_wordset(words.begin(), words.end());

    int frame = words[0].size(); // uniform word length
    int match_len = frame * words.size();
    int pre_end = s.size() - match_len + 1;
    vector<int> ret;
    for(int offset = 0; offset < frame; ++offset)
    {
      // serach in bins
      int beg = offset;
      while (beg < pre_end)
      {
        if ( original_wordset.find(s.substr(beg, frame)) != original_wordset.end() )
        {
          // check for a complete match
          int sub_beg = beg;
          unordered_multiset<string> remain{original_wordset}; // copy
          decltype(remain.begin()) iter;
          while ( (iter = remain.find(s.substr(sub_beg, frame))) != remain.end() )
          {
              remain.erase(iter);
              sub_beg += frame;
          }
          if (remain.empty()) // realy match
          {
              ret.push_back(beg);
              // collection repetition
              while ( (beg < pre_end) &&
                  (s.substr(beg, frame) == s.substr(sub_beg, frame)) )
              {
                  beg += frame; sub_beg += frame;
                  ret.push_back(beg);
              }
          }
          else // not match
          {
              // skip same combination
              while ( (beg < pre_end) &&
                  (s.substr(beg, frame) == s.substr(sub_beg, frame)) )
              {
                  beg += frame; sub_beg += frame;
              }
          }
          // update
          beg += frame;
        }
        else
        { // just move on
          beg += frame;
        }

      } // end while

    } // end for
    return ret;
  }
};

int main()
{
  Solution solver;

  vector<string> ws1{"bar", "foo","bar"};
  auto sol1 = solver.findSubstring("barfoothefoobarfoobarman", ws1);

  vector<string> ws2{"aaaa", "aaaa", "aaaa"};
  auto sol2 = solver.findSubstring("aaaaaaaaaaaaaaaaa", ws2);

  return 0;
}
