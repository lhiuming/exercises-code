#include <iostream>
#include <vector>
#include <functional>
#include <queue>

using namespace std;


/**
 * Definition for singly-linked list.
 */
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
  // wrapper class
  struct IndexedNode {
    ListNode* pnode;
    int index;

    // inversed compare; used for priority queue
    friend bool operator<(const IndexedNode& lhs, const IndexedNode& rhs) {
        return lhs.pnode->val > rhs.pnode->val;
    }
  };
public:
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    int k = lists.size();

    // coner cases
    if (k < 1) return nullptr;
    if (k < 2) return lists.front();

    // use heap sort on k-node //

    // push the first heads
    priority_queue<IndexedNode> pq;
    for (int i = 0; i < k; ++i)
    {
        if (lists[i]) {
            pq.push( {lists[i], i} );
            lists[i] = lists[i]->next;
        }
    }
    if (pq.empty()) return nullptr;

    // pop the first node from pq
    ListNode* head = pq.top().pnode;
    int i = pq.top().index;
    pq.pop();
    if (lists[i]) {
        pq.push( {lists[i], i});
        lists[i] = lists[i]->next;
    }

    // push and pop for the rest nodes
    ListNode* tail = head;
    while (!pq.empty())
    {
        // pop a next node from `pq`
        tail->next = pq.top().pnode;
        int i = pq.top().index;
        pq.pop();
        // pop from `lists[i]` to filll `pq`, if `lists[i]` is not empty
        if (lists[i]) {
            pq.push( {lists[i], i});
            lists[i] = lists[i]->next;
        }
        // update the tail
        tail = tail->next;
    }

    return head;

  }
};


// helper
ListNode* make_list(vector<int>& vals)
{
  if (vals.empty()) return nullptr;
  ListNode* head = new ListNode(vals[0]);
  ListNode* tail = head;
  for (int i = 1; i < vals.size(); ++i) {
    tail->next = new ListNode(vals[i]);
    tail = tail->next;
  }
  return head;
}

// hleper
ostream& operator<<(ostream& os, ListNode* p) {
  if (p) {
    os << p->val;
    if (p->next) os << ", " << p->next;
  }
  return os;
}

int main()
{
  using Case = vector< vector<int> >;
  vector<Case> test_cases = {
    {},
    { {1, 2, 3, 4}, {0, 5, 7, 9} },
    { {} },
    { {}, {} },
    { {}, {1} },
    { {}, {0}, {0} },
    { {}, {1, 1, 1, 1, 1}, {2, 3, 9} }
  };

  Solution solver;
  for (Case& c : test_cases) {
    vector<ListNode*> input;
    for (vector<int>& vals : c) input.push_back(make_list(vals));
    auto sol = solver.mergeKLists(input);
    cout << "{" << sol << "}" << endl;
  }

  return 0;
}
