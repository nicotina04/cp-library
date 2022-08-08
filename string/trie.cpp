#include "bits/stdc++.h"

using namespace std;

struct trie {
  const static int sz = 26;
  const static char offset = 'a';
  trie *child[sz];
  bool terminal, haschild;

  trie() : terminal(false), haschild(false) { fill(child, child + sz, nullptr); }
  ~trie() { for (auto &i : child) delete i; }

  void insert(const char *key) {
    if (*key == '\0') {
      terminal = true;
      return;
    }
    haschild = true;
    int nxt = *key - offset;
    if (child[nxt] == nullptr) child[nxt] = new trie();
    child[nxt]->insert(key + 1);
  }

  int find(const char *key) {
    if (*key == '\0') return terminal;
    int nxt = *key - offset;
    if (child[nxt] == nullptr) return 0;
    return child[nxt]->find(key + 1);
  }
};
