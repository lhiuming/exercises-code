#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

#define DEBUG

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // Each nums is split into two clear halves:
        //       [0, left_end)  and  [right_begin, end),
        // where left_end - right_begin == 0 or 1.

        // Handle emtpy array
        int size1 = nums1.size(), size2 = nums2.size();
        if (size1 == 0) return median(nums2);
        if (size2 == 0) return median(nums1);

        // For simplicity, remove a max element if sum of sizes is odd
        bool bias = false;
        if ( (size1 + size2) % 2 == 1 )
        {
          nums1.back() < nums2.back() ? --size2 : --size1;
          bias = true;
        }

        // Make an initialze clear split
        int size_of_halves = (size1 + size2) / 2;
        int split1 = size1 / 2, split2 = size_of_halves - split1;

        // search for a split at the median-position
        // loop invariant: size_of (left halves) == size_of (right halves)
        while (true)
        {
          // debug
          #ifdef DEBUG
          cout << "nums1: " << split1 << endl;
          cout << "nums2: " << split2 << endl;
          #endif

          // get the max of left halves
          int left_max1 = (split1 == 0) ? INT_MIN : nums1[split1 - 1];
          int left_max2 = (split2 == 0) ? INT_MIN : nums2[split2 - 1];
          int left_max = max(left_max1, left_max2);

          // get the min of right halves
          int right_min1 = (split1 == size1) ? INT_MAX : nums1[split1];
          int right_min2 = (split2 == size2) ? INT_MAX : nums2[split2];
          int right_min = min(right_min1, right_min2);

          // Check if reaches the final goal
          if (left_max <= right_min)
          {
            if (bias) return right_min;
            return (left_max + right_min) / 2.0;
          }

          // Otherwise, adjust the splitting by binarily skipping
          if (left_max1 > right_min2)  // nums1 leans too right
          {
            int moveable = min(split1, size2 - split2);
            // prine the range before next move
            size1 = split1;
            int amount =  (moveable + 1) / 2;
            // split1 should move left, split2 right;
            split1 -= amount; split2 += amount;
          }
          else // nums2 leans too right
          {
            int moveable = min(size1 - split1, split2);
            int amount = (moveable + 1) / 2;
            // prine for next move
            size2 = split2;
            // split1 should move right, split2 left
            split1 += amount; split2 -= amount;
          }
        } // end while
        throw runtime_error("Array not sorted!");
        return 0.0;
    }
private:

static double median(vector<int>& nums) {
  size_t s = nums.size();
  return ( nums[ (s-1)/2 ] + nums[ s / 2 ] ) / 2.0;
}

};

int main()
{
  Solution solver;

  // Test case 0
  vector<int> nums1;
  vector<int> nums2({2});

  cout << solver.findMedianSortedArrays(nums1, nums2) << endl;

  // Test case 1
  nums1 = vector<int>({1, 3});
  nums2 = vector<int>({2});

  cout << solver.findMedianSortedArrays(nums1, nums2) << endl;

  // Test case 2
  nums1 = vector<int>({1, 3, 5});
  nums2 = vector<int>({1, 2, 5});

  cout << solver.findMedianSortedArrays(nums1, nums2) << endl;

  // Test case 3
  nums1 = vector<int>({1, 3, 5});
  nums2 = vector<int>({1, 2, 4, 5});

  cout << solver.findMedianSortedArrays(nums1, nums2) << endl;

  // Test case 4
  nums1 = vector<int>({1, 3, 5, 9, 10});
  nums2 = vector<int>({11});

  cout << solver.findMedianSortedArrays(nums1, nums2) << endl;

  // Test case 5
  nums1 = vector<int>( {1,2,3,6,7} );
  nums2 = vector<int>( {4,5,8,9,10} );
  cout << solver.findMedianSortedArrays(nums1, nums2) << endl;

  return 0;
}
