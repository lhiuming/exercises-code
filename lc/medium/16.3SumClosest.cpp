/*
 * "
 * Given an array S of n integers, find three integers in S such that the sum is
 * closest to a given number, target. Return the sum of the three integers. You
 * may assume that each input would have exactly one solution.
 * "
 *
 * https://leetcode.com/problems/3sum-closest/#/description
 */

#include <cstddef>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
  int threeSumClosest(vector<int>& nums, int target) {
    // Sort the bums for fast picking
    sort(nums.begin(), nums.end());
    // For each i, find the closest (k, j) to target
    int best = nums[0] + nums[1] + nums[2];
    for (size_t i = 0; i < nums.size() - 2; ++i) {
      int target_i = target - nums[i];
      size_t j = i + 1, k = nums.size() - 1;
      int best_i = nums[j] + nums[k];
      while (j < k) {
        int sum = nums[j] + nums[k];
        if (closer(target_i, sum, best_i)) {
          best_i = sum;
          if (best_i == target_i) return target; // quick return
        }
        (sum < target_i ? ++j : --k);
      } // end while
      if (closer(target, best_i + nums[i], best))
        best = best_i + nums[i];
    } // end for
    return best;
}
private:
  int abs(int a) { return (a < 0) ? -a : a; }
  bool closer(const int& target, const int& rhs, const int& lhs) {
    return abs(rhs - target) < abs(lhs - target); }
};

int main()
{
  Solution s;
  vector<int> test {-1, 2, 1, -4};
  cout << s.threeSumClosest(test, 1) << endl;

  return 0;
}
