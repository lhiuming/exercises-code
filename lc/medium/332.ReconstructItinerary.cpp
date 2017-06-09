#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <unordered_map>
#include <set>

using namespace std;

class Solution {
public:
  vector<string> findItinerary(vector<pair<string, string>> tickets) {
    // Put data into a hash-map of multiset
    unordered_map<string, multiset<string>> adj;
    for (auto& p : tickets)
    {
      adj[std::move(p.first)].insert(std::move(p.second));
    }

    // Construct a linear base-route
    vector<string> itinerary;
    itinerary.reserve(tickets.size() + 1);
    itinerary.push_back("JFK");
    take_route(itinerary.front(), itinerary, adj);

    // Handle the loops (that starts with less immediate targets)
    int loop_start_pos = itinerary.size() - 1;
    while (loop_start_pos >= 0)
    {
      if (adj.find(itinerary[loop_start_pos]) != adj.end())
      { // We do have a loop to include from airport `loop_start_pos`
        vector<string> loop;
        take_route(itinerary[loop_start_pos], loop, adj);
        // insert into `itinerary` // NOTE better use a linked-list
        itinerary.insert(itinerary.begin() + loop_start_pos + 1,
          loop.begin(), loop.end() );

        #ifdef DEBUG
        cout << "loop_start_pos : " << loop_start_pos << " = "
             << itinerary[loop_start_pos] << " -> " << loop.front() << endl;
        #endif

        // roll back to check the new parts
        loop_start_pos += loop.size();
      }
      else
      { // No more loops for this airport
        #ifdef DEBUG
        cout << "loop_start_pos : " << loop_start_pos << " = "
             << itinerary[loop_start_pos] << " -> no alternative ap" << endl;
        #endif
        --loop_start_pos;
      }
    }

    return itinerary;
  }

private:

  // Extra a route from adj, starting from `ret.front()`; return last airport
  static void take_route(string& head, vector<string>& output,
    unordered_map<string, multiset<string>>& adj) {
    auto map_pos = adj.find(head);
    while ( map_pos != adj.end() )
    {
      auto& targets = map_pos->second;
      const auto& first_pos = targets.begin();
      output.push_back( std::move(*first_pos) );
      targets.erase(first_pos);
      if (targets.empty()) adj.erase(map_pos);

      map_pos = adj.find(output.back());
    }
    return;
  }

};


int main()
{
  using Input = vector<pair<string, string>>;
  Input test1 = { {"MUC","LHR"},{"JFK","MUC"},{"SFO","SJC"},{"LHR","SFO"} };
  Input test2 = { {"JFK", "SFO"}, {"SFO", "ATL"}, {"JFK", "SFO"},
    {"SFO", "MUC"}, {"MUC", "JFK"},
    {"JFK", "AAA"}, {"AAA", "JFK"},
    {"JFK", "ZZZ"}, {"ZZZ", "JFK"},
  };

  Solution solver;
  for (string s : solver.findItinerary(test1))
    cout << s << ", ";
  cout << endl;
  for (string s : solver.findItinerary(test2))
    cout << s << ", ";
  cout << endl;

  return 0;
}
