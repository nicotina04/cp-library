#include "bits/stdc++.h"

using namespace std;

struct trie {
  trie *child[26];
  bool terminal, haschild;

  trie() : terminal(false), haschild(false) { fill(child, child + 26, nullptr); }
  ~trie() {
    for (int i = 0; i < 26; ++i) if (child[i] != nullptr) delete child[i];
  }

  void insert(const char *key) {
    if (*key == '\0') {
      terminal = true;
      return;
    }
    haschild = true;
    int nxt = *key - 'a';
    if (child[nxt] == nullptr)
      child[nxt] = new trie();
    child[nxt]->insert(key + 1);
  }

  int find(const char *key) {
    if (*key == '\0') return terminal;
    int nxt = *key - 'a';
    if (child[nxt] == nullptr) return 0;
    return child[nxt]->find(key + 1);
  }
};