#include "bits/stdc++.h"

using namespace std;

struct trie {
  trie *child[26];
  bool terminal, haschild;

  trie() : terminal(false), haschild(false) { for (auto &i : child) i = nullptr; }
  ~trie() { for (auto &i : child) delete i; }

  void insert(const char *key) {
    if (*key == '\0') {
      terminal = true;
      return;
    }
    haschild = true;
    int nxt = *key - 'a';
    if (child[nxt] == nullptr) child[nxt] = new trie();
    child[nxt]->insert(key + 1);
  }

  int find(const char *key) {
    if (*key == '\0') return terminal;
    int nxt = *key - 'a';
    if (child[nxt] == nullptr) return 0;
    return child[nxt]->find(key + 1);
  }
};
