#include <vector>
#include <array>
#include <string>
#include <iostream>

#define DEBUG

using namespace std;

class Solution {
public:
  string shortestPalindrome(string s) {
    // Corner case
    if (s.size() < 2) return s;

    // Make a KMP DFA for the first half of s
    int len = (s.size() + 1) / 2;
    vector<size_t> mismatch_update(len, 0);
    for (int i = 1, reset = 0; i < len; ++i) {
      mismatch_update[i] = reset;
      while (s[i] != s[reset] && reset > 0) reset = mismatch_update[reset];
      if (s[i] == s[reset]) ++reset;
    }

    #ifdef DEBUG
    for (int i = 0; i < len; ++i)
      cout << s[i] << ":" << mismatch_update[i] << ", ";
    cout << endl;
    #endif

    // Find palindrome in the original string, using the DFA in reversed order
    // that is, run until left and right meet at the center of the sub-palindrome
    int left = 0, right = s.size();
    while (left < right) {
      --right;
      while ( (s[left] != s[right]) && (left > 0))
        left = mismatch_update[left];
      if (s[left] == s[right]) ++left;
    }

    // Build the return
    string ret;
    int pali_end;
    if (left == right) { // `abba` style or no-palidrome, and `left` cross the center or `left==0`
      pali_end = 2 * left;
    } else { // 'abcba' style, and `left` cross the center
      pali_end = 2 * left - 1;
    }
    for (int i = s.size(); i > pali_end; --i) ret.append(1, s[i - 1]);
    #ifdef DEBUG
    cout << "append " << ret << ", left = " << left << endl;
    #endif
    ret.append(s);

    return ret;
  }
};


int main()
{
  Solution solver;
  string test1 = "aacecaaa";
  string test2 = "babbbabbaba";
  string test3 = "ababbbabbaba";


  cout << "size " << test1.size() << ": "
       << solver.shortestPalindrome(test1) << endl;
  cout << "size " << test2.size() << ": "
       << solver.shortestPalindrome(test2) << endl;
  cout << "size " << test3.size() << ": "
       << solver.shortestPalindrome(test3) << endl;

  return 0;
}
