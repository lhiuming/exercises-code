/*
 * Given a list of positive integers, the adjacent integers will perform the
 * float division. For example, [2,3,4] -> 2 / 3 / 4.
 *
 * However, you can add any number of parenthesis at any position to change the
 * priority of operations. You should find out how to add parenthesis to get the
 * maximum result, and return the corresponding expression in string format.
 * Your expression should NOT contain redundant parenthesis.
 *
 * https://leetcode.com/problems/optimal-division/
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  string optimalDivision(vector<int>& nums) {
    if (nums.size() <= 2) return insert(nums.begin(), nums.end());
    string ret = to_string(nums[0]).append("/");
    ret.append("(").append( insert(nums.begin() + 1, nums.end()) ).append(")");
    return ret;
  }
private:
  using Iter = typename vector<int>::iterator;
  string insert(Iter b, Iter e) {
    string ret = to_string( *(b++) );
    for (; b != e; ++b) ret.append( string("/") + to_string(*b) );
    return ret;
  }
};

int main() {
  Solution s;
  vector<int> testcase0 {5};
  cout << s.optimalDivision(testcase0) << endl;
  vector<int> testcase1 {5, 2};
  cout << s.optimalDivision(testcase1) << endl;
  vector<int> testcase2 {1000,100,10,2};
  cout << s.optimalDivision(testcase2) << endl;

  return 0;
}
