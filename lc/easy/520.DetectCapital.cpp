/*
 * Given a word, you need to judge whether the usage of capitals in it is right or not.
 *
 * We define the usage of capitals in a word to be right when one of the following cases holds:
 *
 * All letters in this word are capitals, like "USA".
 * All letters in this word are not capitals, like "leetcode".
 * Only the first letter in this word is capital if it has more than one letter, like "Google".
 * Otherwise, we define that this word doesn't use capitals in a right way.
 *
 * https://leetcode.com/problems/detect-capital/
 */

#include <string>
#include <iostream>
#include <cctype>
#include <locale>

using namespace std;

class Solution {
public:
  bool detectCapitalUse(string word) {
    if (word.size() < 2) return true;
    int second_cap = isupper(word[1]);
    if (second_cap && !isupper(word[0])) return false;
    for (int i = 2; i < word.size(); ++i)
      if (second_cap != isupper(word[i])) return false;
    return true;
  }
};


// Test the solution
int main () {
  Solution s;
  string a("USA"), b("LeetcodeD"), c("Google"), d("miao");
  cout << a << ": " << s.detectCapitalUse(a) << endl;
  cout << b << ": " << s.detectCapitalUse(b) << endl;
  cout << c << ": " << s.detectCapitalUse(c) << endl;
  cout << d << ": " << s.detectCapitalUse(d) << endl;

  return 0;
}
