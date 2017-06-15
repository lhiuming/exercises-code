#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

//#define DEBUG

ostream& operator<<(ostream& os, unordered_map<int, shared_ptr<pair<int, int>>>& table) {
  for (auto p : table) {
    os << p.first << " : [" << p.second->first
       << ", " << p.second->second << "]" << endl;
  }
  return os;
}


class Solution {
public:
  int longestConsecutive(vector<int>& nums) {
    // Define a hash table to store consecutive sequence
    using Sequence = pair<int, int>; // (first, last)
    using SeqPtr = shared_ptr<Sequence>;
    unordered_map<int, SeqPtr> left_table; // map by left-bound
    unordered_map<int, SeqPtr> right_table; // map by right_bound

    // Scan the nums and make the mapping
    int longest = 0;
    for (int a : nums)
    {
      // ignore duplicate terminals
      if (left_table.find(a) != left_table.end()) continue;
      if (right_table.find(a) != right_table.end()) continue;

      #ifdef DEBUG
      cout << a << " ---- " << endl;
      cout << left_table << endl;
      cout << right_table << endl;
      #endif

      auto pre_iter = right_table.find(a - 1);
      auto post_iter = left_table.find(a + 1);

      SeqPtr seqp;
      if (pre_iter != right_table.end())
      {
        if (post_iter != left_table.end())
        { // case 3: can bridge two sequences
          int left = (pre_iter->second)->first;
          int right = (post_iter->second)->second;
          seqp = make_shared<Sequence>(left, right);
          // erase mapping from indisde
          left_table.erase(post_iter);
          right_table.erase(pre_iter);
          // update mapping from outside
          left_table[left] = seqp;
          right_table[right] = seqp;
        }
        else
        { // case 2: can elongate a sequence from tail
          seqp = pre_iter->second;
          seqp->second = a; // change right bound (from a-1 to a)
          right_table.erase(pre_iter);
          right_table[a] = seqp; // add new right-bound mapping
        }
      }
      else
      {
        if (post_iter != left_table.end())
        { // case 1: can elongate a sequence from head
          seqp = post_iter->second;
          seqp->first = a; // change left bound (from a+1 to a)
          left_table.erase(post_iter);
          left_table[a] = seqp; // add new left-bound mapping
        }
        else
        { // case 4 : new, single number
          seqp = make_shared<Sequence>(a, a);
          left_table[a] = seqp;
          right_table[a] = seqp;
        }
      }

      // update longest
      longest = max(longest, seqp->second - seqp->first + 1);

    } // end for

    return longest;
  }
};


int main()
{
  using Case = vector<int>;
  vector<Case> test_cases = {
    {100,4,200,1,3,2},
    {2, 3, 1},
    {},
    {0},
    {0, 1},
    {0, 0, 1},
    {0, 1, 1},
    {0, 0, 0, 1, 1, 1},
    {4, 3, 2, 1},
    {1, 2, 4, 5, 3},
    {9, 5, 2, 1, 2},
    {7,-9,3,-6,3,5,3,6,-2,-5,8,6,-4,-6,-4,-4,5,-9,2,7,0,0},
  };

  Solution solver;
  for (Case& c : test_cases)
    cout << solver.longestConsecutive(c) << endl;

  return 0;
}
