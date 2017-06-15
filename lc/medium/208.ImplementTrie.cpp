#include <iostream>
#include <string>

using namespace std;

class Trie {

  // Node class
  struct Node {
    char c;
    Node* match = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
    int count; // word count
    Node(char c, int n = 0) : c(c), count(n) {}

    // debug print
    friend ostream& operator<<(ostream& os, const Node* np) {
      if (np) {
        os << np->c;
        if (np->count > 0) os << np->count;
        os << " { " << np->left
           << " | "
           << np->match << " | " << np->right << " }";
      }
      return os;
    }
  };

public:
  /** Initialize your data structure here. */
  Trie() {
    // nothing to do
  }

  /** Inserts a word into the trie. */
  void insert(string word) {
    root = insert(root, word, 0);
  }

  /** Returns if the word is in the trie. */
  bool search(string word) {
    if (word.empty()) return true;
    int count = 0;
    int match_size = find(root, word, 0, count);
    return (match_size == word.size()) && (count > 0);
  }

  /** Returns if there is any word in the trie that starts with the given
   * prefix. */
  bool startsWith(string prefix) {
    if (prefix.empty()) return true;
    int count = 0;
    int match_size = find(root, prefix, 0, count);
    return match_size == prefix.size();
  }

  // Debug helper
  friend ostream& operator<<(ostream& os, const Trie& trie) {
    return os << trie.root;
  }

private:

  Node* root = nullptr;

  // Helpers //

  // Insert from root-node
  Node* insert(Node* root, const string& word, int depth) {
    if (depth == word.size()) return root;
    if (root == nullptr) root = new Node(word[depth]);

    if (word[depth] < root->c)
      root->left = insert(root->left, word, depth);
    else if (word[depth] > root->c)
      root->right = insert(root->right, word, depth);
    else { // match
      root->match = insert(root->match, word, depth + 1);
      if (depth == word.size() - 1) root->count += 1;
    }

    return root;
  }

  // Find from root-node; return the match_size and count
  int find(Node* root, const string& word, int depth, int& count) {
    if (depth == word.size()) return depth;
    if (root == nullptr) return depth;

    if (word[depth] > root->c)
      return find(root->right, word, depth, count);
    if (word[depth] < root->c)
      return find(root->left, word, depth, count);

    count = root->count; // update the count of most recent match
    return find(root->match, word, depth + 1, count);
  }

};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * bool param_2 = obj.search(word);
 * bool param_3 = obj.startsWith(prefix);
 */


 int main()
 {
   Trie trie;

   trie.insert("Mio");
   trie.insert("Miku");
   trie.insert("Miu");
   cout << trie << endl;

   cout << "`` inside : " << trie.search("") << endl;
   cout << "M inside : " << trie.search("M") << endl;
   cout << "i inside : " << trie.search("i") << endl;
   cout << "Miu inside : " << trie.search("Miu") << endl;
   cout << "Mik inside : " << trie.search("Mik") << endl;
   cout << "Mio inside : " << trie.search("Mio") << endl;
   cout << "Miku inside : " << trie.search("Miku") << endl;

   cout << "start with ``" << trie.startsWith("") << endl;
   cout << "start with `i`" << trie.startsWith("i") << endl;
   cout << "start with `M`" << trie.startsWith("M") << endl;
   cout << "start with `MI`" << trie.startsWith("MI") << endl;
   cout << "start with `Mi`" << trie.startsWith("Mi") << endl;
   cout << "start with `Mik`" << trie.startsWith("Mik") << endl;

   cout << "-- new trie -- " << endl;
   trie = Trie{};
   trie.insert("abc");
   trie.insert("ab");
   cout << trie << endl;
   cout << "ab inseide : " << trie.search("ab") << endl;

   return 0;
 }
