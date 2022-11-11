#include <bits/stdc++.h>

using namespace std;

#define SPAS_LOG 22
#define SPAS_NODE 1000001
int spas[SPAS_LOG][SPAS_NODE];
int h[SPAS_NODE];
void do_spas() {
  for (int i = 1; i < SPAS_LOG; ++i) {
    for (int j = 1; j < SPAS_NODE; ++j) {
      spas[i][j] = spas[i - 1][spas[i - 1][j]];
    }
  }
}
int lca(int u, int v) {
  if (h[u] < h[v]) swap(u, v);
  int diff = h[u] - h[v];
  for (int i = SPAS_LOG - 1; i >= 0; --i)
    if (diff & (1 << i)) u = spas[u][i];
  if (u == v) return u;
  for (int i = SPAS_LOG - 1; i >= 0; --i)
    if (spas[u][i] != spas[v][i])
      u = spas[u][i], v = spas[v][i];
  return spas[u][0];
}
