// Solve S.Loyd's 8 puzzle using A* algorithm on a grid-layouted graph.

#include <string>
#include <iostream>
#include <vector>
#include <array>

#include <sorting.hpp> // for MaxPQ
#include <fundamentals.hpp> // for Stack

using namespace std;

template<int W>
class EightPuzzle {

  // Class to represent a state
  struct State {
    array<int, W * W> arrange; // 0 : space; others: tiles

    vector<State> next() const {
      int i, j; // position of the space
      for (int t = 0; t < W * W; ++t)
        if (arrange[t] == 0) { i = t / W; j = t % W; break; }
      vector<State> ret;
      if (i > 0  ) ret.push_back(slide(i, j, i - 1, j));
      if (i < W-1) ret.push_back(slide(i, j, i + 1, j));
      if (j > 0  ) ret.push_back(slide(i, j, i, j - 1));
      if (j < W-1) ret.push_back(slide(i, j, i, j + 1));
      return ret;
    }
    State slide(int i, int j, int to_i, int to_j) const {
      array<int, W * W> new_arrange = arrange;
      std::swap(new_arrange[i * W + j], new_arrange[to_i * W + to_j]);
      return State{new_arrange};
    }

    int distance(const State& rhs) const {
      // Hanmming distance; Alternative: Manhhatan, Manhhatan^2
      int ret = 0;
      for (int i = 0; i < W * W; ++i)
          if (arrange[i] != rhs.arrange[i]) ++ret;
      return ret;
    }

    bool operator==(const State& rhs) const {
      for (int i = 0; i < W * W; ++i)
          if (arrange[i] != rhs.arrange[i]) return false;
      return true;
    }
    bool operator!=(const State& rhs) const { return !(*this == rhs); }

    // self-printing
    friend ostream& operator<<(ostream& os, const State& s) {
      for (int i = 0; i < W * W; ++i) {
        if (i % W == 0) {
          os << endl;
          for (int i = 0; i < W; ++i) os << "----";
          os << "-" << endl << "| ";
        }
        os << s.arrange[i] << " | ";
      }
      os << endl;
      for (int i = 0; i < W; ++i) os << "----";
      return os << "-";
    }
  };

  // Node to record move directions
  struct Node {
    State state;
    shared_ptr<Node> prev;
    int moves;
    int cost;

    Node(State& s, shared_ptr<Node> p, int m, int c)
    : state(s), prev(p), moves(m), cost(c) {}
  };
  struct NodePtr : public shared_ptr<Node> { // wrapper
    using Base = shared_ptr<Node>;
    using Base::Base;

    // The only reason for this wrapper :D
    bool operator<(const NodePtr& rhs) const {
      return (*this)->cost < rhs->cost; }
  };


public:

  // Construct and solve
  EightPuzzle(vector<int> initial_config,
    vector<int> goal_config = vector<int>()) {
    for (int i = 0; i < W * W; ++i) {
      init.arrange[i] = initial_config[i];
      goal.arrange[i] = goal_config.empty() ? i : goal_config[i];
    }
    solve();
  }

  // Get solusion path
  algs::Stack<Node> path() const {
    algs::Stack<Node> ret;
    shared_ptr<Node> head = solution;
    while (head) {
      #ifdef DEBUG
      cout << "trying to push stack : " << head->moves << endl;
      #endif
      ret.push(*head);
      head = head->prev;
    }
    return ret;
  }

  // Self-printing
  friend ostream& operator<<(ostream& os, const EightPuzzle& sol) {
    for (Node& node : sol.path())
      os << node.moves << " (cost " << node.cost << "):" << node.state << endl;
    return os;
  }

private:

  State init;
  State goal;
  shared_ptr<Node> solution;

  void solve() {
    algs::MinPQ<NodePtr> pq;
    pq.push( make_shared<Node>(init, nullptr, 0, init.distance(goal)) );
    while (!pq.empty()) {
      NodePtr curr = pq.pop();
      if (curr->state == goal) { solution = curr; return; }
      for (State& n : curr->state.next()) {
        int moves = curr->moves + 1;
        if ( curr->prev && (curr->prev->state == n) ) continue;
        pq.push(make_shared<Node>(n, curr, moves, moves + n.distance(goal)));
      }
    }
    #ifdef DEBUG
    cout << "End without solution!" << endl;
    #endif
  }

};


int main()
{
  const int DIM = 3;

  int s;
  vector<int> init, goal;
  for (int i = 0; i < DIM * DIM; ++i)
  {
    cin >> s; init.push_back(s);
  }
  for (int i = 0; i < DIM * DIM; ++i)
  {
    cin >> s; goal.push_back(s);
  }
  cout << "Reading input DONE." << endl;

  EightPuzzle<DIM> solver(init, goal);
  cout << "Solution constructed: ";
  cout << solver << endl;

  return 0;
}
