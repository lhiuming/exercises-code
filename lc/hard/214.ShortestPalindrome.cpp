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
    char base = numeric_limits<char>::min();
    const int char_num = numeric_limits<char>::max() + 1 - numeric_limits<char>::min();
    vector<array<int, char_num>> DFA(len);
    // the first state
    for (int j = 0; j < char_num; ++j) DFA[0][j] = 0;
    DFA[0][s[0] - base] = 1;
    // the rest states
    for (int i = 1, reset = 0; i < len; ++i) {
      for (int j = 0; j < char_num; ++j) DFA[i][j] = DFA[reset][j];
      DFA[i][s[i] - base] = i + 1;
      reset = DFA[ reset ][ s[i] - base ];
    }

    // Find palindrome in the original string, using the DFA in reversed order
    // that is, run until left and right meet at the center of the sub-palindrome
    int left = 0, right = s.size();
    while (left < right) {
      unsigned char inp = s[--right] - base;
      left = DFA[left][inp];
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
    cout << "append " << ret << endl;
    #endif
    ret.append(s);

    return ret;
  }
};


int main()
{
  Solution solver;
  string test1 = "xsbuyiszrlmbzqlmdtzmfkgcomdapmzhtltbzqaz";
  string test2 = "aaa";

  cout << "size " << test1.size() << ": "
       << solver.shortestPalindrome(test1) << endl;
  cout << "size " << test2.size() << ": "
       << solver.shortestPalindrome(test2) << endl;

  return 0;
}
