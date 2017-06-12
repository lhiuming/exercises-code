#include <vector>
#include <string>
#include <set>

using namespace std;

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> ret;

        // corner cases
        if (beginWord.empty()) return ret;
        if (wordList.empty()) return ret;
        if (beginWord == endWord) { return ret; }

        // Filter the dict
        set<string> remain_words;
        for (string& s : wordList) remain_words.insert(std::move(s));

        // must fail if endWord is not in original word list
        if (remain_words.find(endWord) == remain_words.end()) return ret;

        // make sure terminal words are not in it
        remain_words.erase(beginWord);

        // BFS search on the graph in reversed order (simpler concatation)
        vector<string> first_layer {endWord};
        auto pre_ret = bfs(first_layer, beginWord, remain_words);
        ret = std::move(pre_ret[0]);
        return ret;
    }
private:

    // bfs
    using Path = vector<string>;
    using Paths = vector<Path>;
    static vector<Paths>
    bfs(const vector<string>& layer,  const string& endWord, set<string>& remain_words) {

        vector<Paths> ret{layer.size()};

        // check if this layer reaches the endWord
        bool reached = false;
        for (int i = 0; i < layer.size(); ++i) {
            if (word_dist(layer[i], endWord) == 1) {
                ret[i].push_back( {endWord, layer[i]} ); // add the short path (reversed)
                reached = true;
            }
        }
        if (reached) return ret;

        // reutrn {} if we can't conitnue
        if (remain_words.empty()) return ret;

        // find and connect to next_layer
        vector<string> next_layer;
        vector<vector<int>> next(layer.size());
         for (auto iter = remain_words.begin(); iter != remain_words.end(); /*below*/) {
            bool to_erase = false;
            for (int i = 0; i < layer.size(); ++i)
                if (word_dist(layer[i], *iter) == 1) {
                    next[i].push_back(next_layer.size()); // not in next_layer yet
                    to_erase = true;
                }
            if (to_erase) {
                next_layer.push_back(*iter); // in next_layout now
                remain_words.erase(iter++);
            } else { iter++; }
         }

        // end if we can't go deeper
        if (next_layer.empty()) return ret;

        // recieve sub_paths
        vector<Paths> subpaths_from_next = bfs(next_layer, endWord, remain_words);
        for (int i = 0; i < layer.size(); ++i) {
            for (int li : next[i]) {
                const Paths& subpaths = subpaths_from_next[li];
                for (const Path& sp : subpaths) {
                    ret[i].push_back(sp);
                    ret[i].back().push_back(layer[i]); // append to the subpath
                }
            }
        }

        return ret;
    }

    static int word_dist(const string& s, const string& t) {
        int count = 0;
        for (int i = 0; i < s.size(); ++i)
            if (s[i] != t[i]) ++count;
        return count;
    }

};


int main()
{
  return 0;
}
