#include <vector>

using namespace std;

struct union_find {
  vector<int> parent, rank;
  union_find(int _n): parent(_n), rank(_n) {
    for (int i = 0; i < _n; i++) parent[i] = i;
  }
  int find(int u) {
    if (parent[u] == u) return u;
    return parent[u] = find(parent[u]);
  }
  bool eq(int u, int v) {
    return find(u) == find(v);
  }
  void vnion(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return;
    if (rank[u] > rank[v]) swap(u, v);
    parent[u] = v;
    if (rank[u] == rank[v]) ++rank[v];
  }
};
